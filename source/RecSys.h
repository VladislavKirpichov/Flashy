#ifndef RECSYS__RECSYS_H_
#define RECSYS__RECSYS_H_

#include "Net.h"
#include "Dataset.h"
#include <unordered_map>
#include <algorithm>

class RecSys {

  std::shared_ptr<Net> net_;

  std::shared_ptr<Dataset> dataset_;

  std::unordered_map<int, torch::Tensor> flashcard_embeddings_;

  std::unordered_map<int, torch::Tensor> document_embeddings_;

  void save_cards_embeddings(const torch::Tensor &p_interactions,
                             std::shared_ptr<Dataset> p_dataset);

  void save_docs_embeddings(const torch::Tensor &p_interactions,
                             std::shared_ptr<Dataset> p_dataset);

  double eval_loss(const torch::Tensor &output,
                   std::shared_ptr<Dataset> p_dataset);

  const std::vector<int> generate_k_grid(int M, int N);

  const std::vector<double> generate_lr_grid(int count);

  double cosine_similarity(torch::Tensor first, torch::Tensor second);

  const std::vector<int> filter(const std::vector<int> &flashcards, int doc_id);

 public:

  RecSys(const Dataset &p_dataset);

  RecSys(const RecSys<Net> &other) = delete;

  RecSys(RecSys<Net> &&other) = delete;

  RecSys& operator=(const RecSys<Net> &other) = delete;

  RecSys& operator=(RecSys<Net> &&other) = delete;

  ~RecSys();

  double fit();

  std::vector<int> i2i_predictions(int card_id, int count);

  std::vector<int> u2i_predictions(int doc_id, int count);

};


#endif //RECSYS__RECSYS_H_
