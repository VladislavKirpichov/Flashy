#ifndef RECSYS__RECSYS_H_
#define RECSYS__RECSYS_H_

#include "Net.h"
#include "Dataset.h"

template<class Net>
class RecSys {

  std::shared_ptr<Net> net_;
  std::shared_ptr<Dataset> dataset_;

  void evaluate();
  double eval_loss(const torch::Tensor &output,
                   std::shared_ptr<Dataset> p_dataset);
  const std::vector<int> generate_k_grid(size_t M, size_t N);
  const std::vector<double> generate_lr_grid();

 public:

  RecSys();
  RecSys(const RecSys<Net> &other) = delete;
  RecSys(RecSys<Net> &&other) = delete;
  RecSys& operator=(const RecSys<Net> &other) = delete;
  RecSys& operator=(RecSys<Net> &&other) = delete;
  ~RecSys();

  double fit(std::shared_ptr<Dataset> p_dataset);
  void predict();

  void predict_new_data();
};

#endif //RECSYS__RECSYS_H_
