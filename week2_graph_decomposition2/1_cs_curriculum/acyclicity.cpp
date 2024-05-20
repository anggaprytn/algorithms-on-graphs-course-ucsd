#include <iostream>
#include <vector>

using std::vector;
using std::pair;

bool dfs(const vector<vector<int>> &adj, vector<bool> &visited, vector<bool> &recStack, int v) {
    visited[v] = true;
    recStack[v] = true;

    for (int u : adj[v]) {
        if (!visited[u] && dfs(adj, visited, recStack, u)) {
            return true;
        } else if (recStack[u]) {
            return true;
        }
    }

    recStack[v] = false;
    return false;
}

int acyclic(vector<vector<int>> &adj) {
    vector<bool> visited(adj.size(), false);
    vector<bool> recStack(adj.size(), false);

    for (size_t i = 0; i < adj.size(); i++) {
        if (!visited[i]) {
            if (dfs(adj, visited, recStack, i)) {
                return 1;
            }
        }
    }
    return 0;
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
    std::cout << acyclic(adj);
}
