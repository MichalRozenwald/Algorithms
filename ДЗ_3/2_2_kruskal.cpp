#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
  int first, second, weight;

  bool operator < (const Edge& other) const {
    return weight < other.weight;
  }
};

class DSU { //объединение непер. множеств
public:
  DSU(size_t size){
    for(int i = 0; i < size; ++i) parent_.push_back(i);
  }
  int getComponents(int element) {
    if (parent_[element] == element) {
      return element;
    }
    parent_[element] = getComponents(parent_[element]);
    return parent_[element];
  }
  void joinCompanent(int first, int second) {
    int firstRoot = getComponents(first);
    int secondRoot = getComponents(second);

    if(rand() & 1) {
      parent_[firstRoot] = secondRoot;
    }else {
      parent_[secondRoot] = firstRoot;
    }
  }

private:
  std::vector<int> parent_;
};


int FindMinCost(std::vector<Edge>& graph, int num_towns) {
  int result = 0;

  std::sort(graph.begin(), graph.end());

  DSU dsu(num_towns);
   for (size_t edge = 0; edge < graph.size(); edge++) {
    Edge e = graph[edge];
    if(dsu.getComponents(e.first) != dsu.getComponents(e.second)) {
      dsu.joinCompanent(e.first, e.second);
      result += e.weight;
    }
  }

  return result;
}

std::vector<Edge> Input(int num_towns, int roads, int connected) {
  std::vector<Edge> graph(connected - 1);
  for (size_t vertex = 0; vertex < connected - 1; vertex++) { //connect the towns, whicj has storages
    graph[vertex].first = vertex;
    graph[vertex].second = vertex + 1;
    graph[vertex].weight = 0;
  }
  for(size_t road = 0; road < 2 * roads; road++) {
    int start, finish, payment;
    std::cin >> start >> finish >> payment;
    if(start < finish) {
      Edge new_e;
      new_e.first = start - 1;
      new_e.second = finish - 1;
      new_e.weight = payment;
      graph.push_back(new_e);
    }
  }
  return graph;
}

main() {
  int num_towns, roads, connected;
  std::cin >> num_towns >> roads >> connected;

  std::vector<Edge> graph = Input(num_towns, roads, connected);
  std::cout << FindMinCost(graph, num_towns);

  return 0;
}
