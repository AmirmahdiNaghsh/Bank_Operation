#include "Customer.h"
#include "Account.h" 
#include <iostream>
using namespace std;

Customer::Customer(const string& fname, const string& lname, const string& natId, int userAge, const string& uname, const string& pass)
    : User(fname, lname, natId, userAge, uname, pass) {}

void Customer::displayInfo() const {
    User::displayInfo(); 
    
    cout << "--- Bank Accounts ---" << endl;
    if (bankAccounts.getCount() == 0) {
        cout << "This customer has no bank accounts." << endl;
    } else {
        bankAccounts.display(); 
    }
}

Customer::~Customer() {
    auto* currentNode = bankAccounts.getHead();
    while (currentNode != nullptr) {
        delete currentNode->getData();
        currentNode = currentNode->getNext();
    }
}

void Customer::addAccount(Account* newAccount) {
    if (bankAccounts.getCount() < 5) {
        bankAccounts.add(newAccount);
    } else {
        cout << "Error: Customer cannot have more than 5 accounts." << endl;
        delete newAccount;
    }
}

Account* Customer::findAccountByCardNumber(const string& cardNumber) {
    return bankAccounts.find([&](Account* acc) {
        return acc->getCardNumber() == cardNumber;
    });
}

LinkedList<Account*>& Customer::getAccounts() {
    return bankAccounts;
}