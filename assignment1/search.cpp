#include "search.h"
#include "Book.h"
#include <algorithm>

std::vector<Book> sortBooks(std::vector<Book> books) {
    std::sort(books.begin(), books.end());
    return books;
}

bool linearSearch(const std::vector<Book>& books, const Book& target) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i] == target) {
            return true;  // Found 
        }
    }
    return false;  // Not found
}

bool binarySearch(const std::vector<Book>& sorted_books, const Book& target) {
    int left = 0;
    int right = sorted_books.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;  
        
        if (sorted_books[mid] == target) return true; // Found
        if (sorted_books[mid] < target) {
            left = mid + 1; // Search right half
        } else {
            right = mid - 1; // Search left half
        }
    }
    return false; // Not found
}

bool recursiveBinarySearch(const std::vector<Book>& sorted_books, const Book& target, int left, int right) {
    if (left > right) {
        return false;
    }
    
    int mid = left + (right - left) / 2;
    
    // Base case
    if (sorted_books[mid] == target) {
        return true; // Found
    }
    
    // Recursive cases
    if (sorted_books[mid] < target) {
        // Search right half
        return recursiveBinarySearch(sorted_books, target, mid + 1, right);
    } else {
        // Search left half
        return recursiveBinarySearch(sorted_books, target, left, mid - 1);
    }
}