#include "Bank.h"
#include "Admin.h"
#include "Customer.h"
#include "SavingAccount.h"
#include "CurrentAccount.h"
#include <iostream>
#include <limits>

using namespace std;

Bank::Bank() : currentUser(nullptr) {
    srand(time(NULL));
    cout << "Welcome to the Bank Management System!" << endl;
}
Bank::~Bank() {
    auto* currentNode = users.getHead();
    while (currentNode != nullptr) {
        delete currentNode->getData();
        currentNode = currentNode->getNext();
    }
    cout << "Bank system shut down. All data cleared." << endl;
}

void Bank::setupInitialData() {
    Admin* admin1 = new Admin("admin", "admin", "0000000000", 30, "admin", "123");
    users.add(admin1);