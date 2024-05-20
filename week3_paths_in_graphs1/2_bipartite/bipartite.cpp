#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

bool isBipartiteComponent(const vector<vector<int>> &adj, vector<int> &colors, int start) {
	queue<int> q;
	q.push(start);
	colors[start] = 1;

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		for (int u : adj[v]) {
			if (colors[u] == 0) {
				colors[u] = 3 - colors[v];  // Assign the opposite color
				q.push(u);
			} else if (colors[u] == colors[v]) {
				return false;  // Same color on both ends of an edge means it's not bipartite
			}
		}
	}

	return true;
}

int bipartite(vector<vector<int>> &adj) {
	vector<int> colors(adj.size(), 0);

	for (size_t i = 0; i < adj.size(); ++i) {
		if (colors[i] == 0) {
			if (!isBipartiteComponent(adj, colors, i)) {
				return 0;  // Not bipartite
			}
		}
	}

	return 1;  // Bipartite
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<vector<int>> adj(n, vector<int>());
	for (int i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}
	std::cout << bipartite(adj);
}
