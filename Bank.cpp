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

        Customer* customer2 = new Customer("sara", "saraei", "2222222222", 35, "sara", "123");
    Account* account2 = new CurrentAccount("2222", "6219", "IR2222", "2222", "2222");
    account2->deposit(10000000);
    customer2->addAccount(account2);
    users.add(customer2);

    cout << "Initial data has been set up." << endl;
}

void Bank::run() {
    setupInitialData();
    int choice;
    do {
        if (currentUser == nullptr) {
            showMainMenu();
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = -1; 
            }
            if (choice == 1) {
                handleLogin();
            }
        } else {
            if (Admin* admin = dynamic_cast<Admin*>(currentUser)) {
                showAdminMenu(admin);
            } else if (Customer* customer = dynamic_cast<Customer*>(currentUser)) {
                showCustomerMenu(customer);
            }
        }
    } while (choice != 2);
    cout << "Exiting the program. Goodbye!" << endl;
}

void Bank::showMainMenu() {
    cout << "\n--- Main Menu ---" << endl;
    cout << "1. Login" << endl;
    cout << "2. Exit" << endl;
    cout << "Enter your choice: ";
}

void Bank::handleLogin() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    User* user = findUserByUsername(username);
    if (user && user->checkPassword(password)) {
        currentUser = user;
        cout << "Login successful! Welcome " << currentUser->getFullName() << endl;
    } else {
        cout << "Invalid username or password." << endl;
    }
}

void Bank::handleLogout() {
    cout << "Logging out " << currentUser->getFullName() << "..." << endl;
    currentUser = nullptr;
}