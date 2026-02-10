// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "quicksort.h"

void QuickSort(std::vector<long long>& numbers, long long* compares, long long* memaccess) {
    QuickSortRecurse(numbers, 0, numbers.size() - 1, compares, memaccess);
}

void QuickSortRecurse(std::vector<long long>& numbers, int i, int k, long long* compares, long long* memaccess) {

    if (i >= k) return;

    int j = Partition(numbers, i, k, compares, memaccess);
    QuickSortRecurse(numbers, i, j, compares, memaccess);
    QuickSortRecurse(numbers, j + 1, k, compares, memaccess);
}

int Partition(std::vector<long long>& numbers, int i, int k, long long* compares, long long* memaccess) {

    int midpoint = i + (k - i) / 2;
    long long pivot = numbers[midpoint];
    (*memaccess)++;

    int l = i;
    int h = k;

    while (true) {
      (*compares)++;
      (*memaccess)++;
        while (numbers[l] < pivot) {
            (*compares)++;
            (*memaccess)++;
            ++l;
        }
      
      (*compares)++;
      (*memaccess)++;
        while (pivot < numbers[h]) {
            (*compares)++;
            (*memaccess)++;
            --h;
        }

        if (l >= h) return h;

        std::swap(numbers[l], numbers[h]);
        (*memaccess) += 4;
        ++l;
        --h;
    }
}
