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
    
    User(const string& fname, const string& lname, const string& natId, 
         int userAge, const string& uname, const string& pass);
    
    
    virtual ~User();
    
    
    string getFirstName() const;
    string getLastName() const;
    string getUsername() const;
    string getFullName() const;
    string getNationalId() const;
    int getAge() const;
    
    
    bool checkPassword(const string& pass) const;
    void changePassword(const string& oldPass, const string& newPass);
    
    
    void changeInfo(const string& newFirstName, const string& newLastName, int newAge);
    
    
    virtual void displayInfo() const;
    
    
    virtual bool login(const string& username, const string& password) = 0;
    virtual void showMainMenu() = 0;
};

#endif 