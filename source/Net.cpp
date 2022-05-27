#include "Net.h"

Net::Net(int M, int N, int k) {
  if (k == -1) {
    k = (M + N) / 2;
  }

  documents_embeddings = register_parameter("docs_embeddings", torch::randn({M, k}));
  flashcards_embedding = register_parameter("cards_embeddings", torch::randn({k, N}));

  bias_q = register_parameter("bias_q", torch::randn({M,N}));
  bias_p = register_parameter("bias_p", torch::randn({M,N}));
}

torch::Tensor Net::forward() {
  doc2card = torch::mm(documents_embeddings, flashcards_embedding);
  doc2card.addmm(bias_q, bias_p);

  doc2card = torch::sigmoid(doc2card);
  return doc2card;
}

void Net::save_model() {
  std::string model_path = "../serialized/Net.pt";
  torch::serialize::OutputArchive output_archive;
  this->save(output_archive);
  output_archive.save_to(model_path);
}

void Net::load_model() {
  // TODO: exceptions if file is not found
  std::string model_path = "../serialized/Net.pt";
  torch::serialize::InputArchive input_archive;
  input_archive.load_from(model_path);
  this->load(input_archive);
}

torch::Tensor Net::train(torch::Tensor input, size_t pEpoch,
                    double learning_rate)
{
  torch::optim::Adam nn_optimizers(this->parameters(),
                                   torch::optim::AdamOptions(learning_rate));
  torch::Tensor output;
  torch::Tensor loss;

  for (size_t epoch = 0; epoch < pEpoch; ++epoch) {
    this->zero_grad();
    output = this->forward();
    loss = torch::mse_loss(output, input);

    loss.backward();
    nn_optimizers.step();
  }

  return loss;
}

const torch::Tensor Net::get_doc2card() const {
  return doc2card;
}

const torch::Tensor Net::get_documents_embeddings() const {
  return documents_embeddings;
}

const torch::Tensor Net::get_flashcards_embeddings() const {
  return flashcards_embedding;
}

