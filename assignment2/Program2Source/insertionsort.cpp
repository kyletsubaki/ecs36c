// Insertion Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "insertionsort.h"

void InsertionSort(std::vector<long long>& numbers, long long* compares, long long* memaccess) {

    for (int i = 1; i < numbers.size(); ++i) {
        int j = i;

        while (j > 0) {
            (*compares)++;
            (*memaccess) += 2; // numbers[j] and numbers[j-1]

            if (numbers[j] < numbers[j - 1]) {
                long long temp = numbers[j];
                numbers[j] = numbers[j - 1];
                numbers[j - 1] = temp;
                (*memaccess) += 4; // temp + two writes
                --j;
            }
            else {
                break;
            }
        }
    }
}