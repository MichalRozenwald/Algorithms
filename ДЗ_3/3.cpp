#include <iostream>
#include <algorithm>
#include <vector>

struct Experiment {
  long int download, counting;

  bool operator < (const Experiment& other) const {
    return counting > other.counting;
  }
};

long int MinTime(std::vector<Experiment>& all_exps) {
  long int result_time = 0, download_time = 0;
  std::sort(all_exps.begin(), all_exps.end());

  for (size_t file = 0; file < all_exps.size(); file++) {
    Experiment cur_exp = all_exps[file];
    result_time = std::max(result_time, download_time + cur_exp.download + cur_exp.counting);
    download_time += cur_exp.download;
  }

  return result_time;
}

std::vector<Experiment> Input() {
  int num_experiments;
  std::cin >> num_experiments;

  std::vector<Experiment> all_exp(num_experiments);
  for(size_t file = 0; file < num_experiments; file++) {
    Experiment new_exp;
    std::cin >> new_exp.download >> new_exp.counting ;
    all_exp[file] = new_exp;
  }
  return all_exp;
}

main() {

  std::vector<Experiment> all_experiments = Input();
  std::cout << MinTime(all_experiments);

  return 0;
}
