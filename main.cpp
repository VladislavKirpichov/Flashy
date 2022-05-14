#include <torch/torch.h>
#include "source/Net.h"
#include "source/RecSys.h"
#include "source/Dataset.h"

int main() {

  torch::Tensor matrix = torch::rand({5,5});
  auto dataset = std::make_shared<Dataset>(matrix);
  RecSys<Net> model;
  model.fit(dataset);


}
