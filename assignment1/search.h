#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include "Book.h"  

std::vector<Book> sortBooks(std::vector<Book> books);
bool linearSearch(const std::vector<Book>& books, const Book& target);
bool binarySearch(const std::vector<Book>& sorted_books, const Book& target);
bool recursiveBinarySearch(const std::vector<Book>& sorted_books, const Book& target, int left, int right);

#endif