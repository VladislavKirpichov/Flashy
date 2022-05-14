#include "Dataset.h"

void Dataset::preprocessing() {

}

Dataset::Dataset() {

}

Dataset::~Dataset() {

}

const std::vector<Dataset> &Dataset::train_test_split() {

  return std::vector<Dataset>();
}

const torch::Tensor &Dataset::get_iteraction_table() const {
  return iteractions_table_;
}
const size_t Dataset::get_documents_count() const {
  return documents_id_.size();
}
const size_t Dataset::get_flashcards_count() const {
  return flashcards_id_.size();
}
const std::vector<Dataset::Data_t> &Dataset::get_iteractions_data() const {
  return iteractions_data_;
}

Dataset::Dataset(torch::Tensor a)
: iteractions_table_(a)
{

}
