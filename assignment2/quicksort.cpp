#include "quicksort.h"

int partition(long long A[], int lo, int hi, long long* compares, long long* memaccess) {
    (*memaccess)++; // read A[lo]
    long long pivot = A[lo];
    int i = lo;
    int j = hi + 1;
    while (true) {
        do {
            ++i;
            (*memaccess)++; // read A[i]
            (*compares)++; // A[i] < pivot
        } while (i <= hi && A[i] < pivot);
        do {
            --j;
            (*memaccess)++; // read A[j]
            (*compares)++; // pivot < A[j]
        } while (j >= lo && pivot < A[j]);
        if (i >= j) break;
        std::swap(A[i], A[j]);
        (*memaccess) += 4; // read A[i], read A[j], write A[i], write A[j]
    }
    std::swap(A[lo], A[j]);
    (*memaccess) += 4;
    return j;
}


void quickSort(long long A[], int lo, int hi, long long* compares, long long* memaccess) {
    if (hi <= lo) return;
    int j = partition(A, lo, hi, compares, memaccess);  
    quickSort(A, lo, j - 1, compares, memaccess);
    quickSort(A, j + 1, hi, compares, memaccess);
}
