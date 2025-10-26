#include "bookstore.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <algorithm>
#include <numeric>

std::string BookStore::getTimeStamp(){
    time_t tStamp;
    time(&tStamp);
    return ctime(&tStamp);
}

void BookStore::insertBook(Book b){
    this->catalogue.push_back(b);

    std::sort(this->catalogue.begin(), this->catalogue.end());

    std::cout << "Added Book || Title: " << b.title << "|| At: " << getTimeStamp() << std::endl;

    audit.push_back("Added Book || Title: " + b.title + "|| At: " + getTimeStamp());
}


int BookStore::searchBookByIsbn(std::string isbn){
    std::array<int, 13> arrayI = stringToIsbnArray(isbn);
    std::vector<int> indices = sortIndicesByIsbn(catalogue);

    int low = 0;
    int high = indices.size() - 1;

    while(high >= low){

        int mid = low +(high - low)/2;
        int book_index = indices.at(mid);

        if(this->catalogue.at(mid).isbn == arrayI){
           return book_index;
        }
        else if(this->catalogue.at(mid).isbn < arrayI){
            low = mid - 1;
        }
        else{
            high = mid + 1;
        }
    }
    return -1;
}

int BookStore::searchBookByTitle(std::string title){
    int low = 0;
    int high = this->catalogue.size() - 1;
    while(high >= low){

        int mid = low +(high - low)/2;

        if(this->catalogue.at(mid).title == title){
            return mid;
        }
        else if(this->catalogue.at(mid).title < title){
            low = mid - 1;
        }
        else{
            high = mid - 1;
        }
    }
    return -1;
}


std::vector<int> BookStore::sortIndicesByIsbn(const std::vector<Book>& n){
    std::vector<int> ind(n.size());

    std::iota(ind.begin(), ind.end(), 0);

    std::sort(ind.begin(), ind.end(), [&n](int i1, int i2){
        return n.at(i1).isbn < n.at(i2).isbn;
    });

    return ind;
}

std::array<int, 13> BookStore::stringToIsbnArray(const std::string& input){
    std::array<int, 13> isbn;
    for (int i = 0; i < 13; ++i) {
        char num = input[i];
        isbn[i] = num - '0';
    }
    return isbn;
}








