#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
public:
    int ISBN_number{};
    std::string language;
    std::string type;

    // Default constructor 
    Book() = default;

    // Parameterized constructor
    Book(int i, const std::string& l, const std::string& t) : ISBN_number(i), language(l), type(t) {}

    // Comparison order: ISBN number, language, type
    bool operator<(const Book& other) const {
        if (ISBN_number != other.ISBN_number)
            return ISBN_number < other.ISBN_number;

        if (language != other.language)
            return language < other.language;

        return type < other.type;
    }

    // Returns true if all fields of both Book objects are identical
    bool operator==(const Book& other) const {
        return ISBN_number == other.ISBN_number &&
               language == other.language &&
               type == other.type;
    }
};

#endif
