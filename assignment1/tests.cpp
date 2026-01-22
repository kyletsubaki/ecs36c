#include <cassert>
#include <iostream>
#include <vector>
#include "Book.h"
#include "search.h"

int count_matches_linear(const std::vector<Book>& newbooks, const std::vector<Book>& requests) {
    int count = 0;
    for (const auto& request : requests) {
        if (linearSearch(newbooks, request)) {
            count++;
        }
    }
    return count;
}

int count_matches_binary_sorted(const std::vector<Book>& newbooks, const std::vector<Book>& requests) {
    std::vector<Book> sorted = sortBooks(newbooks);
    int count = 0;
    for (const auto& request : requests) {
        if (binarySearch(sorted, request)) {
            count++;
        }
    }
    return count;
}

int count_matches_recursive(const std::vector<Book>& newbooks, const std::vector<Book>& requests) {
    std::vector<Book> sorted = sortBooks(newbooks);
    int count = 0;
    for (const auto& request : requests) {
        if (recursiveBinarySearch(sorted, request, 0, static_cast<int>(sorted.size()) - 1)) {
            count++;
        }
    }
    return count;
}

// Test 1: Linear hit (exact match)
void test_linear_hit() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests = { {123, "english", "new"} };
    assert(count_matches_linear(newbooks, requests) == 1);
}

// Test 2: Linear miss (no match)
void test_linear_miss() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests = { {124, "english", "new"} };
    assert(count_matches_linear(newbooks, requests) == 0);
}

// Test 3: Empty newbooks
void test_empty_newbooks() {
    std::vector<Book> newbooks;
    std::vector<Book> requests = { {123, "english", "new"} };
    assert(count_matches_linear(newbooks, requests) == 0);
}

// Test 4: Empty requests
void test_empty_requests() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests;
    assert(count_matches_linear(newbooks, requests) == 0);
}

// Test 5: Multiple matches (duplicates in newbooks)
void test_duplicates_newbooks() {
    std::vector<Book> newbooks = { {123, "english", "new"}, {123, "english", "new"} };
    std::vector<Book> requests = { {123, "english", "new"} };
    assert(count_matches_linear(newbooks, requests) == 1);  
}

// Test 6: Language mismatch
void test_language_mismatch() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests = { {123, "chinese", "new"} };
    assert(count_matches_linear(newbooks, requests) == 0);
}

// Test 7: Type mismatch  
void test_type_mismatch() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests = { {123, "english", "used"} };
    assert(count_matches_linear(newbooks, requests) == 0);
}

// Test 8: Test everything for match
void test_all_equivalent() {
    std::vector<Book> newbooks = { 
        {100, "english", "new"}, 
        {200, "spanish", "used"},
        {300, "chinese", "digital"}
    };
    std::vector<Book> requests = { 
        {100, "english", "new"},
        {999, "english", "new"}  
    };
    
    assert(count_matches_linear(newbooks, requests) == 1);
    assert(count_matches_binary_sorted(newbooks, requests) == 1);
    assert(count_matches_recursive(newbooks, requests) == 1);
}

int main() {
    test_linear_hit();
    test_linear_miss();
    test_empty_newbooks();
    test_empty_requests();
    test_duplicates_newbooks();
    test_language_mismatch();
    test_type_mismatch();
    test_all_equivalent();
    
    std::cout << "All unit tests passed!";
}


