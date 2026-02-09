#include "insertionsort.h"

void insertionSort(std::vector<long long>& arr, long long* compares, long long* memaccess) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        (*memaccess)++;  // arr[i] access
        long long key = arr[i];  
        
        int j = i - 1;
        (*memaccess)++;  // arr[j] access

        // Move elements greater than key one position to the right
        while (j >= 0 && arr[j] > key) {
            (*compares)++;   // arr[j] > key comparison
            (*memaccess)++;  // arr[j] access 
            (*memaccess)++;  // arr[j+1] access
            arr[j + 1] = arr[j];
            j--;
        }

        (*memaccess)++;  // arr[j+1] access
        arr[j + 1] = key;
    }
}
