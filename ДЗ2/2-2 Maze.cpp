#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> GraphMatrix;

int bfsFindShort(const GraphMatrix& g_matrix,
                  int start_b, int start_e, int finish_b, int finish_e) {
  int INF = -1;
  GraphMatrix way_length;
  for (int i = 0; i < g_matrix.size(); i++) {
    std::vector<int> line(g_matrix[0].size(), INF);
    way_length.push_back(line);
  }
  int step = 0;

  std::vector<std::pair<int,int>> future_set;
  future_set.push_back({start_b, start_e});
  std::vector<std::pair<int,int>> current_set;

  while (!future_set.empty()) {
    current_set = future_set;
    future_set.clear();
    while(!current_set.empty()) {
      std::pair<int, int> front = current_set.back();
      current_set.pop_back();

      if(way_length[front.first][front.second] != -1) { continue; }

      way_length[front.first][front.second] = step;

      if(front.first - 1 > -1) {
        if (g_matrix[front.first - 1][front.second] == 0) {
          future_set.push_back({front.first - 1, front.second});
        }
      }
      if(front.second - 1 > -1) {
        if (g_matrix[front.first][front.second - 1] == 0) {
          future_set.push_back({front.first, front.second - 1});
        }
      }
      if(front.first + 1 < g_matrix.size()) {
        if (g_matrix[front.first + 1][front.second] == 0) {
          future_set.push_back({front.first + 1, front.second});
        }
      }
      if(front.second + 1  < g_matrix[0].size()) {
        if (g_matrix[front.first][front.second + 1] == 0) {
          future_set.push_back({front.first, front.second + 1});
        }
      }
    }
    step++;
    }
  return way_length[finish_b][finish_e];
}

int main() {
  int m, n;
  std::cin >> m >> n;

  int start_b, start_e;
  std::cin >> start_b >> start_e;
  start_b--;
  start_e--;
  int finish_b, finish_e;
  std::cin >> finish_b >> finish_e;
  finish_b--;
  finish_e--;

  GraphMatrix g_matrix;
  for (int i = 0; i < m; i++) {
    std::vector<int> line(n, 0);
    g_matrix.push_back(line);
    for (int j = 0; j < n; j++) {
      int value;
      std::cin >> value;
      g_matrix[i][j] = value;
    }
  }

  int result = bfsFindShort(g_matrix, start_b, start_e, finish_b, finish_e);
  if(result > -1) {
      std::cout << result;
  } else { std::cout << "NO";}

  return 0;
}
