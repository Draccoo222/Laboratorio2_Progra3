#ifndef BOOKSTORE_H
#define BOOKSTORE_H
#include "book.h"
#include <vector>
#include <string>
#include <list>

class BookStore
{
    public:
        std::vector<Book> catalogue;
        std::list<std::string> audit;

        BookStore();

        void insertBook(Book book);
        int searchBookByTitle(std::string title);
        int searchBookByIsbn(std::string isbn);

        std::vector<int> sortIndicesByIsbn(const std::vector<Book>&);
        std::array<int, 13> stringToIsbnArray(const std::string& input);
        std::string getTimeStamp();

};

#endif // BOOKSTORE_H
