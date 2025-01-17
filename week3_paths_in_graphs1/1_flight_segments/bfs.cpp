#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int>> &adj, int s, int t) {
	vector<int> dist(adj.size(), -1);
	queue<int> q;

	dist[s] = 0;
	q.push(s);

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		for (int u : adj[v]) {
			if (dist[u] == -1) {  // u has not been visited
				q.push(u);
				dist[u] = dist[v] + 1;
			}
		}
	}

	return dist[t];
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
	int s, t;
	std::cin >> s >> t;
	s--, t--;
	std::cout << distance(adj, s, t);
}
