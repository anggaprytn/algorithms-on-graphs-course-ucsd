#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

void shortest_paths(vector<vector<int>> &adj, vector<vector<int>> &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
	const long long INF = std::numeric_limits<long long>::max();
	int n = adj.size();
	distance[s] = 0;
	reachable[s] = 1;

	// Step 1: Bellman-Ford to find shortest paths
	for (int i = 0; i < n - 1; ++i) {
		for (int u = 0; u < n; ++u) {
			if (distance[u] == INF) continue;
			for (size_t j = 0; j < adj[u].size(); ++j) {
				int v = adj[u][j];
				if (distance[u] + cost[u][j] < distance[v]) {
					distance[v] = distance[u] + cost[u][j];
					reachable[v] = 1;
				}
			}
		}
	}

	// Step 2: Detect negative cycles
	queue<int> q;
	vector<int> inQueue(n, 0);
	for (int u = 0; u < n; ++u) {
		if (distance[u] == INF) continue;
		for (size_t j = 0; j < adj[u].size(); ++j) {
			int v = adj[u][j];
			if (distance[u] + cost[u][j] < distance[v]) {
				q.push(v);
				inQueue[v] = 1;
			}
		}
	}

	// Process nodes reachable from negative cycles
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		shortest[u] = 0;
		for (int v : adj[u]) {
			if (!inQueue[v]) {
				q.push(v);
				inQueue[v] = 1;
			}
		}
	}
}

int main() {
	int n, m, s;
	std::cin >> n >> m;
	vector<vector<int>> adj(n, vector<int>());
	vector<vector<int>> cost(n, vector<int>());
	for (int i = 0; i < m; i++) {
		int x, y, w;
		std::cin >> x >> y >> w;
		adj[x - 1].push_back(y - 1);
		cost[x - 1].push_back(w);
	}
	std::cin >> s;
	s--;
	vector<long long> distance(n, std::numeric_limits<long long>::max());
	vector<int> reachable(n, 0);
	vector<int> shortest(n, 1);
	shortest_paths(adj, cost, s, distance, reachable, shortest);
	for (int i = 0; i < n; i++) {
		if (!reachable[i]) {
			std::cout << "*\n";
		} else if (!shortest[i]) {
			std::cout << "-\n";
		} else {
			std::cout << distance[i] << "\n";
		}
	}
}
