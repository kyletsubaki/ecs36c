#include "mergesort.h"

void merge(std::vector<long long>& a, int l, int m, int r, long long* compares, long long* memaccess) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<long long> L(n1);
    std::vector<long long> R(n2);

    // Copy into temp arrays
    for (int i = 0; i < n1; ++i) {
        (*memaccess)++; // read a[l+i]
        (*memaccess)++; // write L[i]
        L[i] = a[l + i];
    }

    for (int j = 0; j < n2; ++j) {
        (*memaccess)++; // read a[m+1+j]
        (*memaccess)++; // write R[j]
        R[j] = a[m + 1 + j];
    }

    int i = 0, j = 0, k = l;

    // Merge back
    while (i < n1 && j < n2) {
        (*memaccess)++; // read L[i]
        (*memaccess)++; // read R[j]
        (*compares)++; // L[i] <= R[j]

        if (L[i] <= R[j]) {
            (*memaccess)++; // read L[i]
            (*memaccess)++; // write a[k]
            a[k] = L[i];
            ++i;
        } else {
            (*memaccess)++; // read R[j]
            (*memaccess)++; // write a[k]
            a[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        (*memaccess)++; // read L[i]
        (*memaccess)++; // write a[k]
        a[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        (*memaccess)++; // read R[j]
        (*memaccess)++; // write a[k]
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
