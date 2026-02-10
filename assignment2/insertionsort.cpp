#include "insertionsort.h"

void insertionSort(std::vector<long long>& arr, long long* compares, long long* memaccess) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        (*memaccess)++; // arr[i] access
        long long key = arr[i];      
        int j = i - 1;

        // Move elements greater than key one position to the right
        while (j >= 0) {
            (*memaccess)++; // arr[j] read
            (*compares)++; // arr[j] > key

            if (arr[j] > key) {
                (*memaccess)++; // arr[j+1] write
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
