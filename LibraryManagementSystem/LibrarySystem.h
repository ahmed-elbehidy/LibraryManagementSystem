#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <set>
#include <map>
#include <vector>
#include <fstream>
#include "Book.h"
#include "User.h"

class LibrarySystem {
private:
    set<Book> books;
    map<string, int> bookTitleToId;
    map<int, bool> borrowedBooks;
    vector<User> users;
    User* currentUser = nullptr;

public:
    void addBook(int id, string title, string author);
    bool searchBookById(int id);
    bool searchBookByTitle(const string& title);
    vector<Book> searchBookByAuthor(const string& author);
    void displayBooks();
    bool borrowBook(int id);
    bool borrowBookByTitle(const string& title);
    bool returnBook(int id);
    bool returnBookByTitle(const string& title);

    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);

    void registerUser(const string& username, const string& password);
    bool loginUser(const string& username, const string& password);
    void logoutUser();
    bool isLoggedIn() const;

    void saveUsers(const string& filename);
    void loadUsers(const string& filename);

    // Accessor to current user
    User* getCurrentUser() { return currentUser; }
};

#endif // LIBRARYSYSTEM_H
