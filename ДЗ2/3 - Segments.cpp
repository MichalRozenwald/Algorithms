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
  std::vector<int> sorted, sources;
  for(int vertex = 0; vertex < g.size(); ++vertex) {
    if(inDegree[vertex] == 0) {
      sources.push_back(vertex);
    }
  }
  while(!sources.empty()) {
    int v = sources.back();
    sources.pop_back();
    sorted.push_back(v);
    for(int neighbour : g[v]) {
      --inDegree[neighbour];
      if(inDegree[neighbour] == 0) {
        sources.push_back(neighbour);
      }
    }
  }
  for(int vertex_deg : inDegree){
    if(vertex_deg != 0){
        return {0};
    }
  }
  return sorted;
}


void AddFollowing(int s1, int s2, Graph& g) {
  int segment1_start = 2*(s1-1), segment1_end = 2*(s1-1) + 1;
  int segment2_start = 2*(s2-1), segment2_end = 2*(s2-1) + 1;
  g[segment1_start].push_back(segment1_end);
  g[segment1_end].push_back(segment2_start);
  g[segment2_start].push_back(segment2_end);
}

void AddIntersecting(int s1, int s2, Graph& g) {
  int segment1_start = 2*(s1-1), segment1_end = 2*(s1-1) + 1;
  int segment2_start = 2*(s2-1), segment2_end = 2*(s2-1) + 1;
  g[segment1_start].push_back(segment1_end);
  g[segment2_start].push_back(segment1_end);
  g[segment1_start].push_back(segment2_end);
  g[segment2_start].push_back(segment2_end);
}

Graph input() {
  int num_of_segm, following, intersecting;
  std::cin >> num_of_segm >> following >> intersecting;
  Graph my_graph(2 * num_of_segm);

  for (int fol_pair = 0; fol_pair < following; fol_pair++){
    int segm1, segm2;
    std::cin >> segm1 >> segm2;
    AddFollowing(segm1, segm2, my_graph);
  }
  for (int inter_pair = 0; inter_pair < intersecting; inter_pair++){
    int segm1, segm2;
    std::cin >> segm1 >> segm2;
    AddIntersecting(segm1, segm2, my_graph);
  }
  return my_graph;
}

void output(std::vector<int>& sorted_indexes) {
  std::vector<int> coordin(sorted_indexes.size());
  for (int i = 0; i < sorted_indexes.size(); ++i) {
    coordin[sorted_indexes[i]] = i;
  }
  for (int i = 0; i < sorted_indexes.size(); i += 2) {
    std::cout << coordin[i] << " " << coordin[i + 1] << std::endl;
  }
}

int main() {
  Graph my_graph = input();
  std::vector<int> sorted_indexes = TopSort(my_graph);
  if (sorted_indexes.size() < my_graph.size() / 2) { std::cout << "Impossible"; }
  else { output(sorted_indexes); }

  return 0;
}
