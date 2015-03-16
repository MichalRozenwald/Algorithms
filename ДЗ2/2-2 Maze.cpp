#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> GraphMatrix;

int bfsFindShort(const GraphMatrix& g_matrix,
                  int start_x, int start_y, int finish_x, int finish_y) {
  int INF = -1;
  GraphMatrix path_length;
  for (int i = 0; i < g_matrix.size(); i++) {
    std::vector<int> line(g_matrix[0].size(), INF);
    path_length.push_back(line);
  }
  int step = 0;

  std::vector<std::pair<int,int>> future_set;
  future_set.push_back({start_x, start_y});
  std::vector<std::pair<int,int>> current_set;

  while (!future_set.empty()) {
    current_set = future_set;
    future_set.clear();
    while(!current_set.empty()) {
      std::pair<int, int> top = current_set.back();
      current_set.pop_back();
      int top_x = top.first;
      int top_y = top.second;

      if(path_length[top_x][top_y] != -1) { continue; }

      path_length[top_x][top_y] = step;

      if(top_x - 1 > -1 && g_matrix[top_x - 1][top_y] == 0) {
          future_set.push_back({top_x - 1, top_y});
      }
      if(top_y - 1 > -1 && g_matrix[top_x][top_y - 1] == 0) {
          future_set.push_back({top_x, top_y - 1});
      }
      if(top_x + 1 < g_matrix.size() && g_matrix[top_x + 1][top_y] == 0) {
          future_set.push_back({top_x + 1, top_y});
      }
      if(top_y + 1  < g_matrix[0].size() && g_matrix[top_x][top_y + 1] == 0) {
          future_set.push_back({top_x, top_y + 1});
      }
    }
    step++;
    }
  return path_length[finish_x][finish_y];
}

GraphMatrix input_g_matrix(int m, int n){
  GraphMatrix g_matrix(m, std::vector<int>(n));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      int value;
      std::cin >> value;
      g_matrix[i][j] = value;
    }
  }
  return g_matrix;
}

int main() {
  int m, n;
  std::cin >> m >> n;

  int start_x, start_y;
  std::cin >> start_x >> start_y;
  start_x--;
  start_y--;
  int finish_x, finish_y;
  std::cin >> finish_x >> finish_y;
  finish_x--;
  finish_y--;

  GraphMatrix g_matrix = input_g_matrix(m, n);

  int result = bfsFindShort(g_matrix, start_x, start_y, finish_x, finish_y);
  if(result > -1) { std::cout << result; }
  else { std::cout << "NO"; }

  return 0;
}
