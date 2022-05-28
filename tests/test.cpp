#include "gtest/gtest.h"
#include "../src/RecSys.h"

////NET
//TEST(Net, save_load) {
//  //saving and loading net
////  auto nn = std::make_shared<Net>(5, 5);
////  //save net's tensor
////  torch::Tensor docs = nn->documents_embeddings;
////  torch::Tensor cards = nn->flashcards_embedding;
////
////  save_model(nn);
////  load_model(nn);
////
////  //checking tensor's equality
////  EXPECT_EQ(docs, nn->documents_embeddings);
////  EXPECT_EQ(cards, nn->flashcards_embedding);
//}
//
//TEST(Net, train) {
//
////  int size = 10000;
////  double learning_rate = 0.5;
////  size_t pEpoch = 1e3;
////  auto nn = std::make_shared<Net>(size, size);
////
////  torch::optim::Adam nn_optimizers(nn->parameters(),
////                                   torch::optim::AdamOptions(learning_rate));
////
////  torch::Tensor input = torch::rand({size,size});
////  torch::Tensor output;
////  torch::Tensor loss;
////
////  std::cout << input << std::endl;
////
////  srand(time(nullptr));
////  const std::chrono::time_point<std::chrono::steady_clock> start_fit =
////      std::chrono::steady_clock::now();
////  for (size_t epoch = 0; epoch < pEpoch; ++epoch) {
////    nn->zero_grad();
////    output = nn->forward();
////    loss = torch::mse_loss(output, input);
////    loss.backward();
////    nn_optimizers.step();
////  }
////  std::cout << output << std::endl;
//
//}

//RECOMMENDER SYSTEM
TEST(RecSys, test) {
  int size = 10;
  torch::Tensor a = torch::rand({size, size});
  Dataset data(a);
//  RecSys<Net> recommender(data);
//  recommender.fit();
}

TEST(RecSys, fit) {
  torch::Tensor interactions = torch::rand({3,3});
  Dataset data(interactions);
  Dataset d(data);
//  RecSys<Net> recommender(data);
//  double loss = recommender.fit();
//  for (const int i: recommender.i2i_predictions(0,2)) {
//    std::cout << i << std::endl;
//  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}