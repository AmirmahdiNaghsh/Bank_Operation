#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "LinkedList.h"

class Customer;

class Admin : public User {
public:

    Admin(const string& fname, const string& lname, const string& natId, int userAge, const string& uname, const string& pass);
    void viewAllUsers(const LinkedList<User*>& users) const;
    void addCustomer(LinkedList<User*>& users, const string& fname, const string& lname, const string& natId, int age, const string& uname, const string& pass);
    bool removeCustomer(LinkedList<User*>& users, const string& username);
    void addAccountToCustomer(Customer* customer, const string& accNum, const string& cardNum, const string& sheba, const string& pin, const string& pin2);
    void changeUserInfo(User* userToChange, const string& newFirstName, const string& newLastName, int newAge);

};

#endif