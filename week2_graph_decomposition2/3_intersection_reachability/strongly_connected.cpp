#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::pair;
using std::stack;

void dfs1(const vector<vector<int>> &adj, vector<bool> &visited, stack<int> &finishStack, int v) {
	visited[v] = true;
	for (int u : adj[v]) {
		if (!visited[u]) {
			dfs1(adj, visited, finishStack, u);
		}
	}
	finishStack.push(v);
}

void dfs2(const vector<vector<int>> &adj, vector<bool> &visited, int v) {
	visited[v] = true;
	for (int u : adj[v]) {
		if (!visited[u]) {
			dfs2(adj, visited, u);
		}
	}
}

vector<vector<int>> transposeGraph(const vector<vector<int>> &adj) {
	vector<vector<int>> transposed(adj.size());
	for (size_t v = 0; v < adj.size(); v++) {
		for (int u : adj[v]) {
			transposed[u].push_back(v);
		}
	}
	return transposed;
}

int number_of_strongly_connected_components(vector<vector<int>> adj) {
	int result = 0;
	stack<int> finishStack;
	vector<bool> visited(adj.size(), false);

	// First pass: record the finish times of each node
	for (size_t i = 0; i < adj.size(); i++) {
		if (!visited[i]) {
			dfs1(adj, visited, finishStack, i);
		}
	}

	// Transpose the graph
	vector<vector<int>> transposed = transposeGraph(adj);

	// Second pass: process nodes in decreasing order of finish time
	std::fill(visited.begin(), visited.end(), false);
	while (!finishStack.empty()) {
		int v = finishStack.top();
		finishStack.pop();
		if (!visited[v]) {
			dfs2(transposed, visited, v);
			result++;
		}
	}

	return result;
}

int main() {
	size_t n, m;
	std::cin >> n >> m;
	vector<vector<int>> adj(n, vector<int>());
	for (size_t i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
	}
	std::cout << number_of_strongly_connected_components(adj);
}
