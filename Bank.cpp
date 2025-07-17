#include "Bank.h"
#include "Admin.h"
#include "Customer.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "LoanAccount.h"  
#include <iostream>
#include <limits>
#include <ctime>          
#include <string>         
#include <cstdlib>        

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
    int choice = 0;
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
    } while (choice != 2 || currentUser != nullptr); 
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

User* Bank::findUserByUsername(const string& username) {
    return users.find([&](User* u){ return u->getUsername() == username; });
}

Account* Bank::findAccountByCardNumber(const string& cardNumber) {
    auto* userNode = users.getHead();
    while (userNode != nullptr) {
        if (Customer* customer = dynamic_cast<Customer*>(userNode->getData())) {
            Account* foundAccount = customer->findAccountByCardNumber(cardNumber);
            if (foundAccount) {
                return foundAccount;
            }
        }
        userNode = userNode->getNext();
    }
    return nullptr; 
}

void Bank::showAdminMenu(Admin* admin) {
    cout << "\n--- Admin Menu (" << admin->getUsername() << ") ---" << endl;
    cout << "1. View All Users" << endl;
    cout << "9. Logout" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            admin->viewAllUsers(users);
            break;
        case 9:
            handleLogout();
            break;
        default:
            cout << "Invalid choice." << endl;
    }
}

void Bank::showCustomerMenu(Customer* customer) {
    cout << "\n--- Customer Menu (" << customer->getUsername() << ") ---" << endl;
    cout << "1. Card to Card Transfer" << endl;
    cout << "2. View Accounts" << endl;
    cout << "3. Change Account Password" << endl;
    cout << "9. Logout" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
     if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choice = -1; 
    }

    switch (choice) {
        case 1:
            performCardToCard(customer); 
            break;
        case 2:
            viewCustomerAccounts(customer);
            break;
        case 3:
            changeAccountPassword(customer);
            break;
        case 9:
            handleLogout();
            break;
        default:
            cout << "Invalid choice." << endl;
    }
}

void Bank::performCardToCard(Customer* customer) {
    string sourceCard, destCard, pin1, pin2;
    double amount;

    cout << "Enter your card number (source): ";
    cin >> sourceCard;
    cout << "Enter destination card number: ";
    cin >> destCard;
    cout << "Enter amount to transfer: ";
    cin >> amount;

    Account* sourceAccount = customer->findAccountByCardNumber(sourceCard);
    if (!sourceAccount) {
        cout << "Error: Source card not found or does not belong to you." << endl;
        return;
    }

    Account* destAccount = this->findAccountByCardNumber(destCard);
    if (!destAccount) {
        cout << "Error: Destination card not found." << endl;
        return;
    }

    if (sourceAccount->isExpired()) {
        cout << "Error: Your card has expired." << endl;
        return;
    }

    if (amount <= 0) {
        cout << "Error: Invalid transfer amount." << endl;
        return;
    }

    if (amount > 3000000) {
        cout << "Error: Transaction limit is 3,000,000 Toman." << endl;
        return;
    }
    
    if (sourceAccount->getBalance() < amount) {
        cout << "Error: Insufficient balance." << endl;
        return;
    }
    
    cout << "Enter your PIN1: ";
    cin >> pin1;
    if (!sourceAccount->checkPin1(pin1)) {
        cout << "Error: Incorrect PIN1." << endl;
        return;
    }

    if (amount > 100000) {
        string dynamicPin = to_string(100000 + rand() % 900000);
        sourceAccount->setDynamicPin(dynamicPin);
        cout << "A one-time password has been generated: " << dynamicPin << endl;
        cout << "Please enter the dynamic password: ";
        cin >> pin2;
        if (!sourceAccount->checkPin2Dynamic(pin2)) {
            cout << "Error: Incorrect dynamic password." << endl;
            sourceAccount->setDynamicPin("");
            return;
        }
    } else {
        cout << "Enter your static PIN2: ";
        cin >> pin2;
        if (!sourceAccount->checkPin2Static(pin2)) {
            cout << "Error: Incorrect static PIN2." << endl;
            return;
        }
    }
    
    double fee = amount * 0.0001;
    double finalAmount = amount - fee;

    if (sourceAccount->withdraw(amount)) {
        destAccount->deposit(finalAmount);
        sourceAccount->setDynamicPin("");
        cout << "\nTransfer successful!" << endl;
        cout << "Amount transferred: " << finalAmount << " Toman" << endl;
        cout << "Fee: " << fee << " Toman" << endl;
        cout << "Your new balance: " << sourceAccount->getBalance() << " Toman" << endl;
    } else {
        cout << "An unexpected error occurred during withdrawal." << endl;
    }
}

void Bank::viewCustomerAccounts(Customer* customer) {
    cout << "\n--- Your Bank Accounts ---" << endl;
    customer->getAccounts().display();
}

void Bank::changeAccountPassword(Customer* customer) {
    string cardNum, oldPin, newPin1, newPin2;
    cout << "Enter card number to change its passwords: ";
    cin >> cardNum;
    Account* acc = customer->findAccountByCardNumber(cardNum);
    if (!acc) {
        cout << "Account not found." << endl;
        return;
    }
    cout << "Enter current PIN1: ";
    cin >> oldPin;
    if (acc->checkPin1(oldPin)) {
        cout << "Enter new PIN1: ";
        cin >> newPin1;
        cout << "Enter new static PIN2: ";
        cin >> newPin2;
        acc->changePins(newPin1, newPin2);
        cout << "Passwords changed successfully." << endl;
    } else {
        cout << "Incorrect PIN." << endl;
    }
}