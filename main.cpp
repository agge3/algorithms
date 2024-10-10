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
