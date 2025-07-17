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
