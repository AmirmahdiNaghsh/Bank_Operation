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