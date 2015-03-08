#include<iostream>
#include<vector>
#include<cassert>
#include<algorithm>

typedef std::vector<std::vector<int>> Graph;

std::vector<int> TopSort(const Graph& g) {
  std::vector<int> inDegree(g.size(), 0);
  for(const std::vector<int>& neighbours : g) {
    for(int neighbour: neighbours) {
      inDegree[neighbour]++;
    }
  }
  std::vector<int> sorted, roots;
  for(int vertex = 0; vertex < g.size(); ++vertex) {
    if(inDegree[vertex] == 0) {
      roots.push_back(vertex);
    }
  }
  while(!roots.empty()) {
    int v = roots.back();
    roots.pop_back();
    sorted.push_back(v);
    for(int neighbour : g[v]) {
      --inDegree[neighbour];
      if(inDegree[neighbour] == 0) {
        roots.push_back(neighbour);
      }
    }
  }
  for(int vertex_deg : inDegree){
    if(vertex_deg != 0){
        std::vector<int> cycled = {0};
        return cycled;
    }
  }
  return sorted;
}


void NotCrossed(int s1, int s2, Graph& g) {
  g[2*(s1-1)].push_back(2*(s1-1) + 1);
  g[2*(s1-1) + 1].push_back(2*(s2-1));
  g[2*(s2-1)].push_back(2*(s2-1)+1);
}

void Crossed(int s1, int s2, Graph& g) {
  g[2*(s1-1)].push_back(2*(s1-1) + 1);
  g[2*(s2-1)].push_back(2*(s1-1) + 1);
  g[2*(s1-1)].push_back(2*(s2-1) + 1);
  g[2*(s2-1)].push_back(2*(s2-1) + 1);
}

int main() {
  int n, a, b;
  std::cin >> n >> a >> b;
  Graph my_graph(2 * n);

  for (int pair_a = 0; pair_a < a; pair_a++){
    int segm1, segm2;
    std::cin >> segm1 >> segm2;
    NotCrossed(segm1, segm2, my_graph);
  }
  for (int pair_b = 0; pair_b < b; pair_b++){
    int segm1, segm2;
    std::cin >> segm1 >> segm2;
    Crossed(segm1, segm2, my_graph);
  }
  std::vector<int> result = TopSort(my_graph);

  if (result.size() < n) {
    std::cout << "Impossible";
  }
  else {
    std::vector<int> coordin(result.size());
    for (int i = 0; i < result.size(); ++i) {
      coordin[result[i]] = i;
    }
    for (int i = 0; i < result.size(); i += 2) {
      std::cout << coordin[i] << " " << coordin[i + 1] << std::endl;

    }
  }
}
