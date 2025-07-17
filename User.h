#ifndef USER_H
#define USER_H
using namespace std;
#include <string>

class User {
protected:
    string firstName;
    string lastName;
    string natioalID;
    int age;
    string username;
    string password;

public:
    User(const string& fname,const string& lname, const string& natId, int userAge, const string& uname, const string& pass);

    virtual ~User();

    string getUsername() const;
    string getFullName() const;
    string getNationalID() const;


    bool checkPassword(const string& pass) const;

    virtual void changeInfo(const std::string& newFirstName, const std::string& newLastName, int newAge);
