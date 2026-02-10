// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "mergesort.h"

void MergeSort(std::vector<long long>& numbers, long long* compares, long long* memaccess) {
    MergeSortRecurse(numbers, 0, numbers.size() - 1, compares, memaccess);
}

void MergeSortRecurse(std::vector<long long>& numbers, int i, int k, long long* compares, long long* memaccess) {
    if (i < k) {
        int j = (i + k) / 2;
        MergeSortRecurse(numbers, i, j, compares, memaccess);
        MergeSortRecurse(numbers, j + 1, k, compares, memaccess);
        Merge(numbers, i, j, k, compares, memaccess);
    }
}

void Merge(std::vector<long long>& numbers, int i, int j, int k, long long* compares, long long* memaccess) {

    int mergedSize = k - i + 1;
    std::vector<int> mergedNumbers(mergedSize);

    int leftPos = i;
    int rightPos = j + 1;
    int mergePos = 0;

    while (leftPos <= j && rightPos <= k) {
        (*compares)++;
        (*memaccess) += 2;

        if (numbers[leftPos] < numbers[rightPos]) {
            mergedNumbers[mergePos++] = numbers[leftPos++];
        }
        else {
            mergedNumbers[mergePos++] = numbers[rightPos++];
        }
        (*memaccess)++;
    }

    while (leftPos <= j) {
        mergedNumbers[mergePos++] = numbers[leftPos++];
        (*memaccess)++;
    }

    while (rightPos <= k) {
        mergedNumbers[mergePos++] = numbers[rightPos++];
        (*memaccess)++;
    }

    for (int m = 0; m < mergedSize; ++m) {
        numbers[i + m] = mergedNumbers[m];
        (*memaccess)++;
    }
}