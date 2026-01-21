#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
    private:
        int getTypeOrder(const std::string& type) const {
            if (type == "new") return 0;
            if (type == "used") return 1;
            if (type == "digital") return 2;
            return 3; // Unkown input
        }

    public:
        int ISBN_number;
        std::string language, type;
        Book() = default;

        bool operator<(const Book& other) const {
            if (ISBN_number != other.ISBN_number) return ISBN_number < other.ISBN_number;
            
            int type1 = getTypeOrder(type);
            int type2 = getTypeOrder(other.type);
            if (type1 != type2) return type1 < type2;
            return language < other.language;
        }

        bool operator==(const Book& other) const { 
            return ISBN_number == other.ISBN_number && language == other.language && type == other.type;
        }
};

#endif