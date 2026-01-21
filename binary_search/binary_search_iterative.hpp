// Iterative Form
#include <vector>

int BinarySearch(std::vector<int>& arr, int target) {
    int low = 0; // Left
    int high = arr.size() - 1; // Right
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid; // Target found
        } else if (arr[mid] < target) {
            low = mid + 1; // Go right
        } else {
            high = mid - 1; // Go left
        }
    } return -1; // Target not found
}