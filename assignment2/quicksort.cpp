#include "quicksort.h"

int partition(long long A[], int lo, int hi, long long* compares, long long* memaccess) {
    (*memaccess)++; // A[lo] access
    long long pivot = A[lo];
    
    int i = lo;
    int j = hi + 1;

    while (true) {
        do {
            ++i; // Move i right until A[i] >= pivot or i == hi
            (*memaccess)++; // A[i] access
            (*compares)++; // A[i] < pivot comparison
        } while (i <= hi && A[i] < pivot);
        
        do {
            --j; // Move j left until A[j] <= pivot or j == lo  
            (*memaccess)++; // A[j] access
            (*compares)++; // pivot < A[j] comparison
        } while (j >= lo && pivot < A[j]);
        
        if (i >= j) break;
        
        std::swap(A[i], A[j]);
        (*memaccess) += 2; // swap reads both A[i] and A[j]
    }
    
    std::swap(A[lo], A[j]);
    (*memaccess) += 2; // final swap
    return j;
}

void quickSort(long long A[], int lo, int hi, long long* compares, long long* memaccess) {
    if (hi <= lo) return;
    int j = partition(A, lo, hi, compares, memaccess);  
    quickSort(A, lo, j - 1, compares, memaccess);
    quickSort(A, j + 1, hi, compares, memaccess);
}
