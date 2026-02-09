#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include <iomanip>

int partition(long long A[], int lo, int hi, long long* compares, long long* memaccess);
void quickSort(long long A[], int lo, int hi, long long* compares, long long* memaccess);

#endif