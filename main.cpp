#include <QCoreApplication>

#include "book.h"
#include "bookstore.h"

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <limits>
#include <cctype>

using std::cout;
using std::cin;
using std::list;
using std::endl;
using std::string;
using std::getline;
using std::isdigit;
using std::array;
using std::exception;
using std::numeric_limits;
using std::streamsize;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    BookStore store;
    int opt = 0;

    do{
        cout << "--- BookStore Menu ---" << endl;
        cout << "1. Add a Book" << endl;
        cout << "2. Search by Title" << endl;
        cout << "3. Search by ISBN" << endl;
        cout << "4. View Catalogue" << endl;
        cout << "5. Show Auditlog" << endl;
        cout << "6. Exit" << endl;
        cout << "Type your option: ";

        cin >> opt;

        if(cin.fail()){
            cout << "Error, invalid value, please use a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opt){
        case 1:{
            string title, author, isbnString;

            cout << "Type Book Titulo: ";
            getline(cin, title);

            cout << "Type Book Author: ";
            getline(cin, author);

            cout << "Type Book ISBN (13 digits, no spaces inbetween): ";
            getline(cin, isbnString);

            if (isbnString.length() != 13) {
                cout << "Error: ISBN MUST BE EXACLTY 13 DIGITS IN LENGTH.\n";
                break;
            }


            bool isbnIsValid = true;
            for (char const &c : isbnString) {
                if (isdigit(c) == 0) {
                    cout << "Error: ISBN MAY ONLY CONTAIN INTEGERS.\n";
                    isbnIsValid = false;
                    break;
                }
            }

            if (!isbnIsValid) {
                break;
            }

            try {
                array<int, 13> isbnArray = store.stringToIsbnArray(isbnString);
                Book newBook(title, author, isbnArray);
                cout << "Book added successfully!" << endl;
                store.insertBook(newBook);

            } catch (const exception& e) {
                cout << "Error, Could not Proccess book correctly: " << e.what() << endl;
            }
            break;
        }
        case 2:{
            string title;
            cout << "Insert Book Title: ";
            getline(cin, title);

            int index = store.searchBookByTitle(title);

            if (index != -1) {
                cout << "Book FOUND at: " << index << endl;
                cout << "  Title: " << store.catalogue[index].title << endl;
                cout << "  Author:  " << store.catalogue[index].author << endl;
            } else {
                cout << "Book NOT FOUND." << endl;
            }
            break;
        }
        case 3:{
            string isbnString;
            cout << "Insert the ISBN for the book you want (13 digits, no spaces): ";
            getline(cin, isbnString);

            if (isbnString.length() != 13) {
                cout << "Error: ISBN must be exactly 13 digits." << endl;
                break;
            }

            bool isbnIsValid = true;
            for (char const &c : isbnString) {
                if (isdigit(c) == 0) {
                    cout << "Error: ISBN MAY ONLY CONTAIN INTEGERS." << endl;
                    isbnIsValid = false;
                    break;
                }
            }

            if (!isbnIsValid) {
                break;
            }


            int index = store.searchBookByIsbn(isbnString);

            if (index != -1) {
                cout << "Book found at: " << index << endl;
                cout << "  Title " << store.catalogue[index].title << endl;
                cout << "  Author:  " << store.catalogue[index].author << endl;
            } else {
                cout << "Book not FOUND." << endl;
            }
            break;
        }
        case 5:
            cout << "----------- Auditlog -----------" << endl;

            if(store.audit.empty()){
                cout << "Audit is empty." << endl;
            }else{

                for (const auto& el: store.audit) {
                    cout << el;
                }
            }
            cout << "--------------------------------" << endl;
            break;
        case 4: {
            cout << "----------- Catalogue -----------" << endl;
            int i = 0;
            for(const auto& b: store.catalogue){
                string isbn = "";
                for(int j = 0; j < 13; j++){
                    isbn += std::to_string(b.isbn[j]);
                }
                cout << i << ". Title: " << b.title << " || Author: " << b.author << " || ISBN [" << isbn << "]" << endl;
                i++;
            }
            cout << "--------------------------------" << endl;
            break;
        }
        case 6:
            cout << "END OF PROGRAM." << endl;
            break;
        default:
            cout << "Invalid Input, try again." << endl;
            break;
        }
    }while(opt != 6);

    return a.exec();
}

