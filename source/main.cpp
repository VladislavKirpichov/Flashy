#include <torch/torch.h>
#include "Net.h"
#include "RecSys.h"
#include "Dataset.h"


int main() {
  std::vector<int> pages_id_data;
  for (const auto &i: Storage::all_files) {
    Page page(i);
    pages_id_data.push_back(page.get_page_ID());
    page.page_close_connect();
  }

  Dataset data(pages_id_data);
  RecSys<Net> recommender(data);
  double loss = recommender.fit();
  std::cout << loss << std::endl;

  for (const auto &i: Storage::all_files) {
    Page page(i);
    recommender.u2i_predictions(page.get_page_ID(), 5);
    page.page_close_connect();
  }
  return 0;
}


