#include <csignal>
#include <cstdio>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <random>
#include <thread>
#include <chrono>

static std::vector<int> x;

/**
 * To be called before evaluation in the n_queens problem. Eliminates
 * unnecessary calculations by determining whether the next given input
 * is viable or not.
 *
 * @param k		The kth queen
 *
 * @param i 	The ith column
 *
 * @return True if it is promising, false if not.
 */
bool promising(int k, int i) {
	for (int j = 1; j <= k - 1; ++j) {
		if ((x[j] == i) || (abs(x[j] - i) == abs(j - k))) {
			return false;
		}
	}
	return true;
}

/**
 * Internal double checking function to ensure that our algorithm correctly
 * marked a solution as viable. Mainly for testing purposes.
 *
 * @return True if valid solution, false if not.
 */
bool check() {
	std::unordered_set<int> lookup;
	for (auto e : x) {
		if (lookup.find(e) != lookup.end()) {
			std::cout << "Duplicate value found.\n";
			return false;
		}
		lookup.insert(e);
	}
	return true;
}

/**
 * N-Queens algorithm. Finds all possible valid placements of N Queens on an
 * NxN chessboard.
 *
 * @param int k		Always starts at 1: The current Queen being placed
 *
 * @param n			The total amount of Queens
 *
 * @note This function prints each result.
 */
void n_queens(int k, int n) {
	// Entrance message
	if (k == 1) {
		std::cout << "Trying " << n << "-Queens.\n";
		std::cout << "Solutions were:\n";
	}

	// Dynamically set global vector to the right size. We use n + 1 because
	// the algorithm is 1-based instead of 0-based.
	x.resize(n + 1);
	
	for (int i = 1; i <= n; ++i) {
		if (promising(k, i)) {
			x.at(k) = i;
			if (k == n) {
				for (int j = 1; j <= n; ++j) {
					if (!check()) {
						std::cout << "Algorithm failed.\n";
					}
    				std::cout << x.at(j);
    				if (j < n) { 
						std::cout << ", ";
					}
				}
				std::cout << ".\n";
			} else {
				n_queens(k + 1, n);
			}
		}
	}
}

/**
 * N Queens Monte Carlo Estimation Simulator. Given an amount of queens,
 * it calculates the number of nodes found promising with backtracking.
 *
 * @param int n		The amount of Queens.
 *
 * @return The number of nodes found promising with backtracking.
 */
int n_queens_estimate(int n) {
	int num_nodes = 1;
	int m = 1;
	int mprod = 1;
	int i = 0;
	x.resize(n + 1);
	std::random_device rd;
	std::mt19937 gen(rd());
	while (m != 0 && i != n) {
		mprod = mprod * m;
		num_nodes = num_nodes + mprod * n;
		i++;
		// compute promising nodes in level i
		m = 0;
		std::vector<int> prom_children;
		for (int j = 1; j <= n; ++j) {
			x.at(i) = j;
			if (promising (i, j)) {
				m++;
				prom_children.push_back(j);
			}
		}
		if (m != 0) {
			size_t size = prom_children.size();
			std::uniform_int_distribution<> dist(0, size - 1);
			int rand_num = dist(gen);
			int j = prom_children[rand_num];
			x.at(i) = j;
		}
	}
	x.clear();
	return num_nodes;
}

/**
 * Helper function to run the n_queens_estimate() function with N amount of
 * Queens for num_of_sims.
 *
 * @param int n					The amount of Queens.
 *
 * @param int num_of_sims		The amount of simulations to run.
 *
 * @return The average calculated from num_of_sims simulations.
 *
 * @note This function also prints what the average was.
 */
int estimate(int n, int num_of_sims) {
	double sum = 0;
	for (int i = 0; i < num_of_sims; ++i) {
		double estimate = n_queens_estimate(n);
		std::cout << i << ". Estimate was: " << estimate << ".\n";
		sum += estimate;
	}
	double average = sum / num_of_sims;
	std::cout << "Average was: " << average << "." << std::endl;
	return average;
}

int main() {
	std::cout << "Welcome to Kat's N-Queens problem simulator.\n";
	bool running = true;
	std::vector<int> possible{ 4, 8, 12, 14 };
	while (running) {
		std::cout << "To run the N-Queens problem, please type p.\n"
			      << "To run the Monte Carlo Simulated Estimation of N-Queens,"
			      << " please type s.\nPress q to quit.\n";
		char a;
    	std::cin.get(a);
    	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		if (a == 'q') {
			std::cout << "Thank you for trying Kat's N-Queens problem"
				      << " simulator. System exiting...";
			exit(0);
		}

		if (a == 'p') {
			std::string ans;
			int k;
			bool waiting = true;
			std::cout << "Please enter the amount of queens.\n"
					  << "Possible choices are 4, 8, 12, or 14.\n"
				      << "Press q to quit.\n";
			while (waiting) {
				std::getline(std::cin, ans);
				if (ans == "q") {
					std::cout << "Thank you for trying Kat's N-Queens problem"
				      		  << " simulator.\nSystem exiting...";
					std::exit(0);
				}
				try {
					k = std::stoi(ans);
				} catch (const std::invalid_argument& e) {
					std::cout << "Must enter a number. Please try again.\n";
					continue;
				}
				if (find(possible.begin(), possible.end(), k) == possible.end()) {
					std::cout << "Must be 4, 8, 12, or 14." 
							  << " Please try again.\nPress q to quit.\n";
				} else {
					n_queens(1, k);
					std::cout << "Thank you for trying Kat's N-Queens problem"
				      		  << " simulator.\nSystem restarting...\n";
					waiting = false;
				}
			}

		} else if (a == 's') {
			int num_queens = 0;
			std::string ans;
			bool waiting = true;
			while (waiting) {
				std::cout << "Please enter the amount of queens you would like.\n";
				std::cout << "Possible choices are 4, 8, 12, or 14.\n";
				std::cout << "Press q to quit.\n";
				std::getline(std::cin, ans);
				if (ans == "q") {
					std::cout << "Thank you for trying Kat's N-Queens problem"
				      		  << " simulator.\nSystem exiting...\n";
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					std::exit(0);	
				}
				try {
					num_queens = std::stoi(ans);
				} catch (const std::invalid_argument& e) {
					std::cout << "Must enter a number. Please try again.\n";
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					continue;
				}
				std::cout << "Please enter the amount of simulations you would"
					      << " like.\n";
				int num_sims = 0;
				std::getline(std::cin, ans);
				try {
					num_sims = std::stoi(ans);
				} catch (const std::invalid_argument& e) {
					std::cout << "Must enter a number. Please try again.\n";
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					continue;
				}
				estimate(num_queens, num_sims);
				std::cout << "Thank you for trying my Monte Carlo Simulated"
				          << " Estimation of N-Queens.\nSystem restarting...\n";
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				waiting = false;
			}
		} else {
			std::cout << "Incorrect value submitted. Please try again.\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
}
