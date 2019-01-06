//LeetCode 743
/*
There are N network nodes, labelled 1 to N.
Given times, a list of travel times as directed edges times[i] = (u, v, w), where u is the source node, 
v is the target node, and w is the time it takes for a signal to travel from source to target.
Now, we send a signal from a certain node K. How long will it take for all nodes to receive the signal? 
If it is impossible, return -1.

Note:
N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 1 <= w <= 100.
 */
 
 // Dijkstra's Algorithm
 
 using namespace std;

vector<int> dijkstra(vector<vector<pair<int, int>>>& g, int src) {
	int n = g.size();
	vector<int> ret(n, -1);

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<void>> q;
	q.push({ 0,src });

	while (!q.empty()) {
		auto x = q.top(); q.pop();
		int c = x.first, v = x.second;

		if (ret[v] != -1) continue;
		ret[v] = c;
		for (auto p : g[v]) q.push({ p.second + c, p.first });
	}

	return ret;
}

int networkDelayTime(vector<vector<int>>& a, int n, int k) {
	vector<vector<pair<int, int>>> g(n);

	for (int i = 0; i<a.size(); i++) {
		int u = a[i][0] - 1, v = a[i][1] - 1, c = a[i][2];
		g[u].push_back({ v,c });
	}

	auto ret = dijkstra(g, k - 1);
	int hi = 0;
	for (int i = 0; i<n; i++) {
		if (ret[i] == -1) return -1;
		hi = max(hi, ret[i]);
	}
	return hi;
}


int main() {

	int N = 4, K = 2;
	std::vector<std::vector<int>> times{
		{ 2, 1, 1 },
		{ 2, 3, 1 },
		{ 3, 4, 1 } };

	int result = networkDelayTime(times, N, K);
	std::cout << result << std::endl;    // 2

	std::cin.get();
}
