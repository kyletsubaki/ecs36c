#include "insertionsort.h"

void insertionSort(std::vector<long long>& arr, long long* compares, long long* memaccess) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        (*memaccess) += 2; // key write + arr[i] access
        long long key = arr[i];      
        int j = i - 1;

        // Move elements greater than key one position to the right
        while (j >= 0) {
            (*memaccess) += 2; // arr[j] read, read key
            (*compares)++; // arr[j] > key

            if (arr[j] > key) {
                (*memaccess) += 2; // arr[j+1] write + arr[j] access
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }

        (*memaccess) += 2; // read key + arr[j+1] access
        arr[j + 1] = key;
    }
}
