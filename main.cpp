#include <QCoreApplication> // <-- RE-AGREGADO
#include "book.h"
#include "bookstore.h"

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <limits>
#include <stdexcept>
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

int main()
{

    BookStore store;
    int opt = 0;

    do{
        cout << "--- BookStore Menu ---" << endl;
        cout << "1. Add a Book" << endl;
        cout << "2. Search by Title" << endl;
        cout << "3. Search by ISBN" << endl;
        cout << "4. Show Auditlog" << endl;
        cout << "5. Exit" << endl;
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
                cout << "Libro NO ENCONTRADO." << endl;
            }
            break;
        }
        case 3:{
            string isbnString;
            cout << "Insert the ISBN for the book you want (13 digits, no spaces): ";
            getline(cin, isbnString);

            if (isbnString.length() != 13) {
                cout << "Error: El ISBN debe tener exactamente 13 digitos.\n";

                break;
            }


            int index = store.searchBookByIsbn(isbnString);

            if (index != -1) {
                cout << "Libro ENCONTRADO en el indice: " << index << endl;
                cout << "  Titulo: " << store.catalogue[index].title << endl;
                cout << "  Autor:  " << store.catalogue[index].author << endl;
            } else {
                cout << "Libro NO ENCONTRADO." << endl;
            }
            break;
        }
        case 4:
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
        case 5:
            cout << "End of Program" << endl;
            break;
        default:
            cout << "Invalid Input, try again." << endl;
            break;
        }
    }while(opt != 5);

    return 0;
}

