#include "Book.h"

Book::Book(int id, string title, string author)
    : id(id), title(title), author(author), isAvailable(true) {}

void Book::display() {
    cout << "ID: " << id << ", Title: " << title << ", Author: " << author
        << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
}

bool Book::operator<(const Book& other) const {
    return id < other.id;  // For ordering in the set by ID
}
