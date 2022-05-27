#include <torch/torch.h>
#include "Net.h"
#include "RecSys.h"
#include "Dataset.h"



int main() {

  torch::Tensor interactions = torch::rand({3,3});
  Dataset data(interactions);
  RecSys<Net> recommender(data);
  double loss = recommender.fit();
//  recommender.u2i_predict(id_dock, 5);
  return 0;
}


