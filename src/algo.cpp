/**
 * @file algo.cpp
 *
 * @author Tyler Baxter
 * @version 1.0
 * @since 2024-10-12
 *
 * Implementation of user-implemented algorithms.
 */

#include "algo.hpp"

#include <cctype>

#include <cwchar>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <deque>
#include <utility>
#include <iostream>
#include <sstream>

using namespace algo;

using namespace std;

/**
 * Data structure and algorithm efficiencies:
 * 	Priority queue (heapsort): O(n log n)
 * 		* NOT intended to be traversed
 * 		* NOT intended to be searched
 * 		* NOT intended to randomly delete items
 * 		* To perform any of the above actions, choose a different sorting 
 * 		  algorithm.
 */

bool algo::STLisPalindrome(const string& s)
{
	string str = "";
	// Reconstruct string ignoring case and whitespace.
	for (const char& c : s) {
		if (!isspace(c)) {
			str += toupper(c);
		}
	}
	string r = str;
	reverse(r.begin(), r.end());
	return str == r;
}

bool algo::isPalindrome(const string& s)
{
	if (s.size() < 1) {
		return true;
	}

	size_t i = 0;
	size_t j = s.size() - 1;
	while (i < j) {
		// Ignore whitespace.
		while (isspace(s.at(i))) {	// should be safe
			++i;
		}
		while (isspace(s.at(j))) {	// should be safe
			--j;
		}
		// Ignore case.
		if (toupper(s.at(i++)) != toupper(s.at(j--))) {
			return false;
		}
	}
	return true;
}

/**
 * @pre Does not account for non-palindrome whitespace or non-alphanumeric 
 * characters.
 */
bool algo::risPalindrome(const string& s)
{
	// Base-case: An empty string or a single character is a palindrome.
	if (s.size() < 2) {
		return true;
	}

	// Not a palidrome (ignore case).
	if (toupper(s.front()) != toupper(s.back())) {
		return false;
	}

	// Recursive case:
	return risPalindrome(s.substr(1, s.size() - 2));
}

// Using Sieve of Eratosthenes.
// https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
int algo::countPrimes(int n)
{
	if (n < 2) {	// there are no primes less than two
		return 0;
	}

	vector<bool> primes(n + 1, true);
	primes[0] = primes[1] = false;
	// Upcasting here because integer overflow is a concern with i^2.
	for (long long i = 2; i * i <= n; ++i) {
		if (primes[i]) {
			for (auto j = i * i; j <= n; j += i) {
	  			primes[j] = false;
	  		}
	  	}
	}

	// Remove all non-primes and return size.
	primes.erase(remove_if(primes.begin(), primes.end(), [](bool v) {
		return !v;
	}),	primes.end());
	return primes.size();
}

// Prim's Algorithm.
// https://cp-algorithms.com/graph/mst_prim.html
int algo::primMst(const vector<vector<int>>& adj)
{
	const int INF = 0x7fffffff;
	const size_t size = adj.size();

	int cost = 0;
	// Initialize all edges to "infinity".
	vector<pair<int, int>> tree(size, { INF, -1 });	// { weight, parent }
	vector<bool> selected(size, false);

	// Select an abitrary first vertex (zero index in this case).
	tree[0].first = 0;
	for (int i = 0; i < size; ++i) {
		int v = -1;
		// Find the vertex with the minimum edge weight.
		for (int j = 0; j < size; ++j) {
			if (!selected[j] && (v == -1 || tree[j].first < tree[v].first)) {
	  			v = j;
			}
		}
	
		// If no valid vertex was found, the graph is not connected and no MST
		// exists.
		if (tree[v].first  == INF) {
			return -1;
		}

		selected[v] = true;
		cost += tree[v].first;
		// Update the edge weights for adjacent vertices.
		for (int to = 0; to < size; ++to) {
	  		if (adj[v][to] && !selected[to] && adj[v][to] < tree[to].first) {
	  			tree[to] = { adj[v][to], v };
	  		}
		}
	}
	return cost;
}

// xxx
// Kruskal's Algorithm.
// https://cp-algorithms.com/graph/mst_kruskal.html
//int algo::kruskalMst(const vector<vector<int>>& adj, int n)
//{
//	vector<pair<int, int>> edges;	// xxx convert adjacency matrix to edges
//	int cost = 0;
//	vector<int> treeId(n);
//	vector<pair<int, int>> result;
//	for (int i = 0; i < n; ++i) {
//		treeId[i] = i;
//	}
//
//	sort(edges.begin(), edges.end());
//	for (const auto& e : edges) {
//		if (treeId[e.first] != treeId[e.second]); {
//	  		//cost += e.third;
//			result.push_back(e);
//
//			int oldId = treeId[e.first];
//	  		int newId = treeId[e.second];
//	  		for (int i = 0; i < n; ++i) {
//	  			if (treeId[i] == oldId) {
//	  				treeId[i] == newId;
//	  			}
//	  		}
//	  	}
//	}
//	return cost;
//}

/*
 * Adjacency matrix:
 * 	    0 1 2 3 4
 * 	    ---------
 * 	0 | 0 1 1 0 0
 * 	1 | 1 0 0 1 0
 * 	2 | 1 0 0 0 1
 * 	3 | 0 1 0 0 1
 * 	4 | 0 0 0 1 1
 *
 * 	~~~~~~~~~~~~~
 *
 * 	{
 * 	 { 0, 1, 1, 0, 0 },
 * 	 { 1, 0, 0, 1, 0 },
 * 	 { 1, 0, 0, 0, 1 },
 * 	 { 0, 1, 0, 0, 1 },
 * 	 { 0, 0, 0, 1, 1 },
 * 	}
 */
vector<int> algo::bfs(const vector<vector<int>>& adj, int root)
{
	vector<bool> visited(adj.size(), false);
	vector<int> path;
	deque<int> q;
	q.push_front(root);
	visited[root] = true;

	while (!q.empty()) {
		int v = q.back();
		q.pop_back();
		path.push_back(v);

		for (auto i = 0; i < adj.size(); ++i) {
			if (adj[v][i] && !visited[i]) {
	   			q.push_front(i);
	   			visited[i] = true;
			}
		}
	}
	return path;
}

vector<int> algo::dfs(const vector<vector<int>>& adj, int root)
{
	vector<bool> visited(adj.size(), false);
	vector<int> path;
	deque<int> s;
	s.push_front(root);
	visited[root] = true;

	while (!s.empty()) {
		int v = s.front();
		s.pop_front();
		path.push_back(v);

		// Need to reverse iterate or else higher vertices will be at the top of
		// the stack.
		for (auto i = adj.size() - 1; i > 0; --i) {
			if (adj[v][i] && !visited[i]) {
	   			s.push_front(i);
				visited[i] = true;
			}
		}
	}
	return path;
}

// Recursive depth-first search.
vector<int> algo::rdfs(const vector<vector<int>>& adj, int root) 
{
	vector<bool> visited(adj.size(), false);
	vector<int> path;
	rdfsHelper(adj, root, visited, path);
	return path;
}

void algo::rdfsHelper(const vector<vector<int>>& adj, int root, 
					  vector<bool>& visited, vector<int>& path)
{
	visited[root] = true;	// mark the current node as visited
	for (auto i = 0; i < adj.size(); ++i) {
		if (adj[root][i] && !visited[i]) {
	  		rdfsHelper(adj, i, visited, path);
		}
	}
	path.push_back(root);	// post-order traversal
}

// xxx
// Dijkstra's algorithm.
//int algo::shortestPath(const vector<vector<int>>& adj, int root)
//{
//	const int INF = 0x7fffffff;
//	vector<bool> visited(adj.size(), false);
//	vector<int> dist(adj.size(), INF);
//	vector<int> path(adj.size(), -1);
//	
//	dist[root] = 0;
//	for (int i = 0; i < adj.size(); ++i) {
//		int v = -1;
//		for (int j = 0; j < adj.size(); ++j) {
//	  		if (!visited[j] && (v == -1 || dist[j] < dist[v])) {
//	  			v = j;
//	  		}
//		}
//
//		if (dist[v] == INF) {
//	  		// If the remaining edges are infinite, we've found the shortest 
//	  		// path.
//	  		break;
//		}
//
//		visited[v] = true;
//		for (const auto& e : adj[v]) {
//			// xxx pair
//	  		int to = e.first;
//	  		int len = e.second;
//			
//	  		if (dist[v] + len < dist[t]) {
//	  			dist[to] = dist[v] + len;
//	  			path[to] = v;
//	  		}
//		}
//	}
//	return -1;
//}

void algo::rdfsTimed(const vector<vector<int>>& adj, int root)
{
	vector<int> color(adj.size(), -1);
	int timer = 0;
	vector<int> inTime;
	vector<int> outTime;
	rdfsTimedHelper(adj, root, color, timer, inTime, outTime);
}

void algo::rdfsTimedHelper(const vector<vector<int>>& adj, int root,
						   vector<int>& color, int& timer, 
						   vector<int>& inTime, vector<int>& outTime)
{
	inTime[root] == timer++;
	color[root] = 1;
	for (int v : adj[root]) {
		if (color[root] < 1) {
	  		rdfsTimedHelper(adj, v, color, timer, inTime, outTime);
	  	}
	}
	color[root] = 2;
	outTime[root] = timer++;
}

/**
* @pre Directed acylic graph (DAG), meaning the graph must be directed and there
* must be no cycles.
*/
vector<int> algo::topologicalSort(const vector<vector<int>>& adj)
{	
	vector<bool> visited(adj.size(), false);
	vector<int> path;
	for (int i = 0; i < adj.size(); ++i) {
		if (!visited[i]) {
	  		rdfsHelper(adj, i, visited, path);
		}
	}
	reverse(path.begin(), path.end());
	return path;
}

// https://stackoverflow.com/questions/52131718/rotate-mn-matrix-90-degrees-clockwise-c
vector<vector<char>> algo::rotateMatrixClockwise(
	const vector<vector<char>>& mat)
{
	const size_t M = mat[0].size();
	const size_t N = mat.size();

	vector<vector<char>> myMat(M);	// MxN -> NxM
	for (auto i = 0; i < M; ++i) {
		myMat[i].resize(N);
	}

	// Algorithm to rotate clockwise.
	for (auto i = 0; i < N; ++i) {
		for (auto j = 0; j < M; ++j) {
	  		myMat[j][N - i - 1] = mat[i][j];
	  	}
	}

	return myMat;
}

bool algo::selectionSort(vector<int>& v)
{
	if (v.size() < 1) {
		return false;
	}

	for (auto i = v.size() - 1; i > 0; --i) {
		size_t largest = 0;
		// Don't loop what we've already sorted; all sorted is at end.
		for (auto j = 1; j <= i; ++j) {
	  		if (v.at(j) > v.at(largest)) {
	  			largest = j;
	  		}
		}
		swap(v.at(largest), v.at(i));
	}
	return true;
}

vector<string> algo::splitStringLoop(const string& str)
{
	vector<string> split;
	string s;
	for (const auto& c : str) {
		if (isspace(c)) {
	  		split.push_back(s);
	  		s = "";
		} else {
	  		s += c;
		}
	}
	// Need to push back the last string because `isspace()` won't get called on 
	// it.
	split.push_back(s);
	return split;
}

vector<string> algo::splitStringStream(const string& str)
{
	vector<string> split;
	stringstream stream(str);
	string s;
	while (stream >> s) {
		split.push_back(s);
	}
	return split;
}

void algo::swapMatrixRow(vector<vector<int>>& mat, int r1, int r2)
{
	const int M = mat[0].size();
	vector<int> tmp(M);
	for (auto i = 0; i < M; ++i) {
		tmp.at(i) = mat[r1][i];
	}
	for (auto i = 0; i < M; ++i) {
		mat[r1][i] = mat[r2][i];
	}
	mat[r2] = tmp;
}

void algo::swapMatrixColumn(vector<vector<int>>& mat, int c1, int c2)
{
	const int N = mat.size();
	vector<int> tmp(N);
	for (auto i = 0; i < N; ++i) {
		tmp.at(i) = mat[i][c1];
	}
	for (auto i = 0; i < N; ++i) {
		mat[i][c1] = mat[i][c2];
	}
	for (auto i = 0; i < N; ++i) {
		mat[i][c2] = tmp.at(i);
	}
}

void algo::reverseMatrixRow(vector<vector<int>>& mat, int row)
{
	const int M = mat[0].size();
	vector<int> tmp(M);
	for (auto i = 0; i < M; ++i) {
		tmp.at(i) = mat[row][i];
	}
	reverse(tmp.begin(), tmp.end());
	mat[row] = tmp;
}

void algo::reverseMatrixColumn(vector<vector<int>>& mat, int col)
{
	const int N = mat.size();
	vector<int> tmp(N);
	for (auto i = 0; i < N; ++i) {
		tmp.at(i) = mat[i][col];
	}
	reverse(tmp.begin(), tmp.end());
	for (auto i = 0; i < N; ++i) {
		mat[i][col] = tmp.at(i);
	}
}

bool algo::bubbleSort(vector<int>& v)
{
	if (v.size() < 1) {
	   return false;
	}

	bool sorted = false;
	size_t pass = 1;
	while (!sorted && (pass < v.size())) {
		sorted = true; // Assume sorted.
		for (auto i = 0; i < v.size() - pass; ++i) {
			auto next = i + 1;
			if (v.at(i) > v.at(next)) {
	   			swap(v.at(i), v.at(next));
	   			sorted = false; // Not finished sorting, flag another pass.
			}
		}
		++pass;
	}
	return true;
}

bool algo::mergeSort(vector<int>& v)
{
	const int size = v.size();
	if (size < 1) {
		return false;
	}
	return mergeSortHelper(v, size, 0, size - 1);
}

/**
 * Sorts the vector using merge sort.
 * Advantages: O(n log n).
 * Disadvantages: Requires temporary data structure allocation.
 *
 * @param v The vector to sort.
 * @param first The starting index of the vector.
 * @param last The ending index of the vector.
 */
bool algo::mergeSortHelper(vector<int>& v, int size, int first, int last)
{
	if (first < last) {	// Base-case.
		int mid = (first + last) / 2;

		// Sort: [first, ..., mid].
		mergeSortHelper(v, size, first, mid);
		// Sort: [mid + 1, ..., last].
		mergeSortHelper(v, size, mid + 1, last);

		// Merge the sorted halves.
		merge(v, size, first, mid, last);

		return true;
	}
	return false;
}

/**
 * Merges two sorted halves of the vector.
 *
 * @param v The vector to merge.
 * @param first The starting index of the first half.
 * @param mid The ending index of the first half.
 * @param last The ending index of the second half.
 */
void algo::merge(vector<int>& v, int size, int first, int mid, int last)
{
	vector<int> tmp(size);

	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;

	int idx = first1;
	while (first1 <= last1 && first2 <= last2) {
		if (v.at(first1) <= v.at(first2)) {
			tmp.at(idx++) = v.at(first1++);
		} else {
			tmp.at(idx++) = v.at(first2++);
		}
	}

	// Finish off the first subarray, if necessary.
	while (first1 <= last1) {
		tmp.at(idx++) = v.at(first1++);
	}

	// Finish off the second subarray, if necessary.
	while (first2 <= last2) {
		tmp.at(idx++) = v.at(first2++);
	}

	// Copy the result back into the original array.
	for (auto i = first; i <= last; ++i) {
		v.at(i) = tmp.at(i);
	}
}

bool algo::isPrime(int n) {
	if (n <= 1) {
		return false;
	}
	if (n == 2 || n == 3) {
		return true;
	}
	// Every prime number is 6k + 1 or 6k - 1, except 2 and 3.
	if ((n - 1) % 6 != 0 && (n + 1) % 6 != 0) {
		return false;
	}
	for (long long i = 5; i * i <= n; i += 6) {	// int can overflow
		if (n % i == 0 || n % (i + 2) == 0) {
			return false;
		}
	}
	return true;
}

void algo::swapInt(int a, int b)
{
	b += a;	// b = b + a
	a = b - a;	// (b + a) - a = b
	b = b - a;	// (b + a) - b = a
}

// EOF
