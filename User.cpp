#include "User.h"
#include <iostream>

using namespace std;

User::User(const string& fname, const string& lname, const string& natId, int userAge, const string& uname, const string& pass)
    : firstName(fname), lastName(lname), nationalId(natId), age(userAge), username(uname), password(pass) {}

User::~User() {}

string User::getUsername() const {
    return username;
}

string User::getFullName() const {
    return firstName + " " + lastName;
}

string User::getNationalID() const {
    return nationalId; 
}

bool User::checkPassword(const string& pass) const {
    return password == pass;
}

void User::changeInfo(const string& newFirstName, const string& newLastName, int newAge) {
    this->firstName = newFirstName;
    this->lastName = newLastName;
    this->age = newAge;
}

void User::displayInfo() const {
    cout << "Full Name: " << getFullName() << endl;
    cout << "National ID: " << getNationalID() << endl;

    cout << "Username: " << getUsername() << endl; 
    cout << "Age: " << age << endl;
}