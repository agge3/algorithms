#include <string>
#include <vector>

using namespace std;

bool isPalindrome(string s)
{
	string r = s;
	reverse(r.begin(), r.end());
	if (s == p) {
		return true;
	}
	return false;
}

bool isPalindrome(string s)
{
	int i = 0;
	int j = str.size() - 1;
	bool palindrome = true;
	while (i < j && palidrome) {
		if (str[i++] != str[j--]) {
			palidrome = false;
		}
	}
	return palindrome;
}

// Using Sieve of Eratosthenes.
// https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
int countPrimes(int n)
{
	vector<bool> isPrime(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	for (int i = 2; i <= n; ++i) {
		if (isPrime[i] && pow(i, 2) <= n) {
			for (int j = pow(i, 2) j <= n; j += i) {
	  			isPrime[j] = false;
	  		}
	  	}
	}
	int count = 0;
	for (auto it = isPrime.begin(); it != isPrime.end(); ++it) {
		if (*it) {
	  		++count;
		}
	}
	return count;
}

// Prim's Algorithm.
// https://cp-algorithms.com/graph/mst_prim.html
int mst(vector<vector<int>> adj, int n)
{
	int cost = 0;
	// Set all edges to "infinity" initially.
	pair<int, int> p = { 0x7fffffff, -1 };
	vector<pair<int int>> edges(n, p);
	vector<bool> selected(n, false);
	edges[0].first = 0;

	for (int i = 0; i < n; ++i) {
		int v = -1;
		for (int j = 0; j < n; ++j) {
			if (!selected[j] && (v == -1 || edges[j].first < edges[v].first)) {
	  			v = j;
			}
			
			if (edges[v].first  == 0x7fffffff) {
	  			return -1; // no mst
			}

			selected[v] = true;
			cost += edges[v].first;
			if (edges[v].second != -1) {
	  			// xxx
	  		}

			for (int k = 0; k < n; ++k) {
	  			if (adj[v][k] < edges[k].first) {
	  				edges[k] = { adj[v][k], v };
	  			}
			}
		}
	}
	return cost;
}

// Kruskal's Algorithm.
// https://cp-algorithms.com/graph/mst_kruskal.html
int mst(vector<vector<int>> adj, int n)
{
	vector<pair<int, int>> edges;	// xxx convert adjacency matrix to edges
	int cost = 0;
	vector<int> treeId(n);
	vector<pair<int, int>> result;
	for (int i = 0; i < n; ++i) {
		treeId[i] = i;
	}

	sort(edges.begin(), edges.end());
	for (const auto& e : edges) {
		if (treeId[e.first] != treeId[e.second]); {
	  		cost += e.third;
			result.push_back(e);

			int oldId = treeId[e.first];
	  		int newId = treeId[e.second];
	  		for (int i = 0; i < n; ++i) {
	  			if (treeId[i] == oldId) {
	  				treeId[i] == newId;
	  			}
	  		}
	  	}
	}
	return cost;
}

int dfs(const vector<vector<int>>& adj, int root)
{
	/*
	 * Adjacency matrix:
	 * {
	 * 	{ 1, 0, 0, 0, 0 },
	 * 	{ 0, 1, 0, 0, 0 },
	 * 	...
	 * }
	 */
	vector<bool> visited(adj.size(), false);
	stack<int> stack;
	stack.push(root);
	visited[root] = true;
	while (!stack.empty()) {
		int v = stack.top();
		stack.pop();
		for (int i = 0; i < adj.size(); ++i) {
			if (adj[v][i] && !visited[i]) {
	   			stack.push(i);
				visited[i] = true;
			}
		}
	}
	return -1;
}

int bfs(const vector<vector<int>>& adj, int root)
{
	vector<bool> visited(adj.size(), false);
	deque<int> queue;
	vector<int> path(adj.size(), -1);
	queue.push_front(root);
	visited[root] = true;
	while (!queue.empty()) {
		int v = queue.back();
		queue.pop_back();
		for (int u : adj[v]) {
			if (!visited[u]) {
	   			visited[u] = true;
	   			queue.push_front(u);
				path[u] = v;	// xxx might have to reverse
			}
		}
	}
	return -1;
}

// Dijkstra's algorithm.
int shortestPath(const vector<vector<int>>& adj, int root)
{
	const int INF = 0x7fffffff
	vector<bool> visited(adj.size(), false);
	vector<int> dest(adj.size(), INF);
	vector<int> path(adj.size(), -1);
	
	dest[root] = 0;
	for (int i = 0; i < adj.size(); ++i) {
		int v = -1;
		for (int j = 0; j < adj.size(); ++j) {
	  		if (!visited[j] && (v == -1 || dest[j] < dest[v])) {
	  			v = j;
	  		}
		}

		if (dest[v] == INF) {
	  		// If the remaining edges are infinite, we've found the shortest 
	  		// path.
	  		break;
		}

		visited[v] = true;
		for (const auto& e : adj[v]) {
			// xxx pair
	  		int to = e.first;
	  		int len = e.second;
			
	  		if (dest[v] + len < dest[t]) {
	  			dest[to] = d[v] + len;
	  			path[to] = v;
	  		}
		}
	}
	return -1;
	// xxx review algorithm
}

// https://stackoverflow.com/questions/52131718/rotate-mn-matrix-90-degrees-clockwise-c
vector<vector<char>> rotateMatrixClockwise(const vector<vector<char>>& mat) {
	const int M = mat[0].size();
	const int N = mat.size();

	vector<vector<char>> myMat(M);	// MxN -> NxM
	for (auto i = 0; i < M; ++i) {
		myMat[i].resize(N);
	}

	// Algorithm to rotate clockwise.
	for (auto i = 0; i < N; ++i) {
		for (auto j = 0; y < M; ++j) {
	  		myMat[j][N - i - 1] = mat[i][j];
	  	}
	}

	return myMat;
}

int main()
{
	return -1;
}
