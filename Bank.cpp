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

       Customer* customer1 = new Customer("ali", "alavi", "1111111111", 25, "ali", "123");
    Account* account1 = new SavingsAccount("1111", "6037", "IR1111", "1111", "1111", 1.5);
    account1->deposit(5000000);
    customer1->addAccount(account1);
    users.add(customer1);