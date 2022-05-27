#ifndef RECSYS__NET_H_
#define RECSYS__NET_H_

#include <torch/torch.h>
#include <iostream>
#include <vector>

class Net : public torch::nn::Module {
public:

    // M - documents count
    // N - flashcards count
    Net(int M, int N, int k = -1);

    void save_model();

    void load_model();

    torch::Tensor train(torch::Tensor input, size_t pEpoch = 1e3,
                        double learning_rate = 0.5);

    const torch::Tensor get_doc2card() const;

    const torch::Tensor get_documents_embeddings() const;

    const torch::Tensor get_flashcards_embeddings() const;

private:

    torch::Tensor forward();

    torch::Tensor doc2card;
    torch::Tensor documents_embeddings;
    torch::Tensor flashcards_embedding;

    torch::Tensor bias_p;
    torch::Tensor bias_q;
};


#endif //RECSYS__NET_H_