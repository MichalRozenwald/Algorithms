#include<iostream>
#include<vector>

int MOD = 268435459;

int CountWays(int i, int j, const std::vector<std::vector<int>>& net, std::vector<std::vector<int>>& ways) {
  if(i >= net.size() || j >= net[0].size()) {
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

  ways[i][j] = (CountWays(i, j+1, net, ways) + CountWays(i+1, j, net, ways) ) % MOD;
  return ways[i][j];
}

void input (std::vector< std::vector<int> >& net) {
  for(int i = 0; i < net.size(); i++){
    for(int j = 0; j < net[0].size(); j++) {
      int square;
      std::cin >> square;
      //net[i].push_back(square);
      net[i][j] = square;
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector< std::vector<int> > net(n, std::vector<int>(m));
  input(net);
  std::vector< std::vector<int> > ways(n, std::vector<int>(m, -1));
  std::cout << CountWays(0, 0, net, ways);

  return 0;
}
