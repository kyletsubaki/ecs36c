#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include <iostream>

void merge(std::vector<long long>& a, int l, int m, int r, long long* compares, long long* memaccess);
void mergeSort(std::vector<long long>& a, int left, int right, long long* compares, long long* memaccess);

#endif
