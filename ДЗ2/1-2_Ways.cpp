#include<iostream>
#include<vector>

int MOD = 268435459;

int CountWays(int i, int j, const std::vector<std::vector<int> >& net, std::vector<std::vector<int> >& ways, int step) {
  if (step == 0) {
    for (size_t i = 0; i < ways.size(); ++i) {
      for (size_t j = 0; j < ways[0].size(); ++j){
        ways[i][j] = -1;
      }
    }
    step++;
  }
  //if (ways.empty()) {ways.resize(net.size(), std::vector<int>(net[0].size(), -1));}
  if (i >= net.size() || j >= net[0].size()) {
    return 0;
  }

  if(net[i][j] == 0) {
      ways[i][j] = 0;
      return 0;
  }

  if(ways[i][j] != -1) { return ways[i][j]; }
  if(i == net.size() - 1 && j == net[0].size() - 1) {
    ways[i][j] = 1;
    return 1;
  }

  ways[i][j] = (CountWays(i, j+1, net, ways, 1) + CountWays(i+1, j, net, ways, 1) ) % MOD;
  return ways[i][j];
}

std::vector< std::vector<int> > input () {
   int n, m;
  std::cin >> n >> m;
  std::vector< std::vector<int> > net(n, std::vector<int>(m));
  for(int i = 0; i < net.size(); i++){
    for(int j = 0; j < net[0].size(); j++) {
      int square;
      std::cin >> square;
      net[i][j] = square;
    }
  }
  return net;
}

int main() {
  std::vector< std::vector<int> > net = input();
  int step = 0;
  std::cout << CountWays(0, 0, net, net, step);

  return 0;
}
