#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> GraphMatrix;

int INF = -1;

int bfsFindShort(const GraphMatrix& g_matrix,
                  int start_x, int start_y, int finish_x, int finish_y) {
  int width = g_matrix[0].size(), height = g_matrix.size();
  GraphMatrix path_length(height, std::vector<int>(width, INF));

  std::vector<std::pair<int,int>> future_set;
  future_set.push_back({start_x, start_y});
  std::vector<std::pair<int,int>> current_set;

  for (int step = 0; !future_set.empty(); step++) {
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
      if(top_x + 1 < height && g_matrix[top_x + 1][top_y] == 0) {
          future_set.push_back({top_x + 1, top_y});
      }
      if(top_y + 1  < width && g_matrix[top_x][top_y + 1] == 0) {
          future_set.push_back({top_x, top_y + 1});
      }
    }
  }
  return path_length[finish_x][finish_y];
}

GraphMatrix input_g_matrix(int width, int height){
  GraphMatrix g_matrix(width, std::vector<int>(height));
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      std::cin >> g_matrix[i][j];
    }
  }
  return g_matrix;
}

int main() {
  int width, height;
  std::cin >> width >> height;

  int start_x, start_y;
  std::cin >> start_x >> start_y;
  start_x--;
  start_y--;
  int finish_x, finish_y;
  std::cin >> finish_x >> finish_y;
  finish_x--;
  finish_y--;

  GraphMatrix g_matrix = input_g_matrix(width, height);

  int result = bfsFindShort(g_matrix, start_x, start_y, finish_x, finish_y);
  if(result > -1) { std::cout << result; }
  else { std::cout << "NO"; }

  return 0;
}
