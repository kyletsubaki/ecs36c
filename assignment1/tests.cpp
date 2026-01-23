#include <cassert>
#include <iostream>
#include <vector>
#include "Book.h"
#include "search.h"

int count_matches_linear(const std::vector<Book>& newbooks, const std::vector<Book>& requests) {
    int count = 0;
    for (const auto& request : requests) {
        if (linearSearch(newbooks, request)) count++;
    }
    return count;
}

int count_matches_binary_sorted(const std::vector<Book>& newbooks, const std::vector<Book>& requests) {
    std::vector<Book> sorted = sortBooks(newbooks);
    int count = 0;
    for (const auto& request : requests) {
        if (binarySearch(sorted, request)) count++;
    }
    return count;
}

int count_matches_recursive(const std::vector<Book>& newbooks, const std::vector<Book>& requests) {
    std::vector<Book> sorted = sortBooks(newbooks);
    int count = 0;
    for (const auto& request : requests) {
        if (recursiveBinarySearch(sorted, request, 0, static_cast<int>(sorted.size()) - 1)) count++;
    }
    return count;
}

// Test 1: Test everything for match
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

// Test 2: Linear miss 
void test_linear_miss() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests = { {124, "english", "new"} };
    assert(count_matches_linear(newbooks, requests) == 0);
}

// Test 3: Linear empty newbooks
void test_empty_newbooks() {
    std::vector<Book> newbooks;
    std::vector<Book> requests = { {123, "english", "new"} };
    assert(count_matches_linear(newbooks, requests) == 0);
}

// Test 4: Linear empty requests
void test_empty_requests() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests;
    assert(count_matches_linear(newbooks, requests) == 0);
}

// Test 5: Linear Mmltiple matches 
void test_duplicates_newbooks() {
    std::vector<Book> newbooks = { {123, "english", "new"}, {123, "english", "new"} };
    std::vector<Book> requests = { {123, "english", "new"} };
    assert(count_matches_linear(newbooks, requests) == 1);  
}

// Test 6: Linear language mismatch
void test_language_mismatch() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests = { {123, "chinese", "new"} };
    assert(count_matches_linear(newbooks, requests) == 0);
}

// Test 7: Linear type mismatch  
void test_type_mismatch() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests = { {123, "english", "used"} };
    assert(count_matches_linear(newbooks, requests) == 0);
}

// Test 8: Binary miss
void test_binary_miss() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests = { {124, "english", "new"} };
    assert(count_matches_binary_sorted(newbooks, requests) == 0);
}

// Test 9: Binary empty newbooks
void test_binary_empty_newbooks() {
    std::vector<Book> newbooks;
    std::vector<Book> requests = { {123, "english", "new"} };
    assert(count_matches_binary_sorted(newbooks, requests) == 0);
}

// Test 10: Binary empty requests
void test_binary_empty_requests() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests;
    assert(count_matches_binary_sorted(newbooks, requests) == 0);
}

// Test 11: Binary multiple matches
void test_binary_duplicates_newbooks() {
    std::vector<Book> newbooks = { {123, "english", "new"}, {123, "english", "new"} };
    std::vector<Book> requests = { {123, "english", "new"} };
    assert(count_matches_binary_sorted(newbooks, requests) == 1);
}

// Test 12: Binary language mismatch
void test_binary_language_mismatch() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests = { {123, "chinese", "new"} };
    assert(count_matches_binary_sorted(newbooks, requests) == 0);
}

// Test 13: Binary type mismatch
void test_binary_type_mismatch() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests = { {123, "english", "used"} };
    assert(count_matches_binary_sorted(newbooks, requests) == 0);
}

// Test 14: Recursive binary miss
void test_recursive_binary_miss() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests = { {124, "english", "new"} };
    assert(count_matches_recursive(newbooks, requests) == 0);
}

// Test 15: Recursive binary empty newbooks
void test_recursive_binary_empty_newbooks() {
    std::vector<Book> newbooks;
    std::vector<Book> requests = { {123, "english", "new"} };
    assert(count_matches_recursive(newbooks, requests) == 0);
}

// Test 16: Recursive binary empty requests
void test_recursive_binary_empty_requests() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests;
    assert(count_matches_recursive(newbooks, requests) == 0);
}

// Test 17: Recursive binary multiple matches
void test_recursive_binary_duplicates_newbooks() {
    std::vector<Book> newbooks = { {123, "english", "new"}, {123, "english", "new"} };
    std::vector<Book> requests = { {123, "english", "new"} };
    assert(count_matches_recursive(newbooks, requests) == 1);
}

// Test 18: Recursive binary language mismatch
void test_recursive_binary_language_mismatch() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests = { {123, "chinese", "new"} };
    assert(count_matches_recursive(newbooks, requests) == 0);
}

// Test 19: Recursive binary type mismatch
void test_recursive_binary_type_mismatch() {
    std::vector<Book> newbooks = { {123, "english", "new"} };
    std::vector<Book> requests = { {123, "english", "used"} };
    assert(count_matches_recursive(newbooks, requests) == 0);
}

int main() {
    // Basic test
    test_all_equivalent();

    // Linear search tests
    test_linear_miss();
    test_empty_newbooks();
    test_empty_requests();
    test_duplicates_newbooks();
    test_language_mismatch();
    test_type_mismatch();

    // Binary search tests
    test_binary_miss();
    test_binary_empty_newbooks();
    test_binary_empty_requests();
    test_binary_duplicates_newbooks();
    test_binary_language_mismatch();
    test_binary_type_mismatch();

    // Recursive search tests
    test_recursive_binary_miss();
    test_recursive_binary_empty_newbooks();
    test_recursive_binary_empty_requests();
    test_recursive_binary_duplicates_newbooks();
    test_recursive_binary_language_mismatch();
    test_recursive_binary_type_mismatch();
    
    std::cout << "All unit tests passed!" << std::endl;
}