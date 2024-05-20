#include <iostream>
#include <vector>
#include <limits>

using std::vector;

const long long INF = std::numeric_limits<long long>::max();

int negative_cycle(vector<vector<int>> &adj, vector<vector<int>> &cost) {
	int n = adj.size();
	vector<long long> dist(n, INF);
	dist[0] = 0; // Start from the first node (or you can start from any node)

	// Relax edges up to n-1 times
	for (int i = 0; i < n - 1; ++i) {
		for (int u = 0; u < n; ++u) {
			for (size_t k = 0; k < adj[u].size(); ++k) {
				int v = adj[u][k];
				int weight = cost[u][k];
				if (dist[u] != INF && dist[u] + weight < dist[v]) {
					dist[v] = dist[u] + weight;
				}
			}
		}
	}

	// Check for negative cycles
	for (int u = 0; u < n; ++u) {
		for (size_t k = 0; k < adj[u].size(); ++k) {
			int v = adj[u][k];
			int weight = cost[u][k];
			if (dist[u] != INF && dist[u] + weight < dist[v]) {
				return 1; // Negative cycle detected
			}
		}
	}

	return 0; // No negative cycle
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<vector<int>> adj(n, vector<int>());
	vector<vector<int>> cost(n, vector<int>());
	for (int i = 0; i < m; i++) {
		int x, y, w;
		std::cin >> x >> y >> w;
		adj[x - 1].push_back(y - 1);
		cost[x - 1].push_back(w);
	}
	std::cout << negative_cycle(adj, cost);
}
