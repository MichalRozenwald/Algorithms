#include<iostream>
#include<vector>

int CountWays(int i, int j,std::vector<std::vector<int>>& data, std::vector<std::vector<int>>& ways) {
  if(i >= data.size() || j >= data[0].size()) {
    return 0;
  }

  if(data[i][j] == 0) {
      ways[i][j] = 0;
      return 0;
  }

  if(ways[i][j] != -1) { return ways[i][j]; }
  if(i == data.size() - 1 && j == data[0].size() - 1) {
    ways[i][j] = 1;
    return 1;
  }

  ways[i][j] = (CountWays(i, j+1, data, ways) + CountWays(i+1, j, data, ways) ) % 268435459;
  return ways[i][j];
}


int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> data;
  for(int i = 0; i < n; i++){
    std::vector<int> line;
    data.push_back(line);
    for(int j = 0; j < m; j++) {
      int square;
      std::cin >> square;
      data[i].push_back(square);
    }
  }

  std::vector<std::vector<int>> ways;
  for(int i = 0; i < n; i++){
    std::vector<int> line;
    ways.push_back(line);
    for(int j = 0; j < m; j++) {
      ways[i].push_back(-1);
    }
  }

  std::cout << CountWays(0, 0, data, ways);

  return 0;
}
