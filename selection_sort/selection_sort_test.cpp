#include "selection_sort.hpp"
#include <gtest/gtest.h>

TEST(SelectionSortTest, BasicTest) {
    std::vector<int> A = {9, 2, 4, 1, 6};
    SelectionSort(A);
    EXPECT_EQ(A, std::vector<int>({1, 2, 4, 6, 9}));
}

TEST(SelectionSortTest, LongTest) {
    std::vector<int> A = {71, 102, 31, 29, 5, 364, 1021, 0, 97, 89, 63, 8, 33, 235};
    SelectionSort(A);
    EXPECT_EQ(A, std::vector<int>({0, 5, 8, 29, 31, 33, 63, 71, 89, 97, 102, 235, 364, 1021}));
}

TEST(SelectionSortTest, ZeroTest) {
    std::vector<int> A = {0, 0, 0, 0, 0};
    SelectionSort(A);
    EXPECT_EQ(A, std::vector<int>({0, 0, 0, 0, 0}));
}

TEST(SelectionSortTest, AllEqualTest) {
    std::vector<int> A = {1, 1, 1, 1, 1};
    SelectionSort(A);
    EXPECT_EQ(A, std::vector<int>({1, 1, 1, 1, 1}));
}

