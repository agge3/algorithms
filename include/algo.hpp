/**
 * @file algo.hpp
 * @namespace algo
 *
 * @author Tyler Baxter
 * @version 1.0
 * @since 2024-10-12
 *
 * Namespace for user-implemented algorithms.
 */

#pragma once

#include <stdexcept>
#include <string>
#include <vector>

namespace algo {
	bool isPalindrome(const std::string& s);

	bool risPalindrome(const std::string& s);

	bool STLisPalindrome(const std::string& s);

	bool isPrime(int n);

	int countPrimes(int n);

	void swapInt(int a, int b);

	int primMst(const std::vector<std::vector<int>>& adj);

	std::vector<std::string> splitStringLoop(const std::string& str);

	std::vector<std::string> splitStringStream(const std::string& str);

	void swapMatrixRow(std::vector<std::vector<int>>& mat, int r1, int r2);

	void swapMatrixColumn(std::vector<std::vector<int>>& mat, int c1, int c2);

	void reverseMatrixRow(std::vector<std::vector<int>>& mat, int row);

	void reverseMatrixColumn(std::vector<std::vector<int>>& mat, int col);

	//int kruskalMst(const std::vector<std::vector<int>>& adj, int n);

	std::vector<int> dfs(const std::vector<std::vector<int>>& adj, int root);

	std::vector<int> bfs(const std::vector<std::vector<int>>& adj, int root);

	//int shortestPath(const std::vector<std::vector<int>>& adj, int root);

	std::vector<int> rdfs(const std::vector<std::vector<int>>& adj, int root);

	void rdfsHelper(const std::vector<std::vector<int>>& adj, int root,
				 std::vector<bool>& visited, std::vector<int>& path);

	void rdfsTimed(const std::vector<std::vector<int>>& adj, int root);

	void rdfsTimedHelper(const std::vector<std::vector<int>>& adj, int root, 
					  std::vector<int>& color, int& timer, 
					  std::vector<int>& inTime, std::vector<int>& outTime);

	std::vector<int> topologicalSort(const std::vector<std::vector<int>>& adj);

	std::vector<std::vector<char>> rotateMatrixClockwise(
		const std::vector<std::vector<char>>& mat);

	bool selectionSort(std::vector<int>& v);

	bool bubbleSort(std::vector<int>& v);

	bool mergeSort(std::vector<int>& v);
	
	bool mergeSortHelper(std::vector<int>& v, int size, int first, int last);;

	void merge(std::vector<int>& v, int size, int first, int mid, int last);
} // namespace algo

// ALGO_HPP
