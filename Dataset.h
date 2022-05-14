#ifndef RECSYS_SOURCE_DATASET_H_
#define RECSYS_SOURCE_DATASET_H_

#include <iostream>
#include <vector>
#include <torch/torch.h>

class Dataset {
 public:

  struct Data_t{
    size_t doc_id;
    size_t card_id;
    int mark;
  };

 private:

  std::vector<size_t> documents_id_;
  std::vector<size_t> flashcards_id_;
  std::vector<Data_t> iteractions_data_;

  void preprocessing();

  torch::Tensor iteractions_table_;

 public:

  const torch::Tensor& get_iteraction_table() const;
  const size_t get_documents_count() const;
  const size_t get_flashcards_count() const;
  const std::vector<Dataset::Data_t>& get_iteractions_data() const;
  const std::vector<Dataset>& train_test_split();

  Dataset();
  explicit Dataset(torch::Tensor a); //test
  Dataset(const Dataset &other)=delete;
  Dataset(Dataset &&other)=delete;
  Dataset& operator=(const Dataset &other)=delete;
  Dataset& operator=(Dataset &&other)=delete;
  ~Dataset();
};

#endif //RECSYS_SOURCE_DATASET_H_
