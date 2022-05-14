#include "RecSys.h"

template<class Net>
double RecSys<Net>::fit(std::shared_ptr<Dataset> p_dataset) {
  //optimize hyperparameters:
  //learning rate
  //k - tensor shape

  //Define matrix shape
  size_t docs_count = p_dataset->get_documents_count();
  size_t cards_count = p_dataset->get_flashcards_count();

  //fill random numbers in some range
  std::vector<size_t> k_grid = generate_k_grid(docs_count, cards_count);

  //fill random numbers in some range
  std::vector<double> learning_rate_grid = generate_lr_grid();

  //Define best parameters
  double best_loss;
  size_t best_k;
  double best_lr;

  //multithread
  for (const size_t k_iter: k_grid) {
    for (const double lr_iter: learning_rate_grid) {
      auto net = std::make_shared<Net>(docs_count, cards_count, k_grid);
      torch::Tensor output = train(p_dataset->get_iteraction_table(), net, 1e+3, lr_iter);
      double loss = eval_loss(output, p_dataset);

      std::cout << "Model {lr = " << lr_iter << ", k = " << k_iter << "}"
       << "\nLoss: " << loss << std::endl;

      if (loss < best_loss) {
        best_loss = loss;
        best_k = k_iter;
        best_lr = lr_iter;
      }
    }
  }

  std::cout << "Best loss:" << best_loss
  << "\nBest k:" << best_k
  << "\nBest learning rate" << best_lr << std::endl;

  //Training best model
  net_ = std::make_shared<Net>(docs_count, cards_count, best_k);
  train(p_dataset->get_iteraction_table(), net_, 1e+3, best_lr);
  save_model(net_);
}

template<class Net>
const std::vector<int> RecSys<Net>::generate_k_grid(size_t M, size_t N) {
  std::vector<int> grid;
  //
  return grid;
}

template<class Net>
const std::vector<double> RecSys<Net>::generate_lr_grid() {
  std::vector<double> grid;
  //
  return grid;
}

template<class Net>
double RecSys<Net>::eval_loss(const torch::Tensor &output,
                                       std::shared_ptr<Dataset> p_dataset) {
  double loss = 0;
  for (const auto& i: p_dataset->get_iteractions_data()) {
    loss += (output[i.card_id][i.doc_id].item().to<double>() - i.mark);
  }
  return loss;
}

template<class Net>
void RecSys<Net>::evaluate() {

}

template<class Net>
RecSys<Net>::RecSys() {
  //
  load_model(net_);
  //
}

template<class Net>
RecSys<Net>::~RecSys() {
  //
  save_model(net_);
  //
}

template<class Net>
void RecSys<Net>::predict() {

}

template<class Net>
void RecSys<Net>::predict_new_data() {

}

