#include "algo.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <iostream>

// Set to FALSE to use default gtest.
const bool NANOSECONDS = true;

// Record execution time in nanoseconds.
class NanosecondListener : public testing::TestEventListener {
public:
    explicit NanosecondListener(testing::TestEventListener* delegate)
        : delegate_(delegate) {}

    void OnTestStart(const testing::TestInfo& test_info) override {
        start_time_ = std::chrono::high_resolution_clock::now();
    }

    void OnTestEnd(const testing::TestInfo& test_info) override {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration_ns = 
			std::chrono::duration_cast<std::chrono::nanoseconds>(
				end_time - start_time_).count();
        std::cout << "[   TIME   ] " << test_info.test_suite_name() << "." << 
			test_info.name() << " (" << duration_ns << " ns)\n";

        // Call the original listener's OnTestEnd method
        delegate_->OnTestEnd(test_info);
    }

    // Implement all required pure virtual functions
    void OnTestPartResult(const testing::TestPartResult& test_part_result) override {
        delegate_->OnTestPartResult(test_part_result);
    }

    void OnTestProgramStart(const testing::UnitTest& unit_test) override {
        delegate_->OnTestProgramStart(unit_test);
    }

    void OnTestIterationStart(const testing::UnitTest& unit_test, int iteration) override {
        delegate_->OnTestIterationStart(unit_test, iteration);
    }

    void OnEnvironmentsSetUpStart(const testing::UnitTest& unit_test) override {
        delegate_->OnEnvironmentsSetUpStart(unit_test);
    }

    void OnEnvironmentsSetUpEnd(const testing::UnitTest& unit_test) override {
        delegate_->OnEnvironmentsSetUpEnd(unit_test);
    }

    void OnEnvironmentsTearDownStart(const testing::UnitTest& unit_test) override {
        delegate_->OnEnvironmentsTearDownStart(unit_test);
    }

    void OnEnvironmentsTearDownEnd(const testing::UnitTest& unit_test) override {
        delegate_->OnEnvironmentsTearDownEnd(unit_test);
    }

    void OnTestIterationEnd(const testing::UnitTest& unit_test, int iteration) override {
        delegate_->OnTestIterationEnd(unit_test, iteration);
    }

    void OnTestProgramEnd(const testing::UnitTest& unit_test) override {
        delegate_->OnTestProgramEnd(unit_test);
    }

private:
    testing::TestEventListener* delegate_;
    std::chrono::high_resolution_clock::time_point start_time_;
};

// Define test cases
TEST(AlgoTests, IsPalindrome)
{
    EXPECT_TRUE(algo::isPalindrome("racecar"));
    EXPECT_TRUE(algo::isPalindrome("A man a plan a canal Panama")); // Assuming case insensitivity
    EXPECT_TRUE(algo::isPalindrome("No lemon no melon")); // Assuming punctuation/space handling
    EXPECT_TRUE(algo::isPalindrome("a"));
    EXPECT_TRUE(algo::isPalindrome(""));
    EXPECT_FALSE(algo::isPalindrome("hello"));
    EXPECT_FALSE(algo::isPalindrome("world"));
    EXPECT_FALSE(algo::isPalindrome("12345"));
}

TEST(AlgoTests, RisPalindrome)
{
    EXPECT_TRUE(algo::risPalindrome("level"));
    EXPECT_TRUE(algo::risPalindrome("Able was I ere I saw Elba")); // Assuming case insensitivity
    EXPECT_TRUE(algo::risPalindrome("A"));
    EXPECT_TRUE(algo::risPalindrome(""));
    EXPECT_FALSE(algo::risPalindrome("world"));
}

TEST(AlgoTests, STLisPalindrome)
{
    EXPECT_TRUE(algo::STLisPalindrome("deified"));
    EXPECT_TRUE(algo::STLisPalindrome("A man a plan a canal Panama"));
    EXPECT_TRUE(algo::STLisPalindrome("A    man a plan a      canal Panama"));
    EXPECT_TRUE(algo::STLisPalindrome("12321"));
    EXPECT_FALSE(algo::STLisPalindrome("abcd"));
}

TEST(AlgoTests, CountPrimes)
{
    EXPECT_EQ(algo::countPrimes(10), 4);  // 2, 3, 5, 7
    EXPECT_EQ(algo::countPrimes(20), 8);  // 2, 3, 5, 7, 11, 13, 17, 19
    EXPECT_EQ(algo::countPrimes(1), 0);
    EXPECT_EQ(algo::countPrimes(0), 0);
    EXPECT_EQ(algo::countPrimes(100), 25); // Check known result
}

TEST(AlgoTests, PrimMST) 
{
    std::vector<std::vector<int>> adj = {
        {0, 1, 2, 0},
        {1, 0, 0, 3},
        {2, 0, 0, 1},
        {0, 3, 1, 0}
    };
    EXPECT_EQ(algo::primMst(adj), 4);  // Example known result
}

//TEST(AlgoTests, KruskalMST)
//{
//    std::vector<std::vector<int>> adj = {
//        {0, 10, 6, 5},
//        {10, 0, 0, 15},
//        {6, 0, 0, 4},
//        {5, 15, 4, 0}
//    };
//    EXPECT_EQ(algo::kruskalMst(adj, 4), 19);  // Example known result
//}

TEST(AlgoTests, BFS) 
{
    std::vector<std::vector<int>> adj = {
        {0, 1, 1, 0, 0},  // Node 0 connects to 1 and 2
        {0, 0, 0, 1, 0},  // Node 1 connects to 3
        {0, 0, 0, 0, 1},  // Node 2 connects to 4
        {0, 0, 0, 0, 0},  // Node 3 has no outgoing edges
        {0, 0, 0, 0, 0}   // Node 4 has no outgoing edges
    };

    std::vector<int> expected_path = {0, 1, 2, 3, 4}; // Actual BFS order
    std::vector<int> actual_path = algo::bfs(adj, 0);
    
    EXPECT_EQ(actual_path, expected_path);
}

TEST(AlgoTests, DFS)
{
    std::vector<std::vector<int>> adj = {
        {0, 1, 1, 0, 0},  // Node 0 connects to 1 and 2
        {0, 0, 0, 1, 0},  // Node 1 connects to 3
        {0, 0, 0, 0, 1},  // Node 2 connects to 4
        {0, 0, 0, 0, 0},  // Node 3 has no outgoing edges
        {0, 0, 0, 0, 0}   // Node 4 has no outgoing edges
    };

    std::vector<int> expected_path = {0, 1, 3, 2, 4}; // Actual DFS order
    std::vector<int> actual_path = algo::dfs(adj, 0);
    
    EXPECT_EQ(actual_path, expected_path);
}

TEST(AlgoTests, RDFS) 
{
    std::vector<std::vector<int>> adj = {
        {0, 1, 1, 0, 0},  // Node 0 connects to 1 and 2
        {0, 0, 0, 1, 0},  // Node 1 connects to 3
        {0, 0, 0, 0, 1},  // Node 2 connects to 4
        {0, 0, 0, 0, 0},  // Node 3 has no outgoing edges
        {0, 0, 0, 0, 0}   // Node 4 has no outgoing edges
    };

    std::vector<int> expected_path = {3, 1, 4, 2, 0};	// post-order traversal
    std::vector<int> actual_path = algo::rdfs(adj, 0);
    //std::reverse(actual_path.begin(), actual_path.end()); // Reverse to match expected order

    EXPECT_EQ(actual_path, expected_path);
}

//TEST(AlgoTests, ShortestPath)
//{
//    std::vector<std::vector<int>> adj = {
//        {0, 1, 4, 0},
//        {0, 0, 2, 0},
//        {0, 0, 0, 3},
//        {0, 0, 0, 0}
//    };
//    EXPECT_EQ(algo::shortestPath(adj, 0), 7); // Modify based on implementation
//}

TEST(AlgoTests, RotateMatrixClockwise)
{
    std::vector<std::vector<char>> mat = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };
    auto result = algo::rotateMatrixClockwise(mat);
    std::vector<std::vector<char>> expected = {
        {'7', '4', '1'},
        {'8', '5', '2'},
        {'9', '6', '3'}
    };
    EXPECT_EQ(result, expected);
}

TEST(AlgoTests, SelectionSort)
{
    std::vector<int> v1 = {64, 25, 12, 22, 11};
    EXPECT_TRUE(algo::selectionSort(v1));
    EXPECT_EQ(v1, std::vector<int>({11, 12, 22, 25, 64}));

    std::vector<int> v2 = {5};
    EXPECT_TRUE(algo::selectionSort(v2));
    EXPECT_EQ(v2, std::vector<int>({5}));

    std::vector<int> v3 = {};
    EXPECT_FALSE(algo::selectionSort(v3)); // Empty vector case
    EXPECT_EQ(v3, std::vector<int>({})); // Should remain empty
}

TEST(AlgoTests, BubbleSort)
{
    std::vector<int> v1 = {64, 34, 25, 12, 22, 11, 90};
    EXPECT_TRUE(algo::bubbleSort(v1));
    EXPECT_EQ(v1, std::vector<int>({11, 12, 22, 25, 34, 64, 90}));

    std::vector<int> v2 = {5};
    EXPECT_TRUE(algo::bubbleSort(v2));
    EXPECT_EQ(v2, std::vector<int>({5}));

    std::vector<int> v3 = {};
    EXPECT_FALSE(algo::bubbleSort(v3)); // Empty vector case
    EXPECT_EQ(v3, std::vector<int>({})); // Should remain empty
}

TEST(AlgoTests, MergeSort)
{
    std::vector<int> v = {38, 27, 43, 3, 9, 82, 10};
    algo::mergeSort(v);
    EXPECT_EQ(v, std::vector<int>({3, 9, 10, 27, 38, 43, 82}));

    std::vector<int> v2 = {5};
    algo::mergeSort(v2);
    EXPECT_EQ(v2, std::vector<int>({5}));

    std::vector<int> v3 = {};
    algo::mergeSort(v3); // Empty vector case
    EXPECT_EQ(v3, std::vector<int>({})); // Should remain empty
}

TEST(AlgoTests, splitStringLoop)
{
	std::string s = "A string that needs to be split";
	std::vector<std::string> split = algo::splitStringLoop(s);
	EXPECT_EQ(split, std::vector<std::string>(
		   { "A", "string", "that", "needs", "to", "be", "split" }
	));

	s = "dontsplit";
	split = algo::splitStringLoop(s);
	EXPECT_EQ(split, std::vector<std::string>({ "dontsplit" }));

	s = "newline\ntab\twhite space";
	split = algo::splitStringLoop(s);
	EXPECT_EQ(split, std::vector<std::string>(
		{ "newline", "tab", "white", "space" }
	));
}

TEST(AlgoTests, splitStringStream)
{
	std::string s = "A string that needs to be split";
	std::vector<std::string> split = algo::splitStringStream(s);
	EXPECT_EQ(split, std::vector<std::string>(
		   { "A", "string", "that", "needs", "to", "be", "split" }
	));

	s = "dontsplit";
	split = algo::splitStringStream(s);
	EXPECT_EQ(split, std::vector<std::string>({ "dontsplit" }));

	s = "newline\ntab\twhite space";
	split = algo::splitStringStream(s);
	EXPECT_EQ(split, std::vector<std::string>(
		{ "newline", "tab", "white", "space"}
	));
}

TEST(MatrixTests, SwapMatrixRow) {
    std::vector<std::vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

	algo::swapMatrixRow(mat, 0, 1);
    EXPECT_EQ(mat[0], std::vector<int>({4, 5, 6}));
    EXPECT_EQ(mat[1], std::vector<int>({1, 2, 3}));
}

TEST(MatrixTests, SwapMatrixColumn) {
    std::vector<std::vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

	algo::swapMatrixColumn(mat, 0, 2);
    EXPECT_EQ(mat[0], std::vector<int>({3, 2, 1}));
    EXPECT_EQ(mat[1], std::vector<int>({6, 5, 4}));
}

TEST(MatrixTests, ReverseMatrixRow) {
    std::vector<std::vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

	algo::reverseMatrixRow(mat, 1);
    EXPECT_EQ(mat[1], std::vector<int>({6, 5, 4}));
}

TEST(MatrixTests, ReverseMatrixColumn) {
    std::vector<std::vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

	algo::reverseMatrixColumn(mat, 1);
    EXPECT_EQ(mat[0][1], 8);
    EXPECT_EQ(mat[1][1], 5);
    EXPECT_EQ(mat[2][1], 2);
}

// Main function for running tests
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // Append custom nanosecond listener.
	if (NANOSECONDS) {
    	// Get the default listeners
    	testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
    	// Append the custom listener, ensuring the default one is still valid
    	listeners.Append(new NanosecondListener(listeners.Release(listeners.default_result_printer())));
	}

    return RUN_ALL_TESTS();
}
