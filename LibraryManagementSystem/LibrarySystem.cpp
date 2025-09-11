#include "LibrarySystem.h"
#include <sstream>
#include <algorithm>

// Add a book
void LibrarySystem::addBook(int id, string title, string author) {
    if (books.find(Book(id, "", "")) != books.end()) {
        cout << "Error: A book with ID " << id << " already exists." << endl;
        return;
    }
    if (bookTitleToId.find(title) != bookTitleToId.end()) {
        cout << "Error: A book with the title \"" << title << "\" already exists." << endl;
        return;
    }

    books.insert(Book(id, title, author));
    bookTitleToId[title] = id;
    cout << "Book added successfully!" << endl;
}

// Search
bool LibrarySystem::searchBookById(int id) {
    auto it = books.find(Book(id, "", ""));
    return it != books.end();
}

bool LibrarySystem::searchBookByTitle(const string& title) {
    return bookTitleToId.find(title) != bookTitleToId.end();
}

vector<Book> LibrarySystem::searchBookByAuthor(const string& author) {
    vector<Book> results;
    for (auto& book : books) {
        if (book.author == author) {
            results.push_back(book);
        }
    }
    return results;
}

// Display
void LibrarySystem::displayBooks() {
    if (books.empty()) {
        cout << "The library is empty." << endl;
        return;
    }
    for (auto book : books) {
        book.display();
    }
}

// Borrow / Return
bool LibrarySystem::borrowBook(int id) {
    if (!currentUser) {
        cout << "Please login first!" << endl;
        return false;
    }

    auto it = books.find(Book(id, "", ""));
    if (it != books.end() && borrowedBooks.find(id) == borrowedBooks.end()) {
        borrowedBooks[id] = true;
        const_cast<Book&>(*it).isAvailable = false;
        currentUser->borrowBook(id);
        cout << "Book borrowed successfully!" << endl;
        return true;
    }
    cout << "Book not available or already borrowed." << endl;
    return false;
}

bool LibrarySystem::borrowBookByTitle(const string& title) {
    if (searchBookByTitle(title)) {
        int id = bookTitleToId[title];
        return borrowBook(id);
    }
    cout << "Book not found by title." << endl;
    return false;
}

bool LibrarySystem::returnBook(int id) {
    if (!currentUser) {
        cout << "Please login first!" << endl;
        return false;
    }

    if (borrowedBooks.find(id) != borrowedBooks.end()) {
        borrowedBooks.erase(id);
        auto it = books.find(Book(id, "", ""));
        if (it != books.end()) {
            const_cast<Book&>(*it).isAvailable = true;
            currentUser->returnBook(id);
            cout << "Book returned successfully!" << endl;
            return true;
        }
    }
    cout << "Invalid book ID or not borrowed." << endl;
    return false;
}

bool LibrarySystem::returnBookByTitle(const string& title) {
    if (searchBookByTitle(title)) {
        int id = bookTitleToId[title];
        return returnBook(id);
    }
    cout << "Invalid book title or not borrowed." << endl;
    return false;
}

// File handling for books
void LibrarySystem::saveToFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error: Could not open file for saving." << endl;
        return;
    }
    for (auto& book : books) {
        outFile << book.id << "|" << book.title << "|" << book.author
            << "|" << book.isAvailable << endl;
    }
    outFile.close();
    cout << "Books saved to file successfully!" << endl;
}

void LibrarySystem::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "No saved data found, starting fresh." << endl;
        return;
    }

    books.clear();
    bookTitleToId.clear();
    borrowedBooks.clear();

    int id;
    string title, author;
    bool available;
    string line;
    while (getline(inFile, line)) {
        size_t p1 = line.find("|");
        size_t p2 = line.find("|", p1 + 1);
        size_t p3 = line.find("|", p2 + 1);

        id = stoi(line.substr(0, p1));
        title = line.substr(p1 + 1, p2 - p1 - 1);
        author = line.substr(p2 + 1, p3 - p2 - 1);
        available = stoi(line.substr(p3 + 1));

        Book book(id, title, author);
        book.isAvailable = available;
        books.insert(book);
        bookTitleToId[title] = id;
        if (!available) borrowedBooks[id] = true;
    }
    inFile.close();
    cout << "Books loaded from file successfully!" << endl;
}

// User Management
void LibrarySystem::registerUser(const string& username, const string& password) {
    for (auto& u : users) {
        if (u.username == username) {
            cout << "Error: Username already exists!" << endl;
            return;
        }
    }
    users.push_back(User(username, password));
    cout << "User registered successfully!" << endl;
}

bool LibrarySystem::loginUser(const string& username, const string& password) {
    for (auto& u : users) {
        if (u.username == username && u.checkPassword(password)) {
            currentUser = &u;
            cout << "Login successful! Welcome, " << username << endl;
            return true;
        }
    }
    cout << "Invalid username or password." << endl;
    return false;
}

void LibrarySystem::logoutUser() {
    if (currentUser) {
        cout << "User " << currentUser->username << " logged out." << endl;
        currentUser = nullptr;
    }
    else {
        cout << "No user is currently logged in." << endl;
    }
}

bool LibrarySystem::isLoggedIn() const {
    return currentUser != nullptr;
}

// Save/Load users
void LibrarySystem::saveUsers(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error: Could not open user file for saving." << endl;
        return;
    }
    for (auto& u : users) {
        outFile << u.username << "|" << u.password << "|";
        for (size_t i = 0; i < u.borrowedBookIds.size(); i++) {
            outFile << u.borrowedBookIds[i];
            if (i < u.borrowedBookIds.size() - 1) outFile << ",";
        }
        outFile << "\n";
    }
    outFile.close();
    cout << "Users saved successfully!" << endl;
}

void LibrarySystem::loadUsers(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "No saved users found, starting fresh." << endl;
        return;
    }
    users.clear();
    string line;
    while (getline(inFile, line)) {
        size_t p1 = line.find("|");
        size_t p2 = line.find("|", p1 + 1);
        if (p1 == string::npos || p2 == string::npos) continue;

        string uname = line.substr(0, p1);
        string pass = line.substr(p1 + 1, p2 - p1 - 1);
        User u(uname, pass);

        string borrowed = line.substr(p2 + 1);
        stringstream ss(borrowed);
        string token;
        while (getline(ss, token, ',')) {
            if (!token.empty()) {
                u.borrowedBookIds.push_back(stoi(token));
            }
        }
        users.push_back(u);
    }
    inFile.close();
    cout << "Users loaded successfully!" << endl;
}
