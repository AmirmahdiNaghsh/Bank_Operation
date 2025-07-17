#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
using namespace std;

class User {
protected:
    string firstName;
    string lastName;
    string nationalId;
    int age;
    string username;
    string password;

public:
    // Constructor
    User(const string& fname, const string& lname, const string& natId, 
         int userAge, const string& uname, const string& pass);
    
    // Virtual destructor
    virtual ~User();
    
    // Getters
    string getFirstName() const;
    string getLastName() const;
    string getUsername() const;
    string getFullName() const;
    string getNationalId() const;
    int getAge() const;
    
    // Authentication
    bool checkPassword(const string& pass) const;
    void changePassword(const string& oldPass, const string& newPass);
    
    // User information management
    void changeInfo(const string& newFirstName, const string& newLastName, int newAge);
    
    // Display functions
    virtual void displayInfo() const;
    
    // Pure virtual functions for login and registration
    virtual bool login(const string& username, const string& password) = 0;
    virtual void showMainMenu() = 0;
};

#endif 