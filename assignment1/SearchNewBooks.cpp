#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono> // NOLINT(build/c++11)
#include "Book.h"
#include "search.h"

class Timer {
    private:
        std::chrono::high_resolution_clock::time_point start;
        bool running;
    
    public:
        Timer() {
            start = std::chrono::high_resolution_clock::time_point{};
            running = false;
        }

        void Reset() {
            running = true;
            start = std::chrono::high_resolution_clock::now();
        }

        double CurrentTime() const {
            auto end = std::chrono::high_resolution_clock::now();
            double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();
            return elapsed_us;
        }
        
};

std::vector<Book> getBooks(char* file_name) {
    std::vector<Book> books;
    std::ifstream in_file(file_name);
    
    if (!in_file) {
        std::cerr << "Error: cannot open file " << file_name << std::endl;
        return books;
    }
    
    std::string line;
    while (std::getline(in_file, line)) {
        std::stringstream ss(line);
        Book book;
        
        // Read the fields separated by commas
        std::string ISBN_str;
        if (std::getline(ss, ISBN_str, ',') &&
            std::stringstream(ISBN_str) >> book.ISBN_number &&
            std::getline(ss, book.language, ',') &&
            std::getline(ss, book.type, ',')) {
            books.push_back(book);
        }
    }
    return books;
}

int main(int argc, char* argv[]) {
    if (argc != 3 && argc != 4) {
        std::cerr << "Usage: ." << argv[0] << " <newBooks.dat> <request.dat> <result_file.dat>\n";
    }

    char* new_books_file_name = argv[1];
    char* requested_books_file_name = argv[2];

    std::vector<Book> new_books = getBooks(new_books_file_name);
    std::vector<Book> requested_books = getBooks(requested_books_file_name);

    Timer ct;

    char search_method;
    std::cout << "Choice of search method ([l]inear, [b]inary, [r]ecursiveBinary)?" << '\n';
    std::cin >> search_method;
    while (search_method != 'l' && search_method != 'b' && search_method != 'r') {
        std::cerr << "Incorrect choice" << '\n';
        std::cin >> search_method;
    }

    std::vector<Book> sorted_books;

    int count = 0;
    ct.Reset();
    if (search_method == 'l') {
        for (Book& request : requested_books) {
            if (linearSearch(new_books, request)) {
                count++;
            }
        }
    } else if (search_method == 'b') {
        sorted_books = sortBooks(new_books);
        for (Book& request : requested_books) {
            if (binarySearch(sorted_books, request)) {
                count++;
            }
        }
    } else if (search_method == 'r') {
        sorted_books = sortBooks(new_books);
        for (Book& request : requested_books) {
            if (recursiveBinarySearch(sorted_books, request, 0, sorted_books.size() - 1)) {
                count++;
            }
        }
    }

    std::cout << "CPU time: " << ct.CurrentTime() << " microseconds";

    const char* output_file_name; 
    if (argc == 4) {
        output_file_name = argv[3];
    } else {
        output_file_name = "found.dat";
    }

    std::ofstream out_file(output_file_name);
    if (out_file) {
        out_file << count << "\n";
    } else {
        std::cerr << "Cannot write to " << output_file_name << std::endl;
    }
}
