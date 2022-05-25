#ifndef RECSYS_SOURCE_DATASET_H_
#define RECSYS_SOURCE_DATASET_H_

#include <iostream>
#include <vector>
#include <torch/torch.h>

class Dataset {

 public:

  struct Data_t {
    size_t doc_id;
    size_t card_id;
    int mark;
  };

 private:

  std::vector<size_t> documents_id_;

  std::vector<size_t> flashcards_id_;

  std::vector<Data_t> interactions_data_;

  torch::Tensor interactions_table_;

  void preprocessing(); // creates interactions table

 public:

  const torch::Tensor& get_interaction_table() const;

  const size_t get_documents_count() const;

  const size_t get_flashcards_count() const;

  const std::vector<Dataset::Data_t>& get_interactions_data() const;

  const std::vector<size_t> get_documents();

  const std::vector<size_t> get_flashcards();

  Dataset();

  Dataset(torch::Tensor a); //test

  Dataset(const Dataset &other);

  Dataset(Dataset &&other)=delete;

  const Dataset& operator=(const Dataset &other);

  Dataset& operator=(Dataset &&other)=delete;

  ~Dataset();
};

#endif //RECSYS_SOURCE_DATASET_H_
