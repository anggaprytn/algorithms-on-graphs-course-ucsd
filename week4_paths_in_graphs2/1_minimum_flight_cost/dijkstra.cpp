#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using std::vector;
using std::priority_queue;
using std::pair;
using std::make_pair;

const long long INF = std::numeric_limits<long long>::max();

long long distance(const vector<vector<int>> &adj, const vector<vector<int>> &cost, int s, int t) {
	vector<long long> dist(adj.size(), INF);
	dist[s] = 0;
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, std::greater<pair<long long, int>>> pq;
	pq.push(make_pair(0, s));

	while (!pq.empty()) {
		int u = pq.top().second;
		long long current_dist = pq.top().first;
		pq.pop();

		if (current_dist > dist[u])
			continue;

		for (size_t i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i];
			long long weight = cost[u][i];

			if (dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}

	return dist[t] == INF ? -1 : dist[t];
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
	int s, t;
	std::cin >> s >> t;
	s--, t--;
	std::cout << distance(adj, cost, s, t);
}
