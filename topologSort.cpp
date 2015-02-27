#include<iostream>
#include<vector>
#include<cassert>
#include<algorithm>

typedef std::vector<std::vector<int>> Graph;


std::vector<int> TopSort (const Graph& g) {
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
}

void CheckTopSort(const Graph& g, const std::vector<int>& sorted) {
  assert(TopSort(g) == sorted);
}

void CheckTopSort(const Graph& g) {
  auto sorted = TopSort(g);
  assert(g.size() == sorted.size());

  for(int from = 0; from < sorted.size(); from++) {
    for(int to: g[from]) {
        assert(std::find(sorted.begin(), sorted.end(), from) <
               std::find(sorted.begin(), sorted.end(), to));
    }
  }

  std::sort(sorted.begin(), sorted.end());
  for(int i = 0; i < sorted.size(); i++) {
    assert(i == sorted[i]);
  }

}

Graph GenGraph(int size, int edges) { //edges = кол-во ребер в графе
  std::vector<int> order;
  for(int i = 0; i < size; ++i) order.push_back(i);

  std::random_shuffle(order.begin(), order.end());

  Graph g(size);
  for(int i = 0; i < edges; ++i) {
    int from = rand() % (size - 1);
    int to = rand() % (size - from - 1) + from + 1;
    g[order[from]].push_back(order[to]);
  }
}

void StressTestTopSort() {
  srand(42);
  CheckTopSort(GenGraph(10,25));
}

void TestTopSort() {
  CheckTopSort({}, {});
  CheckTopSort({ {} }, { 0 });
  CheckTopSort({ {}, {} }, { 1, 0 });
  CheckTopSort({ { 1 }, {} }, { 0, 1 });

  CheckTopSort({});
  CheckTopSort({ {} });
  CheckTopSort({ {}, {} });
  CheckTopSort({ { 1 }, {} });
  CheckTopSort({ {3}, {3}, {3}, {} });
  CheckTopSort({ {1}, {2}, {3}, {} });
}

int main() {
}
