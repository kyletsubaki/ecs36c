// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

void QuickSort(std::vector<long long>& numbers, long long* compares, long long* memaccess);

void QuickSortRecurse(std::vector<long long>& numbers, int i, int k, long long* compares, long long* memaccess);

int Partition(std::vector<long long>& numbers, int i, int k, long long* compares, long long* memaccess);