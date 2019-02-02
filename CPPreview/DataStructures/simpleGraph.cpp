class Graph {
public:
	Graph(int vertices = 0) : V{ vertices } {
		adjL = new std::vector<int>[V];
	}

	void addEdge(int u, int v);
	void BFS(int v);
	void DFS(int v);
private:
	int V;
	std::vector<int> * adjL;

	void DFSRec(int u, std::vector<bool> & visited);
};

void Graph::addEdge(int u, int v) {
	adjL[u].push_back(v);
	adjL[v].push_back(u);
}

void Graph::BFS(int v) {
	std::vector<bool> visited(V, false);
	std::queue<int> myQueue;

	myQueue.push(v);
	while (!myQueue.empty()) {
		int curr = myQueue.front(); myQueue.pop();
		if (!visited[curr]) {
			std::cout << curr << " ";
			visited[curr] = true;
		}
		for (size_t i = 0; i < adjL[curr].size(); i++) {
			if (!visited[adjL[curr][i]])
				myQueue.push(adjL[curr][i]);
		}
	}
}

void Graph::DFS(int s) {
	std::vector<bool> visited(V, false);

	for (int u = 0; u < V; ++u) {
		int start = (u + s) % V;

		if (!visited[start])
			DFSRec(start, visited);
	}  
}

void Graph::DFSRec(int u, std::vector<bool> & visited) {
	std::cout << u << " ";
	visited[u] = true;

	for (size_t i = 0; i < adjL[u].size(); i++) {
		if (!visited[adjL[u][i]])
			DFSRec(adjL[u][i], visited);
	}
}


int main() 
{	 
	Graph g(5);

	g.addEdge(0, 1);
	g.addEdge(0, 4);
	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(2, 3);
	g.addEdge(3, 4);

	std::cout << "\nDFS" << std::endl;
	g.DFS(2);
	std::cout << "\nBFS" << std::endl;
	g.BFS(2);


	std::cin.get();
}
