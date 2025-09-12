# Library Management System

A console-based library management system built with **C++ OOP principles**, **STL containers**, and **file handling**.  
It simulates a real-world library where users can register, log in, and borrow/return books.

##  Features
- **Book Management**: Add, search (by ID, Title, Author), display all books.  
- **User Management**: Register, Login, Logout.  
- **Borrow/Return System**: Track borrowed books per user.  
- **Persistent Storage**: Save and load data from `books.txt` and `users.txt`.  

##  Tech Stack
- **Language**: C++  
- **Concepts**: OOP (Classes: Book, User, LibrarySystem), File Handling  
- **STL Containers**: `set`, `map`, `vector`  
- **Design**: UML Class Diagram included  

##  Project Structure
LibraryManagementSystem/
├── Book.h / Book.cpp
├── User.h
├── LibrarySystem.h / LibrarySystem.cpp
├── main.cpp
├── books.txt (auto-generated)
├── users.txt (auto-generated)


##  How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/ahmed-elbehidy/LibraryManagementSystem.git
   cd LibraryManagementSystem
2. Compile the project:
 g++ main.cpp Book.cpp LibrarySystem.cpp -o library
3. Run:
./library
