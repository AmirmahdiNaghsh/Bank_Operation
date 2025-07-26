#include "Admin.h"
#include "Customer.h"
#include "SavingsAccount.h"  
#include "CurrentAccount.h"
#include "LoanAccount.h"     
#include "BankSystem.h"
#include <iostream>
#include <limits>

using namespace std;

Admin::Admin(const string& fname, const string& lname, const string& natId, 
            int userAge, const string& uname, const string& pass)
    : User(fname, lname, natId, userAge, uname, pass) {
    BankSystem::getInstance().registerAdmin(this);
}

Admin::~Admin() {}


bool Admin::addCustomer(const string& fname, const string& lname, const string& natId,
                       int age, const string& uname, const string& pass) {
    
    if (BankSystem::getInstance().findCustomerByUsername(uname) != nullptr) {
        cout << "Error: Username '" << uname << "' already exists." << endl;
        return false;
    }
    
    Customer* newCustomer = new Customer(fname, lname, natId, age, uname, pass);
    BankSystem::getInstance().registerCustomer(newCustomer);
    cout << "Customer '" << uname << "' added successfully." << endl;
    return true;
}

bool Admin::removeCustomer(const string& username) {
    Customer* customerToRemove = BankSystem::getInstance().findCustomerByUsername(username);
    if (!customerToRemove) {
        cout << "Error: Customer '" << username << "' not found." << endl;
        return false;
    }
    
    auto* currentNode = customerToRemove->getAccounts().getHead();
    while (currentNode != nullptr) {
        Account* account = currentNode->getData();
        BankSystem::getInstance().getAllAccounts().remove([&](Account* acc) {
            return acc->getCardNumber() == account->getCardNumber();
        });
        currentNode = currentNode->getNext();
    }
    
    bool removed = BankSystem::getInstance().getAllCustomers().remove([&](Customer* customer) {
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
    return BankSystem::getInstance().findCustomerByUsername(username);
}

void Admin::viewAllCustomers() const {
    cout << "\n=== All Customers ===" << endl;
    auto& customers = BankSystem::getInstance().getAllCustomers();
    if (customers.getCount() == 0) {
        cout << "No customers found." << endl;
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
    
    auto& admins = BankSystem::getInstance().getAllAdmins();
    Admin* existingAdmin = admins.find([&](Admin* admin) {
        return admin->getUsername() == uname;
    });
    
    if (existingAdmin) {
        cout << "Error: Admin username '" << uname << "' already exists." << endl;
        return false;
    }
    
    Admin* newAdmin = new Admin(fname, lname, natId, age, uname, pass);
    cout << "Admin '" << uname << "' added successfully." << endl;
    return true;
}

void Admin::viewAllAdmins() const {
    cout << "\n=== All Admins ===" << endl;
    auto& admins = BankSystem::getInstance().getAllAdmins();
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
    Customer* customer = BankSystem::getInstance().findCustomerByUsername(customerUsername);
    if (!customer) {
        cout << "Error: Customer '" << customerUsername << "' not found." << endl;
        return false;
    }
    
    if (customer->getAccountCount() >= 5) {
        cout << "Error: Customer already has maximum number of accounts (5)." << endl;
        return false;
    }
    
    if (BankSystem::getInstance().findAccountByCardNumber(cardNum)) {
        cout << "Error: Card number '" << cardNum << "' already exists." << endl;
        return false;
    }
    
    Account* newAccount = nullptr;
    
    if (accountType == "deposit") {
        newAccount = new DepositAccount(cardNum, accNum, iban, primaryPass, staticSecondPass);
    } else if (accountType == "current") {
        newAccount = new CurrentAccount(cardNum, accNum, iban, primaryPass, staticSecondPass);
    } else if (accountType == "loan") {
        newAccount = new QarzAccount(cardNum, accNum, iban, primaryPass, staticSecondPass);
    } else {
        cout << "Error: Invalid account type. Use 'deposit', 'current', or 'loan'." << endl;
        return false;
    }
    
    if (newAccount) {
        customer->addAccount(newAccount);
        BankSystem::getInstance().registerAccount(newAccount);
        cout << "Account created successfully for customer '" << customerUsername << "'." << endl;
        return true;
    }
    
    return false;
}

void Admin::viewAllAccounts() const {
    cout << "\n=== All Accounts ===" << endl;
    auto& accounts = BankSystem::getInstance().getAllAccounts();
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
    Account* account = BankSystem::getInstance().findAccountByCardNumber(cardNumber);
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
    
    Customer* customer = BankSystem::getInstance().findCustomerByUsername(username);
    if (customer) {
        customer->changeInfo(newFirstName, newLastName, newAge);
        cout << "Customer information updated successfully." << endl;
        return true;
    }
    
    Admin* admin = BankSystem::getInstance().getAllAdmins().find([&](Admin* adm) {
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
    auto& customers = BankSystem::getInstance().getAllCustomers();
    auto& admins = BankSystem::getInstance().getAllAdmins();
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
