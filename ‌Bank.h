#ifdef BANK_H
#define BANK_H

#include "LinkedList.h"
#include <string>

class User;
class Customer;
class Admin;
class Account;

using namespace std;

class Bank {
private:
    LinkedList<User*> users; 
    User* currentUser;
    User* findUserByUsername(const string& username);
    Account* findAccountByCardNumber(const string& cardNumber);
    