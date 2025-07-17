#ifndef USER_H
#define USER_H
using namespace std;
#include <string>

class User {
protected:
    string firstName;
    string lastName;
    string nationalId; 
    int age;
    string username;
    string password;

public:
    User(const std::string& fname, const std::string& lname, const std::string& natId, int userAge, const std::string& uname, const std::string& pass);

    virtual ~User();

    string getUsername() const;
    string getFullName() const;

    string getNationalID() const;

    bool checkPassword(const std::string& pass) const;

    void changeInfo(const std::string& newFirstName, const std::string& newLastName, int newAge);

    void displayInfo() const;
};

#endif 