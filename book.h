#ifndef BOOK_H
#define BOOK_H


#include <string>
#include <array>

class Book
{
    public:
    std::string title;
    std::string author;
    std::array<int, 13> isbn{};

    Book(std::string title,std::string author,std::array<int, 13> isbn);

    bool operator<(const Book&  obj) const;

};

#endif // BOOK_H
