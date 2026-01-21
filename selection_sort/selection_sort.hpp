#include <vector>
#include <algorithm>

void SelectionSort(std::vector<int>& A) {
    int n = static_cast<int>(A.size());
    for (int i = 0; i < n - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < n; ++j) {
            if (A[j] < A[min_index]) {
                min_index = j;
            }
        }
        std::swap(A[i], A[min_index]);
    }
}