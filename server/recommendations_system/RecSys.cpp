#include "RecSys.h"

#include <iostream>
#include <algorithm>

#include "Page.h"
#include "Storage.h"

double RecSys::fit() {
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
    std::cout << net_->get_doc2card() << std::endl;

    //save embeddings
    save_cards_embeddings(net_->get_flashcards_embeddings(), dataset_);
    save_docs_embeddings(net_->get_documents_embeddings(), dataset_);

    return best_loss;
}

const std::vector<int> RecSys::generate_k_grid(int M, int N) {
    std::vector<int> grid(std::max(M,N));

    for (int i = 1; i < std::max(M,N); ++i) {
        grid.push_back(i);
    }

    return grid;
}

const std::vector<double> RecSys::generate_lr_grid(int count) {
    std::vector<double> grid(count);
    srand(time(nullptr));

    for (int i = 0; i < count; ++i) {
        int a = rand() % 10 + 1;
        grid[i] = a * std::pow(10, -i);
    }

    return grid;
}

double RecSys::eval_loss(const torch::Tensor &output,
                         std::shared_ptr<Dataset> p_dataset) {
    double loss = 0;
    for (const auto& i: p_dataset->get_interactions_data()) {
        loss += std::pow((output[i.card_id][i.doc_id].item().to<double>() - i.mark), 2);
    }

    return loss;
}

void RecSys::save_cards_embeddings(const torch::Tensor &p_flashcard_matrix,
                                   std::shared_ptr<Dataset> p_dataset) {
    using namespace torch::indexing;

    for (int i = 0; i < p_dataset->get_flashcards_count(); ++i) {
        flashcard_embeddings_[p_dataset->get_flashcards()[i]] =
                p_flashcard_matrix.index({Slice(), i});
    }
}

void RecSys::save_docs_embeddings(const torch::Tensor &p_documents_matrix,
                                  std::shared_ptr<Dataset> p_dataset) {

    for (size_t i = 0; i < p_dataset->get_documents_count(); ++i) {
        document_embeddings_[p_dataset->get_documents()[i]] = p_documents_matrix[i];
    }
}


RecSys::RecSys(const Dataset &p_dataset) {
    dataset_ = std::make_shared<Dataset>(p_dataset);
    net_ = std::make_shared<Net>(dataset_->get_documents_count(),
                                 dataset_->get_flashcards_count());
}

RecSys::~RecSys() {
}

double RecSys::cosine_similarity(torch::Tensor first, torch::Tensor second) {
    double res = 0;

    int size = std::min(first.size(0), second.size(0));

    for (int i = 0; i < size; ++i) {
        res += first.index({i}).item().toDouble()
               * second.index({i}).item().toDouble();
    }
    return res;
}

std::vector<int> RecSys::i2i_predictions(int card_id, int count) {

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
    for (const auto &i: similarity_vec) {
        result.push_back(i.first);
    }
    return result;
}

std::vector<int> RecSys::u2i_predictions(int doc_id, int count) {

    std::vector<std::pair<int, double>> flashcards;
    torch::Tensor interactions = net_->get_doc2card();
    std::vector<int> cards_id = dataset_->get_flashcards();
    std::vector<int> docs_id = dataset_->get_documents();

    if (std::find(docs_id.begin(), docs_id.end(), doc_id) == docs_id.end()) {
        throw("U2I prediction: document id is not found");
    }

    for (int i = 0; i < dataset_->get_flashcards_count(); ++i) {
        std::pair<int, double> temp;
        temp.first = cards_id[i];
        temp.second = interactions.index({docs_id[doc_id], cards_id[i]}).item().toDouble();

        flashcards.push_back(temp);
    }

    std::vector<int> result;
    for (const auto &i: flashcards) {
        result.push_back(i.first);
    }

    std::cout << "Predicted tests before filter\n";
    for (auto i: result) {
        std::cout << i << " ";
    }

    filter(result, doc_id);

    Page page(std::to_string(doc_id), true);
    //save result to db
    for (int i = 0; i < std::min(count, static_cast<int>(result.size())); ++i)
        page.add_one_rec_question_id(std::to_string(result[i]));

    std::cout << "Predicted result\n";
    for (auto i: result) {
        std::cout << i << " ";
    }

    page.page_close_connect();
    return result;
}


const std::vector<int> RecSys::filter(std::vector<int> &flashcards, int doc_id) {
    Page page(std::to_string(doc_id), true);

    //get tests of page
    std::vector<std::vector<std::string>> tests_from_curr_page_str = page.get_all_page_questions_id();
    //get title of page
    std::string title = page.get_page_title();
    std::vector<int> tests_from_curr_page{};

    std::transform(tests_from_curr_page_str.begin(), tests_from_curr_page_str.end(), tests_from_curr_page.begin(), [](std::vector<std::string> test_id){
                return std::stoi(test_id[0]);
            });

    //get tests with curr title
    std::vector<std::vector<std::string>> titles_tests_str = page.get_all_questions_by_theme();
    std::vector<int> titles_tests{};

    std::transform(titles_tests_str.begin(), titles_tests_str.end(),
                   titles_tests.begin(), [](std::vector<std::string> test_id) {
                return std::stoi(test_id[0]);
    });

    //remove test of page
    std::remove_if(flashcards.begin(), flashcards.end(),
                   [flashcards, tests_from_curr_page, titles_tests](int test_id) {
                        return std::find(tests_from_curr_page.begin(), tests_from_curr_page.end(), test_id)
                        != tests_from_curr_page.end() ||
                        std::find(titles_tests.begin(), titles_tests.end(), test_id) != titles_tests.end();
                    });

    auto func = [tests_from_curr_page](std::vector<std::string> test_id){
        return std::stoi(test_id[0]);
    };

    return flashcards;
}

int main() {
    std::vector<int> pages_id_data;
    for (const auto &i: Storage::all_files) {
        Page page(i);
        pages_id_data.push_back(page.get_page_ID());
        page.page_close_connect();
    }

    Dataset data(pages_id_data);
    RecSys recommender(data);
    double loss = recommender.fit();
    std::cout << loss << std::endl;

    for (const auto &i: Storage::all_files) {
        Page page(i);
        recommender.u2i_predictions(page.get_page_ID(), 5);
        page.page_close_connect();
    }
    return 0;
}

