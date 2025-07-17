#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "LinkedList.h"
#include <string>

using namespace std; 

class Account;

class Customer : public User {
private:
    LinkedList<Account*> bankAccounts; 

public:
    Customer(const string& fname, const string& lname, const string& natId, int userAge, const string& uname, const string& pass);
    
    ~Customer();
    void addAccount(Account* newAccount);
    void displayInfo() const override;
    Account* findAccountByCardNumber(const string& cardNumber);
    LinkedList<Account*>& getAccounts();
};

#endif