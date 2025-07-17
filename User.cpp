#include "User.h"
#include <iostream>

using namespace std;

User::User(const string& fname, const string& lname, const string& natID, int userAge, const string& uname, const string& pass)
: firstName(fname), lastName(lname), nationalID(natID), age(userAge), username(uname), password(pass){}

User::~User() {
}

string User::getUsername() const {
    return username;
}

string User::getFullName() const {
    return firstName + " " + lastName;
}

string User:: getNatioalID() const{
    return nationalID;
}

bool User::changePassword(const string& pass) const{
    return password == pass;
}

void User::changeInfo(const string& newFirstName, const string& newLastName, int newAge) {
    this->firstName = newFirstName;
    this->lastName = newLastName;
    this->age = newAge;
}

void User::desplayInfo() const {
    cout<< "Full Name: " << fullName() << endl;
    cout<< "Last Name: " << lastName() << endl;
    cout << "NationalID: " << nationalID() << endl;
    cout << "Age: " << age << endl;
}