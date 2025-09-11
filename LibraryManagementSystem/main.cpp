#include <iostream>
#include "LibrarySystem.h"
using namespace std;

int main() {
    LibrarySystem library;
    library.loadFromFile("books.txt");
    library.loadUsers("users.txt");

    int choice, id;
    string title, author, username, password;

    do {
        cout << "\n=========== Library System Menu ===========\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Logout\n";
        cout << "4. Display all books\n";
        cout << "5. Add a book\n";
        cout << "6. Search for a book by ID\n";
        cout << "7. Search for a book by title\n";
        cout << "8. Search for a book by author\n";
        cout << "9. Borrow a book by ID\n";
        cout << "10. Borrow a book by title\n";
        cout << "11. Return a book by ID\n";
        cout << "12. Return a book by title\n";
        cout << "13. View my borrowed books\n";
        cout << "14. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            library.registerUser(username, password);
            break;
        case 2:
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            library.loginUser(username, password);
            break;
        case 3:
            library.logoutUser();
            break;
        case 4:
            library.displayBooks();
            break;
        case 5:
            cout << "Enter book ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter book title: ";
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            library.addBook(id, title, author);
            break;
        case 6:
            cout << "Enter book ID to search: ";
            cin >> id;
            cout << (library.searchBookById(id) ? "Book found!" : "Book not found.") << endl;
            break;
        case 7:
            cout << "Enter book title to search: ";
            cin.ignore();
            getline(cin, title);
            cout << (library.searchBookByTitle(title) ? "Book found!" : "Book not found.") << endl;
            break;
        case 8:
            cout << "Enter author to search: ";
            cin.ignore();
            getline(cin, author);
            for (auto& b : library.searchBookByAuthor(author)) b.display();
            break;
        case 9:
            if (!library.isLoggedIn()) { cout << "Please login first!" << endl; break; }
            cout << "Enter book ID to borrow: ";
            cin >> id;
            library.borrowBook(id);
            break;
        case 10:
            if (!library.isLoggedIn()) { cout << "Please login first!" << endl; break; }
            cout << "Enter book title to borrow: ";
            cin.ignore();
            getline(cin, title);
            library.borrowBookByTitle(title);
            break;
        case 11:
            if (!library.isLoggedIn()) { cout << "Please login first!" << endl; break; }
            cout << "Enter book ID to return: ";
            cin >> id;
            library.returnBook(id);
            break;
        case 12:
            if (!library.isLoggedIn()) { cout << "Please login first!" << endl; break; }
            cout << "Enter book title to return: ";
            cin.ignore();
            getline(cin, title);
            library.returnBookByTitle(title);
            break;
        case 13:
            if (!library.isLoggedIn()) { cout << "Please login first!" << endl; break; }
            cout << "Books borrowed by you:\n";
            for (auto id : library.getCurrentUser()->borrowedBookIds) {
                cout << "Book ID: " << id << endl;
            }
            break;
        case 14:
            library.saveToFile("books.txt");
            library.saveUsers("users.txt");
            cout << "Exiting system. Data saved!" << endl;
            break;
        default:
            cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 14);

    return 0;
}
