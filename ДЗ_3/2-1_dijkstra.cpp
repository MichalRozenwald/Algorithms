#include <vector>
#include <iostream>
#include <queue>


struct Edge {
    int to, length, from;
};

struct Candidate {
    int index, distance;
    bool operator < (const Candidate& rsh) const {
        return distance > rsh.distance;
    }
};

const int Inf_Distance = -1;

Edge FarestByDijkstra(const std::vector< std::vector<Edge> >& g, int& start) {
    std::priority_queue <Candidate> candidates;
    std::vector<int> distances(g.size(), Inf_Distance);
    Candidate first;
    first.index = start;
    first.distance = 0;
    candidates.push(first);
    while (!candidates.empty()) {
        Candidate best = candidates.top();
        candidates.pop();

        if (distances[best.index] != Inf_Distance) continue;
        distances[best.index] = best.distance;

		    for (Edge e : g[best.index]) {
            Candidate next;
            next.index = e.to;
            next.distance = best.distance + e.length;
            candidates.push(next);
        }
    }
    Edge farest_dist;
    farest_dist.length = 0;
    for(int vertex = 0; vertex < distances.size(); vertex++){
        if(farest_dist.length < distances[vertex]) {
            farest_dist.length = distances[vertex];
            farest_dist.to = vertex;
        }
    }
    farest_dist.from = start;
    return farest_dist;
}

void FarestWays (const std::vector< std::vector<Edge> >& town, int& num_stops) {
    std::vector<Edge> all_farest_stops(num_stops);
    int farest_dist = -1;
    for(int cur_stop = 0; cur_stop < num_stops; cur_stop++) {
        Edge cur_farest = FarestByDijkstra(town, cur_stop);
        all_farest_stops[cur_stop] = cur_farest;
        if(all_farest_stops[cur_stop].length > farest_dist) {
            farest_dist = all_farest_stops[cur_stop].length;
        }
    }
    std::cout << farest_dist << std::endl;
    for(int cur_stop = 0; cur_stop < num_stops; cur_stop++) {
        if(all_farest_stops[cur_stop].length == farest_dist) {
            std::cout << all_farest_stops[cur_stop].from + 1 << " " << all_farest_stops[cur_stop].to + 1 << std::endl;
        }
    }
}

std::vector< std::vector<Edge> > Input (int& num_stops) {
    std::cin >> num_stops;
    std::vector<Edge> road;
    std::vector< std::vector<Edge> > town(num_stops, road);
    for(int stop = 0; stop < num_stops; stop++) {
        int num_neighbors;
        std::cin >> num_neighbors;
        for(int neighbor = 0; neighbor < num_neighbors; neighbor++) {
            int cur_dist, cur_neighb_stop;
            std::cin >> cur_dist >> cur_neighb_stop;
            Edge near;
            near.length = cur_dist;
            near.to = cur_neighb_stop - 1;
            town[stop].push_back(near);
        }
    }
    return town;
}

int main() {
    int num_stops;
    std::vector< std::vector<Edge> > roads = Input(num_stops);
    FarestWays(roads, num_stops);
    return 0;
}
