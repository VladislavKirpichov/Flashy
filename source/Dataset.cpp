#include "Dataset.h"


void Dataset::preprocessing() {

 interactions_table_ = torch::zeros({static_cast<int>(get_documents_count()),
                                     static_cast<int>(get_flashcards_count())});

 for (const Data_t &i: interactions_data_) {
   interactions_table_.index_put_({static_cast<int>(i.doc_id),
                                   static_cast<int>(i.card_id)}, i.mark);
 }

}


const torch::Tensor &Dataset::get_interaction_table() const {
  return interactions_table_;
}

const size_t Dataset::get_documents_count() const {
  return documents_id_.size();
}

const size_t Dataset::get_flashcards_count() const {
  return flashcards_id_.size();
}

const std::vector<Dataset::Data_t> &Dataset::get_interactions_data() const {
  return interactions_data_;
}

Dataset::Dataset(torch::Tensor a)
: interactions_table_(a)
{

}

const std::vector<size_t> Dataset::get_documents() {
  return documents_id_;
}

const std::vector<size_t> Dataset::get_flashcards() {
  return flashcards_id_;
}

Dataset::Dataset(const Dataset &other)
: documents_id_(other.documents_id_)
, flashcards_id_(other.flashcards_id_)
, interactions_data_(other.interactions_data_)
, interactions_table_(other.interactions_table_)
{
}

//TODO
const Dataset &Dataset::operator=(const Dataset &other) {
  documents_id_ = other.documents_id_;
  flashcards_id_ = other.flashcards_id_;
  interactions_data_ = other.interactions_data_;
  interactions_table_ = other.interactions_table_;
  return (*this);
}

Dataset::Dataset() {

}

Dataset::~Dataset() {

}
