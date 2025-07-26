#include "Admin.h"
#include "Customer.h"
#include "SavingsAccount.h"  
#include "CurrentAccount.h"
#include "LoanAccount.h"     
#include "bankingsystem.h"
#include <QString>
#include <QDebug>
#include <iostream>
#include <limits>

using namespace std;

Admin::Admin(const string& fname, const string& lname, const string& natId, 
            int userAge, const string& uname, const string& pass)
    : User(fname, lname, natId, userAge, uname, pass) {
    BankingSystem::getInstance().getAllAdmins().add(this);
}

Admin::~Admin() {}


bool Admin::addCustomer(const string& fname, const string& lname, const string& natId,
                       int age, const string& uname, const string& pass) {
    
    auto& bankSystem = BankingSystem::getInstance();
    QString username = QString::fromStdString(uname);
    
    if (bankSystem.findCustomerByUsername(username) != nullptr) {
        qDebug() << "Error: Username already exists:" << username;
        return false;
    }
    
    bool success = bankSystem.registerCustomer(
        QString::fromStdString(fname),
        QString::fromStdString(lname),
        QString::fromStdString(natId),
        age,
        username,
        QString::fromStdString(pass)
    );
    
    if (success) {
        qDebug() << "Customer added successfully:" << username;
    }
    
    return success;
}

bool Admin::removeCustomer(const string& username) {
    auto& bankSystem = BankingSystem::getInstance();
    Customer* customerToRemove = bankSystem.findCustomerByUsername(QString::fromStdString(username));
    if (!customerToRemove) {
        qDebug() << "Error: Customer not found:" << QString::fromStdString(username);
        return false;
    }
    
    auto* currentNode = customerToRemove->getAccounts().getHead();
    while (currentNode != nullptr) {
        Account* account = currentNode->getData();
        bankSystem.getAllAccounts().remove([&](Account* acc) {
            return acc->getCardNumber() == account->getCardNumber();
        });
        currentNode = currentNode->getNext();
    }
    
    bool removed = bankSystem.getAllCustomers().remove([&](Customer* customer) {
        return customer->getUsername() == username;
    });
    
    if (removed) {
        delete customerToRemove;
        cout << "Customer '" << username << "' removed successfully." << endl;
        return true;
    }
    
    return false;
}

Customer* Admin::findCustomer(const string& username) {
    return BankingSystem::getInstance().findCustomerByUsername(QString::fromStdString(username));
}

void Admin::viewAllCustomers() const {
    qDebug() << "\n=== All Customers ===";
    auto& customers = BankingSystem::getInstance().getAllCustomers();
    if (customers.getCount() == 0) {
        qDebug() << "No customers found.";
        return;
    }
    
    auto* currentNode = customers.getHead();
    int customerNum = 1;
    while (currentNode != nullptr) {
        cout << "\n--- Customer " << customerNum++ << " ---" << endl;
        currentNode->getData()->displayInfo();
        currentNode = currentNode->getNext();
    }
}


bool Admin::addAdmin(const string& fname, const string& lname, const string& natId,
                    int age, const string& uname, const string& pass) {
    
    auto& admins = BankingSystem::getInstance().getAllAdmins();
    Admin* existingAdmin = admins.find([&](Admin* admin) {
        return admin->getUsername() == uname;
    });
    
    if (existingAdmin) {
        cout << "Error: Admin username '" << uname << "' already exists." << endl;
        return false;
    }
    
    Admin* newAdmin = new Admin(fname, lname, natId, age, uname, pass);
    admins.add(newAdmin);
    cout << "Admin '" << uname << "' added successfully." << endl;
    return true;
}

void Admin::viewAllAdmins() const {
    cout << "\n=== All Admins ===" << endl;
    auto& admins = BankingSystem::getInstance().getAllAdmins();
    if (admins.getCount() == 0) {
        cout << "No admins found." << endl;
        return;
    }
    
    auto* currentNode = admins.getHead();
    int adminNum = 1;
    while (currentNode != nullptr) {
        cout << "\n--- Admin " << adminNum++ << " ---" << endl;
        currentNode->getData()->displayInfo();
        currentNode = currentNode->getNext();
    }
}


bool Admin::createAccount(const string& customerUsername, const string& accountType,
                         const string& cardNum, const string& accNum, const string& iban,
                         const string& primaryPass, const string& staticSecondPass) {
    qDebug() << "Creating account for customer:" << QString::fromStdString(customerUsername)
             << "Type:" << QString::fromStdString(accountType);
             
    auto& bankSystem = BankingSystem::getInstance();
    Customer* customer = bankSystem.findCustomerByUsername(QString::fromStdString(customerUsername));
    if (!customer) {
        qDebug() << "Error: Customer not found:" << QString::fromStdString(customerUsername);
        return false;
    }
    
    if (customer->getAccountCount() >= 5) {
        cout << "Error: Customer already has maximum number of accounts (5)." << endl;
        return false;
    }
    
    if (bankSystem.findAccountByCardNumber(QString::fromStdString(cardNum))) {
        qDebug() << "Error: Card number already exists:" << QString::fromStdString(cardNum);
        return false;
    }
    
    Account* newAccount = nullptr;
    
    try {
        if (accountType == "deposit") {
            qDebug() << "Creating deposit account...";
            newAccount = new DepositAccount(
                cardNum,
                accNum,
                iban,
                primaryPass,
                staticSecondPass,
                0.05  // Default interest rate 5%
            );
        } else if (accountType == "current") {
            qDebug() << "Creating current account...";
            newAccount = new CurrentAccount(
                cardNum,
                accNum,
                iban,
                primaryPass,
                staticSecondPass,
                0  // Initial overdraft limit
            );
        } else if (accountType == "loan") {
            qDebug() << "Creating loan account...";
            newAccount = new QarzAccount(  // Using QarzAccount instead of LoanAccount
                cardNum,
                accNum,
                iban,
                primaryPass,
                staticSecondPass
            );
        } else {
            qDebug() << "Error: Invalid account type:" << QString::fromStdString(accountType);
            cout << "Error: Invalid account type. Use 'deposit', 'current', or 'loan'." << endl;
            return false;
        }
        
        if (!newAccount) {
            qDebug() << "Failed to create account object";
            return false;
        }

        qDebug() << "Account object created successfully";
        customer->addAccount(newAccount);
        bankSystem.getAllAccounts().add(newAccount);
        qDebug() << "Account created successfully for customer:" << QString::fromStdString(customerUsername);
        return true;
        
    } catch (const std::exception& e) {
        qDebug() << "Exception during account creation:" << e.what();
        delete newAccount;  // Clean up if partially created
        return false;
    } catch (...) {
        qDebug() << "Unknown error during account creation";
        delete newAccount;  // Clean up if partially created
        return false;
    }
}

void Admin::viewAllAccounts() const {
    cout << "\n=== All Accounts ===" << endl;
    auto& accounts = BankingSystem::getInstance().getAllAccounts();
    if (accounts.getCount() == 0) {
        cout << "No accounts found." << endl;
        return;
    }
    
    auto* currentNode = accounts.getHead();
    int accountNum = 1;
    while (currentNode != nullptr) {
        cout << "\n--- Account " << accountNum++ << " ---" << endl;
        currentNode->getData()->displayAccountInfo();
        currentNode->getData()->displayAccountTypeDifference();
        currentNode = currentNode->getNext();
    }
}

void Admin::viewSpecificAccount(const string& cardNumber) const {
    Account* account = BankingSystem::getInstance().findAccountByCardNumber(QString::fromStdString(cardNumber));
    if (account) {
        cout << "\n=== Account Details ===" << endl;
        account->displayAccountInfo();
        account->displayAccountTypeDifference();
    } else {
        cout << "Account with card number '" << cardNumber << "' not found." << endl;
    }
}


bool Admin::editUserInfo(const string& username, const string& newFirstName,
                        const string& newLastName, int newAge) {
    
    Customer* customer = BankingSystem::getInstance().findCustomerByUsername(QString::fromStdString(username));
    if (customer) {
        customer->changeInfo(newFirstName, newLastName, newAge);
        cout << "Customer information updated successfully." << endl;
        return true;
    }
    
    Admin* admin = BankingSystem::getInstance().getAllAdmins().find([&](Admin* adm) {
        return adm->getUsername() == username;
    });
    
    if (admin) {
        admin->changeInfo(newFirstName, newLastName, newAge);
        cout << "Admin information updated successfully." << endl;
        return true;
    }
    
    cout << "User '" << username << "' not found." << endl;
    return false;
}

void Admin::viewUsersByType() const {
    cout << "\n=== Users by Type ===" << endl;
    auto& customers = BankingSystem::getInstance().getAllCustomers();
    auto& admins = BankingSystem::getInstance().getAllAdmins();
    cout << "\n--- Customers (" << customers.getCount() << ") ---" << endl;
    viewAllCustomers();
    
    cout << "\n--- Admins (" << admins.getCount() << ") ---" << endl;
    viewAllAdmins();
}


// All list management functions have been moved to BankSystem class


bool Admin::login(const string& uname, const string& pass) {
    if (username == uname && checkPassword(pass)) {
        cout << "Admin login successful. Welcome, " << getFullName() << "!" << endl;
        return true;
    }
    return false;
}

void Admin::showMainMenu() {
    while (true) {
        cout << "\n=== Admin Menu ===" << endl;
        cout << "1. View All Customers" << endl;
        cout << "2. View All Accounts" << endl;
        cout << "3. Add Customer" << endl;
        cout << "4. Remove Customer" << endl;
        cout << "5. Create Account" << endl;
        cout << "6. View Specific Account" << endl;
        cout << "7. View All Admins" << endl;
        cout << "8. Edit User Information" << endl;
        cout << "9. Logout" << endl;
        cout << "Choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear(); // clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        string fname, lname, natId, uname, pass;
        int age;

        switch (choice) {
            case 1:
                viewAllCustomers();
                break;
            case 2:
                viewAllAccounts();
                break;
            case 3:
                cout << "Enter customer details:" << endl;
                cout << "First Name: "; cin >> fname;
                cout << "Last Name: "; cin >> lname;
                cout << "National ID: "; cin >> natId;
                cout << "Age: "; cin >> age;
                cout << "Username: "; cin >> uname;
                cout << "Password: "; cin >> pass;
                addCustomer(fname, lname, natId, age, uname, pass);
                break;
            case 4:
                cout << "Enter username to remove: ";
                cin >> uname;
                removeCustomer(uname);
                break;
            case 5:
                {
                    string customerUsername, accountType, cardNum, accNum, iban, primaryPass, staticSecondPass;
                    cout << "Enter customer username: "; cin >> customerUsername;
                    cout << "Enter account type (deposit/current/loan): "; cin >> accountType;
                    cout << "Enter card number: "; cin >> cardNum;
                    cout << "Enter account number: "; cin >> accNum;
                    cout << "Enter IBAN: "; cin >> iban;
                    cout << "Enter primary password: "; cin >> primaryPass;
                    cout << "Enter static second password: "; cin >> staticSecondPass;
                    createAccount(customerUsername, accountType, cardNum, accNum, iban, primaryPass, staticSecondPass);
                }
                break;
            case 6:
                {
                    string cardNumber;
                    cout << "Enter card number: ";
                    cin >> cardNumber;
                    viewSpecificAccount(cardNumber);
                }
                break;
            case 7:
                viewAllAdmins();
                break;
            case 8:
                {
                    string username, newFirstName, newLastName;
                    int newAge;
                    cout << "Enter username to edit: "; cin >> username;
                    cout << "Enter new first name: "; cin >> newFirstName;
                    cout << "Enter new last name: "; cin >> newLastName;
                    cout << "Enter new age: "; cin >> newAge;
                    editUserInfo(username, newFirstName, newLastName, newAge);
                }
                break;
            case 9:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void Admin::displayInfo() const {
    User::displayInfo();
    cout << "User Type: Administrator" << endl;
    cout << "Access Level: Full System Access" << endl;
}


void Admin::initializeDefaultData() {
    
    cout << "Admin class initialization complete." << endl;
}
