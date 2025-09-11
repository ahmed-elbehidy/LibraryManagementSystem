#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class User {
public:
    string username;
    string password;
    vector<int> borrowedBookIds;

    User(string uname, string pass)
        : username(uname), password(pass) {}

    bool checkPassword(const string& pass) const {
        return password == pass;
    }

    void borrowBook(int id) {
        borrowedBookIds.push_back(id);
    }

    void returnBook(int id) {
        borrowedBookIds.erase(remove(borrowedBookIds.begin(),
            borrowedBookIds.end(), id),
            borrowedBookIds.end());
    }
};

#endif // USER_H

