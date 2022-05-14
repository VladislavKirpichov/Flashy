#ifndef RECSYS__NET_H_
#define RECSYS__NET_H_

#include <torch/torch.h>
#include <iostream>
#include <vector>

class Net : public torch::nn::Module {
 public:
  Net(int M, int N, int k = 1) {
    if (k == 1) {
      k = (M + N) / 2;
    }
    documents_embeddings = register_parameter("docs_embeddings", torch::randn({M, k}));
    flashcards_embedding = register_parameter("cards_embeddings", torch::randn({k, N}));

    bias_q = register_parameter("bias_q", torch::randn({M,N}));
    bias_p = register_parameter("bias_p", torch::randn({M,N}));
  }

  torch::Tensor forward() {
    doc2card = torch::mm(documents_embeddings, flashcards_embedding);
    doc2card.addmm(bias_q, bias_p);
    doc2card = torch::sigmoid(doc2card);
    return doc2card;
  }

  torch::Tensor doc2card;
  torch::Tensor documents_embeddings;
  torch::Tensor flashcards_embedding;

  torch::Tensor bias_p;
  torch::Tensor bias_q;
};

torch::Tensor train(torch::Tensor input,
                    std::shared_ptr<Net> nn,
                    size_t pEpoch = 1e+3,
                    double learning_rate = 0.5)
{
  torch::optim::Adam nn_optimizers(nn->parameters(),torch::optim::AdamOptions(learning_rate));
  torch::Tensor output;
  torch::Tensor loss;

  for (size_t epoch = 0; epoch < pEpoch; ++epoch) {
    nn->zero_grad();
    output = nn->forward();
    loss = torch::mse_loss(output, input);
    loss.backward();
    nn_optimizers.step();
  }
  return loss;
}

void save_model(std::shared_ptr<Net> nn) {
  std::string model_path = "../serialized/Net.pt";
  torch::serialize::OutputArchive output_archive;
  nn->save(output_archive);
  output_archive.save_to(model_path);
}

void load_model(std::shared_ptr<Net> nn) {
  std::string model_path = "../serialized/Net.pt";
  torch::serialize::InputArchive input_archive;
  input_archive.load_from(model_path);
  nn->load(input_archive);
}

#endif //RECSYS__NET_H_
