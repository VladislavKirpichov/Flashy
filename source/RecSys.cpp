#include "RecSys.h"

template<class Net>
double RecSys<Net>::fit() {
  //optimize hyperparameters:
  //learning rate
  //k - tensor shape

  //Define matrix shape
  int docs_count = dataset_->get_documents_count();
  int cards_count = dataset_->get_flashcards_count();

  //fill random numbers in some range
  std::vector<int> k_grid = generate_k_grid(docs_count, cards_count);

  //fill random numbers in some range
  std::vector<double> learning_rate_grid = generate_lr_grid(5);

  //Define best parameters
  double best_loss;
  int best_k;
  double best_lr;

  srand(time(nullptr));
  const std::chrono::time_point<std::chrono::steady_clock> start_fit =
      std::chrono::steady_clock::now();

  for (const int k_iter: k_grid) {
    for (const double lr_iter: learning_rate_grid) {

      auto net = std::make_shared<Net>(docs_count, cards_count, k_iter);
      torch::Tensor output = net->train(dataset_->get_interaction_table(), 1e+3, lr_iter);
      double loss = output.item().toDouble();
          //eval_loss(output, dataset_);

      std::cout << "Model {lr = " << lr_iter << ", k = " << k_iter << "}"
       << "\nLoss: " << loss << std::endl;

      if (loss < best_loss) {
        best_loss = loss;
        best_k = k_iter;
        best_lr = lr_iter;
      }
    }
  }

  const auto end_fit = std::chrono::steady_clock::now();

  std::cout << "Best loss:" << best_loss
  << "\nBest k:" << best_k
  << "\nBest learning rate" << best_lr
  << "\nTIME: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_fit - start_fit).count()
  << "nanoseconds" << std::endl;



  //Training best model
  net_ = std::make_shared<Net>(docs_count, cards_count, best_k);
  net_->train(dataset_->get_interaction_table(), 1e+3, best_lr);
//  net_->save_model();
  std::cout << net_->get_doc2card() << std::endl;

  //save embeddings
  save_cards_embeddings(net_->get_flashcards_embeddings(), dataset_);
  save_docs_embeddings(net_->get_documents_embeddings(), dataset_);

  return best_loss;
}

template<class Net>
const std::vector<int> RecSys<Net>::generate_k_grid(int M, int N) {
  std::vector<int> grid(std::max(M,N));

  for (int i = 1; i < std::max(M,N); ++i) {
    grid.push_back(i);
  }

  return grid;
}

template<class Net>
const std::vector<double> RecSys<Net>::generate_lr_grid(int count) {
  std::vector<double> grid(count);
  srand(time(nullptr));

  for (int i = 0; i < count; ++i) {
    int a = rand() % 10 + 1;
    grid[i] = a * std::pow(10, -i);
  }

  return grid;
}

template<class Net>
double RecSys<Net>::eval_loss(const torch::Tensor &output,
                                       std::shared_ptr<Dataset> p_dataset) {
  double loss = 0;
  for (const auto& i: p_dataset->get_interactions_data()) {
    loss += std::pow((output[i.card_id][i.doc_id].item().to<double>() - i.mark), 2);
  }

  return loss;
}

template<class Net>
void RecSys<Net>::save_cards_embeddings(const torch::Tensor &p_flashcard_matrix,
                                        std::shared_ptr<Dataset> p_dataset) {
  using namespace torch::indexing;

  for (int i = 0; i < p_dataset->get_flashcards_count(); ++i) {
    flashcard_embeddings_[p_dataset->get_flashcards()[i]] =
        p_flashcard_matrix.index({Slice(), i});
  }
}

template<class Net>
void RecSys<Net>::save_docs_embeddings(const torch::Tensor &p_documents_matrix,
                                       std::shared_ptr<Dataset> p_dataset) {

  for (size_t i = 0; i < p_dataset->get_documents_count(); ++i) {
    document_embeddings_[p_dataset->get_documents()[i]] = p_documents_matrix[i];
  }
}


template<class Net>
RecSys<Net>::RecSys(const Dataset &p_dataset) {
  dataset_ = std::make_shared<Dataset>(p_dataset);
  net_ = std::make_shared<Net>(dataset_->get_documents_count(),
                                 dataset_->get_flashcards_count());
//  try {
//    load_model(net_);
//    // TODO: load embeddings (from file or database)
//  } catch (...) {
//    net_ = std::make_shared<Net>(dataset_->get_documents_count(),
//                                 dataset_->get_flashcards_count());
//  }
  //
}

template<class Net>
RecSys<Net>::~RecSys() {
  //
  //save_model(net_);
  //save data?
  // TODO: save embeddings to database(?) or in file
}


template<class Net>
double RecSys<Net>::cosine_similarity(torch::Tensor first, torch::Tensor second) {
  double res = 0;

  int size = std::min(first.size(0), second.size(0));

  for (int i = 0; i < size; ++i) {
    res += first.index({i}).item().toDouble()
        * second.index({i}).item().toDouble();
  }
  return res;
}

template<class Net>
std::vector<int> RecSys<Net>::i2i_predictions(int card_id, int count) {

  std::vector<std::pair<int,double>> similarity_vec;
  torch::Tensor current_emb = flashcard_embeddings_[card_id];

  for (const std::pair<int, torch::Tensor> &i: flashcard_embeddings_) {
    std::pair<int, double> temp;
    temp.first = i.first;
    temp.second = cosine_similarity(current_emb, i.second);

    similarity_vec.push_back(temp);
  }

  std::sort(similarity_vec.begin(), similarity_vec.end(),
            [similarity_vec](std::pair<int, double> p1, std::pair<int, double> p2)
  {
    return p1.second < p2.second;
  });

  std::vector<int> result(count + 1);
//  std::copy(similarity_vec.begin(), similarity_vec.begin() + count, result.begin());
  for (const auto &i: similarity_vec) {
    result.push_back(i.first);
  }
  return result;
}

template<class Net>
std::vector<int> RecSys<Net>::u2i_predictions(int doc_id, int count) {

  std::vector<std::pair<int, double>> flashcards;
  torch::Tensor interactions = net_->get_doc2card();
  std::vector<int> cards_id = dataset_->get_flashcards();
  std::vector<int> docs_id = dataset_->get_documents();


  for (int i = 0; i < dataset_->get_flashcards_count(); ++i) {
    std::pair<int, double> temp;
    temp.first = cards_id[i];
    temp.second = interactions.index({docs_id[doc_id], cards_id[i]}).item().toDouble();

    flashcards.push_back(temp);
  }

  std::sort(flashcards.begin(), flashcards.end(),
            [flashcards](std::pair<int, double> p1, std::pair<int, double> p2)
            {
              return p1.second < p2.second;
            });

  std::vector<int> result;
  for (const auto &i: flashcards) {
    result.push_back(i.first);
  }

  for (auto i: result) {
    std::cout << i << " ";
  }
  ///////////////
  Page page(doc_id);

  //get tests of page
  std::vector<std::string> tests_from_curr_page = page.get_all_page_questions_id(doc_id);
  std::transform(tests_from_curr_page.begin(), tests_from_curr_page.end()
  , tests_from_curr_page.begin(), [tests_from_curr_page](std::string test_id){
    return std::stoi(test_id);
  });

  //remove test of page
  std::remove_if(result.begin(), result.end()
                 , [result, tests_from_curr_page](int test_id) {
      return std::find(tests_from_curr_page.begin(), tests_from_curr_page.end(), result) != test_id;

  });

  //get title of page
//  std::string title = page.get_page_title();
  //get tests with curr title
  //remove tests out of title

  //save result to db
  for (int i = 0; i < count; ++i) {
    page.add_rec_question_id(std::to_string(result[i]));
  }
  for (auto i: result) {
    std::cout << i << " ";
  }
  return result;
}

void Creator::start_rec_sys() {
//  torch::Tensor interactions = torch::rand({3,3});
//  std::cout << interactions << std::endl;
//  Dataset data(interactions);
//  RecSys<Net> recommender(data);
//  double loss = recommender.fit();
//  std::cout << loss << '\n';

    Dataset data(Storage::all_files);
    RecSys<Net> recommender(data);
    double loss = recommender.fit();
    std::cout << loss << std::endl;
    for (const int i: Storage::all_files) {
      recommender.u2i_predictions(i, 5);
    }


}
