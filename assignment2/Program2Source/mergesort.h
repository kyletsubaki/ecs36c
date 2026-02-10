// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

void MergeSort(std::vector<long long>& numbers, long long* compares, long long* memaccess);

void MergeSortRecurse(std::vector<long long>& numbers, int i, int k, long long* compares, long long* memaccess);

void Merge(std::vector<long long>& numbers, int i, int j, int k, long long* compares, long long* memaccess);