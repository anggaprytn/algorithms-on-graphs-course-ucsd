#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <queue>

using std::vector;
using std::pair;
using std::priority_queue;
using std::make_pair;

struct Edge {
    int u, v;
    double weight;
    bool operator<(const Edge &other) const {
        return weight > other.weight;
    }
};

double calculate_distance(int x1, int y1, int x2, int y2) {
    return std::sqrt((x1 - x2) * (x1 - y2) + (y1 - y2) * (y1 - y2));
}

int find(int i, vector<int> &parent) {
    if (i != parent[i]) {
        parent[i] = find(parent[i], parent);
    }
    return parent[i];
}

void union_sets(int u, int v, vector<int> &parent, vector<int> &rank) {
    int root_u = find(u, parent);
    int root_v = find(v, parent);
    if (root_u != root_v) {
        if (rank[root_u] > rank[root_v]) {
            parent[root_v] = root_u;
        } else if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
        } else {
            parent[root_v] = root_u;
            rank[root_u]++;
        }
    }
}

double clustering(vector<int> x, vector<int> y, int k) {
    int n = x.size();
    vector<Edge> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            edges.push_back({i, j, calculate_distance(x[i], y[i], x[j], y[j])});
        }
    }

    std::sort(edges.begin(), edges.end());

    vector<int> parent(n);
    vector<int> rank(n, 0);
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }

    int num_clusters = n;
    for (const Edge &edge : edges) {
        if (find(edge.u, parent) != find(edge.v, parent)) {
            union_sets(edge.u, edge.v, parent, rank);
            num_clusters--;
            if (num_clusters == k) {
                return edge.weight;
            }
        }
    }

    return -1.0;
}

int main() {
    size_t n;
    int k;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cin >> k;
    std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
