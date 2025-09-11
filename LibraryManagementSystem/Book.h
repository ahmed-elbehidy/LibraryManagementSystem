#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isAvailable;

    Book(int id, string title, string author);
    void display();
    bool operator<(const Book& other) const;
};

#endif // BOOK_H
