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
        // Time constructor
        Timer() {
            start = std::chrono::high_resolution_clock::time_point{};
            running = false;
        }

        // Starts timer
        void Reset() {
            running = true;
            start = std::chrono::high_resolution_clock::now();
        }

        // Stops timer and provides the time elapsed in microseconds
        double CurrentTime() const {
            auto end = std::chrono::high_resolution_clock::now();
            double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();
            return elapsed_us;
        }
        
};

// Extracts ISBN, language, and type from the books
std::vector<Book> getBooks(char* file_name) {
    std::vector<Book> books;
    std::ifstream in_file(file_name);
    
    // Error if file doesn't exist or not in file
    if (!in_file) {
        std::cerr << "Error: cannot open file " << file_name << std::endl;
        return books;
    }
    
    // Read the file line by line until end of file
    std::string line;
    while (std::getline(in_file, line)) {
        std::stringstream ss(line); // Parse this line using stringstream for CSV processing
        Book book;
        
        // Read the fields separated by commas
        std::string ISBN_str;
        if (std::getline(ss, ISBN_str, ',') && // Extract ISBN before comma
            std::stringstream(ISBN_str) >> book.ISBN_number && // Convert ISBN string to int
            std::getline(ss, book.language, ',') && // Extract language before comma  
            std::getline(ss, book.type, ',')) { // Extract type 
            books.push_back(book); // Add all fields to book 
        }
    }
    return books;
}

int main(int argc, char* argv[]) {
    // Error if the user doesn't provide a requested book file
    if (argc != 3 && argc != 4) {
        std::cerr << "Usage: ." << argv[0] << " <newBooks.dat> <request.dat> <result_file.dat>\n";
    }

    // Gather file names from the command-line arguments
    char* new_books_file_name = argv[1]; 
    char* requested_books_file_name = argv[2]; 

    // Gather books from the file names
    std::vector<Book> new_books = getBooks(new_books_file_name); 
    std::vector<Book> requested_books = getBooks(requested_books_file_name);

    Timer ct; // Instance of Timer calss

    // Prompt the user to select linear, binary, or recursive binary search
    char search_method;
    std::cout << "Choice of search method ([l]inear, [b]inary, [r]ecursiveBinary)?" << '\n';
    std::cin >> search_method;
    // If invalid input, prompt user again
    while (search_method != 'l' && search_method != 'b' && search_method != 'r') {
        std::cerr << "Incorrect choice" << '\n';
        std::cin >> search_method;
    }

    std::vector<Book> sorted_books; 

    int count = 0; // Count for how many found books
    ct.Reset(); // Start timer
    // If user selects linear, loop through every requested book and put it through linear search
    if (search_method == 'l') {
        for (Book& request : requested_books) {
            if (linearSearch(new_books, request)) {
                count++; // Increment found book if linear search is true
            }
        }
    } else if (search_method == 'b') {  
        sorted_books = sortBooks(new_books); // If user selects binary, sort the new books
        for (Book& request : requested_books) { // Loop through every requested book 
            if (binarySearch(sorted_books, request)) {
                count++; // Increment found book if binary search is true
            }
        }
    } else if (search_method == 'r') { // Same procedure as iterative binary
        sorted_books = sortBooks(new_books);
        for (Book& request : requested_books) {
            if (recursiveBinarySearch(sorted_books, request, 0, sorted_books.size() - 1)) {
                count++;
            }
        }
    }

    // Print the CPU time in microseconds
    std::cout << "CPU time: " << ct.CurrentTime() << " microseconds";

    // If the output file isn't given, name it "found.dat"
    const char* output_file_name; 
    if (argc == 4) {
        output_file_name = argv[3];
    } else {
        output_file_name = "found.dat";
    }

    // Print the amount of books found
    std::ofstream out_file(output_file_name);
    if (out_file) {
        out_file << count << "\n";
    } else {
        std::cerr << "Cannot write to " << output_file_name << std::endl;
    }
}