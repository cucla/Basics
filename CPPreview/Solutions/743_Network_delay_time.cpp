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

/*
	std::vector<std::vector<int>> times{
		{2, 1, 1},
		{2, 3, 1},
		{3, 4, 1} };

	/* adjacency matrix
	         0  1  2  3
	1 |  0  -1 -1 -1 -1
	2 |  1   1 -1  1 -1
	3 |  2  -1 -1 -1  1
	4 |  3  -1 -1 -1 -1
	*/
	std::vector<std::vector<int>> adjMatr(4, std::vector<int>(4, -1));
	for (auto el : times) {
		adjMatr[el[0] - 1][el[1] - 1] = el[2];
	}

	/* adjacency list, {node, weight}
	1 |  0  []
	2 |  1  {0, 1}, {2, 1}
	3 |  2  {3, 1}
	4 |  3  []
	*/
	std::vector<std::vector<std::pair<int, int>>> adjList(4);
	for (auto el : times) {
		adjList[el[0] - 1].push_back({ el[1] - 1, el[2] });
	}
 */
 
 // Solution #1: Dijkstra's Algorithm
 
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

// Solution #2 BFS

int networkDelayTime(vector<vector<int>>& times, int N, int K) {
	vector<int> sigTime(N, INT_MAX);
	vector< vector<int> > mat(N, vector<int>(N, -1));    //adjacent matrix
	for (auto edgeVec : times) {
		mat[edgeVec[0] - 1][edgeVec[1] - 1] = edgeVec[2];
	}
	K = K - 1;
	sigTime[K] = 0;
	queue<int> nodeQ;
	nodeQ.push(K);
	while (!nodeQ.empty()) {
		int nd = nodeQ.front();
		for (int i = 0; i<N; ++i) {
			if (mat[nd][i] >= 0 && sigTime[i] > sigTime[nd] + mat[nd][i]) {
				nodeQ.push(i);
				sigTime[i] = sigTime[nd] + mat[nd][i];
			}
		}
		nodeQ.pop();
	}
	int ans = 0;
	for (auto t : sigTime) {
		ans = max(t, ans);
	}
	return (ans == INT_MAX) ? -1 : ans;
}

