#include "User.h"
#include <iostream>

using namespace std;

User::User(const string& fname, const string& lname, const string& natId, 
           int userAge, const string& uname, const string& pass)
    : firstName(fname), lastName(lname), nationalId(natId), 
      age(userAge), username(uname), password(pass) {
}

User::~User() {}


string User::getFirstName() const {
    return firstName;
}

string User::getLastName() const {
    return lastName;
}

string User::getUsername() const {
    return username;
}

string User::getFullName() const {
    return firstName + " " + lastName;
}

string User::getNationalId() const {
    return nationalId;
}

int User::getAge() const {
    return age;
}


bool User::checkPassword(const string& pass) const {
    return password == pass;
}

void User::changePassword(const string& oldPass, const string& newPass) {
    if (checkPassword(oldPass)) {
        password = newPass;
        cout << "Password changed successfully." << endl;
    } else {
        cout << "Incorrect old password." << endl;
    }
}


void User::changeInfo(const string& newFirstName, const string& newLastName, int newAge) {
    firstName = newFirstName;
    lastName = newLastName;
    age = newAge;
    cout << "User information updated successfully." << endl;
}


void User::displayInfo() const {
    cout << "=== User Information ===" << endl;
    cout << "Full Name: " << getFullName() << endl;
    cout << "National ID: " << nationalId << endl;
    cout << "Username: " << username << endl;
    cout << "Age: " << age << endl;
}