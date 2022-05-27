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

    const torch::Tensor& get_interaction_table() const;

    const size_t get_documents_count() const;

    const size_t get_flashcards_count() const;

    const std::vector<Dataset::Data_t>& get_interactions_data() const;

    const std::vector<size_t> get_documents();

    const std::vector<size_t> get_flashcards();

    Dataset()=default;

    explicit Dataset(torch::Tensor a)
            : interactions_table_(a)
            , documents_id_(a.size(0))
            , flashcards_id_(a.size(1))
    {
        for (size_t i = 0; i < a.size(0); ++i) {
            documents_id_[i] = i;
        }
        for (size_t i = 0; i < a.size(1); ++i) {
            flashcards_id_[i] = i;
        }
    };

    Dataset(const Dataset &other);

    Dataset(Dataset &&other)=delete;

    const Dataset& operator=(const Dataset &other);

    Dataset& operator=(Dataset &&other)=delete;

    ~Dataset()=default;

private:

    std::vector<size_t> documents_id_;

    std::vector<size_t> flashcards_id_;

    std::vector<Data_t> interactions_data_;

    torch::Tensor interactions_table_;

    void preprocessing(); // creates interactions table

    int get_mark(int p_doc_id, int p_card_id);

};

#endif //RECSYS_SOURCE_DATASET_H_