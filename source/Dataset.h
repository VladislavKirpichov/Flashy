#ifndef RECSYS_SOURCE_DATASET_H_
#define RECSYS_SOURCE_DATASET_H_

#include <iostream>
#include <vector>
#include <torch/torch.h>

class Dataset {

 public:

  struct Data_t {
    int doc_id;
    int card_id;
    int mark;
  };

  const torch::Tensor& get_interaction_table() const;

  const int get_documents_count() const;

  const int get_flashcards_count() const;

  const std::vector<Dataset::Data_t>& get_interactions_data() const;

  const std::vector<int> get_documents() const;

  const std::vector<int> get_flashcards() const;

  Dataset(const std::vector<int> &pages);

  explicit Dataset(torch::Tensor a)
      : interactions_table_(a)
      , documents_id_(a.size(0))
      , flashcards_id_(a.size(1))
  {
    for (int i = 0; i < a.size(0); ++i) {
      documents_id_[i] = i;
    }
    for (int i = 0; i < a.size(1); ++i) {
      flashcards_id_[i] = i;
    }
  };

  Dataset(const Dataset &other);

  Dataset(Dataset &&other)=delete;

  const Dataset& operator=(const Dataset &other);

  Dataset& operator=(Dataset &&other)=delete;

  ~Dataset()=default;

 private:

  std::vector<int> documents_id_;

  std::vector<int> flashcards_id_;

  std::vector<Data_t> interactions_data_;

  torch::Tensor interactions_table_;

  void preprocessing();

  int get_mark(int p_doc_id, int p_card_id);

};

#endif //RECSYS_SOURCE_DATASET_H_