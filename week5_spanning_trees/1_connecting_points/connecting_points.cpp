#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <queue>

using std::vector;
using std::priority_queue;
using std::pair;
using std::make_pair;

double calculate_distance(int x1, int y1, int x2, int y2) {
	return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double minimum_distance(vector<int> x, vector<int> y) {
	int n = x.size();
	vector<bool> inMST(n, false);
	vector<double> minEdge(n, std::numeric_limits<double>::max());
	priority_queue<pair<double, int>, vector<pair<double, int>>, std::greater<pair<double, int>>> pq;

	// Start with the first point
	minEdge[0] = 0;
	pq.push(make_pair(0, 0));

	double result = 0.0;

	while (!pq.empty()) {
		int u = pq.top().second;
		double weight = pq.top().first;
		pq.pop();

		if (inMST[u]) continue;

		inMST[u] = true;
		result += weight;

		for (int v = 0; v < n; ++v) {
			if (!inMST[v]) {
				double dist = calculate_distance(x[u], y[u], x[v], y[v]);
				if (dist < minEdge[v]) {
					minEdge[v] = dist;
					pq.push(make_pair(dist, v));
				}
			}
		}
	}

	return result;
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> x(n), y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
