#include "Admin.h"
#include "Customer.h"
#include "SavingsAccount.h"  // DepositAccount
#include "CurrentAccount.h"
#include "LoanAccount.h"     // QarzAccount
#include <iostream>

using namespace std;

// Static member definitions
LinkedList<Customer*> Admin::allCustomers;
LinkedList<Admin*> Admin::allAdmins;
LinkedList<Account*> Admin::allAccounts;

Admin::Admin(const string& fname, const string& lname, const string& natId, 
            int userAge, const string& uname, const string& pass)
    : User(fname, lname, natId, userAge, uname, pass) {
    addToAdminList(this);
}

Admin::~Admin() {}

// Customer management
bool Admin::addCustomer(const string& fname, const string& lname, const string& natId,
                       int age, const string& uname, const string& pass) {
    // Check if username already exists
    if (findCustomerByUsername(uname) != nullptr) {
        cout << "Error: Username '" << uname << "' already exists." << endl;
        return false;
    }
    
    Customer* newCustomer = new Customer(fname, lname, natId, age, uname, pass);
    addToCustomerList(newCustomer);
    cout << "Customer '" << uname << "' added successfully." << endl;
    return true;
}

bool Admin::removeCustomer(const string& username) {
    Customer* customerToRemove = findCustomerByUsername(username);
    if (!customerToRemove) {
        cout << "Error: Customer '" << username << "' not found." << endl;
        return false;
    }
    
    // Remove customer's accounts first
    auto* currentNode = customerToRemove->getAccounts().getHead();
    while (currentNode != nullptr) {
        Account* account = currentNode->getData();
        allAccounts.remove([&](Account* acc) {
            return acc->getCardNumber() == account->getCardNumber();
        });
        currentNode = currentNode->getNext();
    }
    
    // Remove customer
    bool removed = allCustomers.remove([&](Customer* customer) {
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
    return findCustomerByUsername(username);
}

void Admin::viewAllCustomers() const {
    cout << "\n=== All Customers ===" << endl;
    if (allCustomers.getCount() == 0) {
        cout << "No customers found." << endl;
        return;
    }
    
    auto* currentNode = allCustomers.getHead();
    int customerNum = 1;
    while (currentNode != nullptr) {
        cout << "\n--- Customer " << customerNum++ << " ---" << endl;
        currentNode->getData()->displayInfo();
        currentNode = currentNode->getNext();
    }
}

// Admin management
bool Admin::addAdmin(const string& fname, const string& lname, const string& natId,
                    int age, const string& uname, const string& pass) {
    // Check if username already exists among admins
    Admin* existingAdmin = allAdmins.find([&](Admin* admin) {
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
    if (allAdmins.getCount() == 0) {
        cout << "No admins found." << endl;
        return;
    }
    
    auto* currentNode = allAdmins.getHead();
    int adminNum = 1;
    while (currentNode != nullptr) {
        cout << "\n--- Admin " << adminNum++ << " ---" << endl;
        currentNode->getData()->displayInfo();
        currentNode = currentNode->getNext();
    }
}

// Account management
bool Admin::createAccount(const string& customerUsername, const string& accountType,
                         const string& cardNum, const string& accNum, const string& iban,
                         const string& primaryPass, const string& staticSecondPass) {
    Customer* customer = findCustomerByUsername(customerUsername);
    if (!customer) {
        cout << "Error: Customer '" << customerUsername << "' not found." << endl;
        return false;
    }
    
    if (customer->getAccountCount() >= 5) {
        cout << "Error: Customer already has maximum number of accounts (5)." << endl;
        return false;
    }
    
    // Check if card number already exists
    if (findAccountByCardNumber(cardNum)) {
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
        addToAccountList(newAccount);
        cout << "Account created successfully for customer '" << customerUsername << "'." << endl;
        return true;
    }
    
    return false;
}

void Admin::viewAllAccounts() const {
    cout << "\n=== All Accounts ===" << endl;
    if (allAccounts.getCount() == 0) {
        cout << "No accounts found." << endl;
        return;
    }
    
    auto* currentNode = allAccounts.getHead();
    int accountNum = 1;
    while (currentNode != nullptr) {
        cout << "\n--- Account " << accountNum++ << " ---" << endl;
        currentNode->getData()->displayAccountInfo();
        currentNode->getData()->displayAccountTypeDifference();
        currentNode = currentNode->getNext();
    }
}

void Admin::viewSpecificAccount(const string& cardNumber) const {
    Account* account = findAccountByCardNumber(cardNumber);
    if (account) {
        cout << "\n=== Account Details ===" << endl;
        account->displayAccountInfo();
        account->displayAccountTypeDifference();
    } else {
        cout << "Account with card number '" << cardNumber << "' not found." << endl;
    }
}

// User information management
bool Admin::editUserInfo(const string& username, const string& newFirstName,
                        const string& newLastName, int newAge) {
    // Check customers first
    Customer* customer = findCustomerByUsername(username);
    if (customer) {
        customer->changeInfo(newFirstName, newLastName, newAge);
        cout << "Customer information updated successfully." << endl;
        return true;
    }
    
    // Check admins
    Admin* admin = allAdmins.find([&](Admin* adm) {
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
    cout << "\n--- Customers (" << allCustomers.getCount() << ") ---" << endl;
    viewAllCustomers();
    
    cout << "\n--- Admins (" << allAdmins.getCount() << ") ---" << endl;
    viewAllAdmins();
}

// Static data management
void Admin::addToCustomerList(Customer* customer) {
    allCustomers.add(customer);
}

void Admin::addToAdminList(Admin* admin) {
    allAdmins.add(admin);
}

void Admin::addToAccountList(Account* account) {
    allAccounts.add(account);
}

Customer* Admin::findCustomerByUsername(const string& username) {
    return allCustomers.find([&](Customer* customer) {
        return customer->getUsername() == username;
    });
}

Account* Admin::findAccountByCardNumber(const string& cardNumber) {
    return allAccounts.find([&](Account* account) {
        return account->getCardNumber() == cardNumber;
    });
}

// Inherited virtual functions
bool Admin::login(const string& uname, const string& pass) {
    if (username == uname && checkPassword(pass)) {
        cout << "Admin login successful. Welcome, " << getFullName() << "!" << endl;
        return true;
    }
    return false;
}

void Admin::showMainMenu() {
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
    cout << "===================" << endl;
}

void Admin::displayInfo() const {
    User::displayInfo();
    cout << "User Type: Administrator" << endl;
    cout << "Access Level: Full System Access" << endl;
}

// Initialization
void Admin::initializeDefaultData() {
    // This will be called from main.cpp to set up sample data
    cout << "Admin class initialization complete." << endl;
}
