#include "book.h"
#include <string>
#include <array>

Book::Book(std::string title, std::string author, std::array<int, 13> isbn): title(title), author(author), isbn(isbn) {}


bool Book::operator<(const Book& obj) const{
    if(this->title.compare(obj.title) < 0){
        return true;
    }else if(this->title.compare(obj.title) == 0){
        if(this->author.compare(obj.author) < 0){
            return true;
        }else
            if(this->isbn < obj.isbn){
                return true;
            }
        }
    return false;
}
