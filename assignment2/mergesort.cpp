#include "mergesort.h"

void merge(std::vector<long long>& a, int l, int m, int r, long long* compares, long long* memaccess) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<long long> L(n1);
    std::vector<long long> R(n2);

    // Copy to temp arrays
    for (int i = 0; i < n1; ++i) {
        (*memaccess)++;  // a[l+i] access
        L[i] = a[l + i];
    }
    for (int j = 0; j < n2; ++j) {
        (*memaccess)++;  // a[m+1+j] access
        R[j] = a[m + 1 + j];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        (*compares)++;  // L[i] <= R[j] comparison
        (*memaccess)++;  // L[i] access
        (*memaccess)++;  // R[j] access
        
        if (L[i] <= R[j]) {
            (*memaccess)++;  // a[k] access
            a[k] = L[i];
            (*memaccess)++;  // L[i] access (already counted, conservative)
            ++i;
        } else {
            (*memaccess)++;  // a[k] access
            a[k] = R[j];
            (*memaccess)++;  // R[j] access (already counted, conservative)
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        (*memaccess)++;  // L[i] access
        (*memaccess)++;  // a[k] access
        a[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        (*memaccess)++;  // R[j] access
        (*memaccess)++;  // a[k] access
        a[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<long long>& a, int left, int right, long long* compares, long long* memaccess) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid, compares, memaccess);
    mergeSort(a, mid + 1, right, compares, memaccess);
    merge(a, left, mid, right, compares, memaccess);
}
