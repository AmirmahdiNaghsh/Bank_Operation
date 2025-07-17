// Banking Management System - Main Application Entry Point
// This is the console version - Qt GUI to be added in subsequent commits

#include "Account.h"
#include "SavingsAccount.h"  // DepositAccount
#include "CurrentAccount.h"
#include "LoanAccount.h"     // QarzAccount
#include "User.h"
#include "Customer.h"
#include "Admin.h"
#include "LinkedList.h"
#include <iostream>
#include <string>

using namespace std;

// Global data storage (in-memory only as required)
LinkedList<Customer*> allCustomers;
LinkedList<Admin*> allAdmins;
LinkedList<Account*> allAccounts;

// Function declarations
void initializeDefaultData();
void showMainMenu();
bool authenticateUser();
void customerMenu(Customer* customer);
void adminMenu(Admin* admin);
Customer* findCustomerByUsername(const string& username);
Admin* findAdminByUsername(const string& username);
Account* findAccountByCardNumber(const string& cardNumber);

int main() {
    cout << "=== Banking Management System ===" << endl;
    cout << "Initializing system..." << endl;
    
    // Initialize with sample data
    initializeDefaultData();
    
    cout << "System ready!" << endl;
    cout << "==================================" << endl;
    
    // Main application loop
    while (true) {
        showMainMenu();
        
        int choice;
        cin >> choice;
        cin.ignore(); // Clear newline
        
        switch (choice) {
            case 1: {
                // Login
                if (authenticateUser()) {
                    cout << "Login successful!" << endl;
                } else {
                    cout << "Login failed!" << endl;
                }
                break;
            }
            case 2: {
                // Register new customer
                string fname, lname, natId, username, password;
                int age;
                
                cout << "Enter first name: ";
                getline(cin, fname);
                cout << "Enter last name: ";
                getline(cin, lname);
                cout << "Enter national ID: ";
                getline(cin, natId);
                cout << "Enter age: ";
                cin >> age;
                cin.ignore();
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                
                Customer* newCustomer = new Customer(fname, lname, natId, age, username, password);
                allCustomers.add(newCustomer);
                
                cout << "Customer registered successfully!" << endl;
                break;
            }
            case 3: {
                cout << "Thank you for using Banking Management System!" << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        }
    }
    
    return 0;
}

void initializeDefaultData() {
    // Create sample admin
    Admin* sampleAdmin = new Admin("Admin", "User", "1234567890", 30, "admin", "admin123");
    allAdmins.add(sampleAdmin);
    
    // Create sample customers
    Customer* customer1 = new Customer("Ali", "Ahmadi", "0123456789", 25, "ali_ahmadi", "pass123");
    Customer* customer2 = new Customer("Sara", "Hosseini", "0987654321", 28, "sara_h", "pass456");
    
    allCustomers.add(customer1);
    allCustomers.add(customer2);
    
    // Create sample accounts for customer1
    DepositAccount* depositAcc = new DepositAccount("1234567812345678", "ACC001", "IR123456789", "1234", "5678", 0.15);
    depositAcc->deposit(1000000); // 1M Toman initial balance
    
    CurrentAccount* currentAcc = new CurrentAccount("1234567887654321", "ACC002", "IR987654321", "4321", "8765", 500000);
    currentAcc->deposit(500000); // 500K Toman initial balance
    
    QarzAccount* loanAcc = new QarzAccount("1234567855556666", "ACC003", "IR555666777", "6666", "7777");
    loanAcc->requestLoan(2000000, 24); // 2M Toman loan for 24 months
    
    customer1->addAccount(depositAcc);
    customer1->addAccount(currentAcc);
    customer1->addAccount(loanAcc);
    
    allAccounts.add(depositAcc);
    allAccounts.add(currentAcc);
    allAccounts.add(loanAcc);
    
    // Create sample account for customer2
    DepositAccount* depositAcc2 = new DepositAccount("9876543212345678", "ACC004", "IR999888777", "9999", "8888", 0.12);
    depositAcc2->deposit(750000); // 750K Toman initial balance
    
    customer2->addAccount(depositAcc2);
    allAccounts.add(depositAcc2);
    
    cout << "Sample data created:" << endl;
    cout << "- Admin: username='admin', password='admin123'" << endl;
    cout << "- Customer 1: username='ali_ahmadi', password='pass123' (3 accounts)" << endl;
    cout << "- Customer 2: username='sara_h', password='pass456' (1 account)" << endl;
}

void showMainMenu() {
    cout << "\n=== Main Menu ===" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register (New Customer)" << endl;
    cout << "3. Exit" << endl;
    cout << "Choice: ";
}

bool authenticateUser() {
    string username, password;
    
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    
    // Check if admin
    Admin* admin = findAdminByUsername(username);
    if (admin && admin->login(username, password)) {
        adminMenu(admin);
        return true;
    }
    
    // Check if customer
    Customer* customer = findCustomerByUsername(username);
    if (customer && customer->login(username, password)) {
        customerMenu(customer);
        return true;
    }
    
    return false;
}

void customerMenu(Customer* customer) {
    while (true) {
        customer->showMainMenu();
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                // View all accounts
                customer->viewAllAccounts();
                break;
            }
            case 2: {
                // View specific account
                string cardNumber;
                cout << "Enter card number: ";
                getline(cin, cardNumber);
                customer->viewSpecificAccount(cardNumber);
                break;
            }
            case 3: {
                // Change account password
                string cardNumber, passwordType, oldPass, newPass;
                cout << "Enter card number: ";
                getline(cin, cardNumber);
                cout << "Password type (primary/second): ";
                getline(cin, passwordType);
                cout << "Enter old password: ";
                getline(cin, oldPass);
                cout << "Enter new password: ";
                getline(cin, newPass);
                
                customer->changeAccountPassword(cardNumber, passwordType, oldPass, newPass);
                break;
            }
            case 4: {
                // Card to card transfer
                string fromCard, toCard, secondPassword;
                double amount;
                
                cout << "Enter source card number: ";
                getline(cin, fromCard);
                cout << "Enter destination card number: ";
                getline(cin, toCard);
                cout << "Enter transfer amount: ";
                cin >> amount;
                cin.ignore();
                cout << "Enter second password: ";
                getline(cin, secondPassword);
                
                customer->performCardToCardTransfer(fromCard, toCard, amount, secondPassword);
                break;
            }
            case 5: {
                // Generate dynamic password
                string cardNumber;
                cout << "Enter card number: ";
                getline(cin, cardNumber);
                customer->generateDynamicPassword(cardNumber);
                break;
            }
            case 6: {
                // Change personal information
                string newFirstName, newLastName;
                int newAge;
                cout << "Enter new first name: ";
                getline(cin, newFirstName);
                cout << "Enter new last name: ";
                getline(cin, newLastName);
                cout << "Enter new age: ";
                cin >> newAge;
                cin.ignore();
                
                customer->changeInfo(newFirstName, newLastName, newAge);
                break;
            }
            case 7: {
                // Logout
                cout << "Logged out successfully." << endl;
                return;
            }
            default: {
                cout << "Invalid choice!" << endl;
                break;
            }
        }
    }
}

void adminMenu(Admin* admin) {
    while (true) {
        admin->showMainMenu();
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                // View all customers
                admin->viewAllCustomers();
                break;
            }
            case 2: {
                // View all accounts
                admin->viewAllAccounts();
                break;
            }
            case 3: {
                // Add customer
                string fname, lname, natId, username, password;
                int age;
                
                cout << "Enter first name: ";
                getline(cin, fname);
                cout << "Enter last name: ";
                getline(cin, lname);
                cout << "Enter national ID: ";
                getline(cin, natId);
                cout << "Enter age: ";
                cin >> age;
                cin.ignore();
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                
                admin->addCustomer(fname, lname, natId, age, username, password);
                break;
            }
            case 4: {
                // Remove customer
                string username;
                cout << "Enter customer username to remove: ";
                getline(cin, username);
                admin->removeCustomer(username);
                break;
            }
            case 5: {
                // Create account
                string customerUsername, accountType, cardNum, accNum, iban, primaryPass, staticSecondPass;
                
                cout << "Enter customer username: ";
                getline(cin, customerUsername);
                cout << "Account type (deposit/current/loan): ";
                getline(cin, accountType);
                cout << "Enter card number: ";
                getline(cin, cardNum);
                cout << "Enter account number: ";
                getline(cin, accNum);
                cout << "Enter IBAN: ";
                getline(cin, iban);
                cout << "Enter primary password: ";
                getline(cin, primaryPass);
                cout << "Enter static second password: ";
                getline(cin, staticSecondPass);
                
                admin->createAccount(customerUsername, accountType, cardNum, accNum, iban, primaryPass, staticSecondPass);
                break;
            }
            case 6: {
                // View specific account
                string cardNumber;
                cout << "Enter card number: ";
                getline(cin, cardNumber);
                admin->viewSpecificAccount(cardNumber);
                break;
            }
            case 7: {
                // View other admins
                admin->viewAllAdmins();
                break;
            }
            case 8: {
                // Edit user information
                string username, newFirstName, newLastName;
                int newAge;
                
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter new first name: ";
                getline(cin, newFirstName);
                cout << "Enter new last name: ";
                getline(cin, newLastName);
                cout << "Enter new age: ";
                cin >> newAge;
                cin.ignore();
                
                admin->editUserInfo(username, newFirstName, newLastName, newAge);
                break;
            }
            case 9: {
                // Logout
                cout << "Admin logged out successfully." << endl;
                return;
            }
            default: {
                cout << "Invalid choice!" << endl;
                break;
            }
        }
    }
}

Customer* findCustomerByUsername(const string& username) {
    return allCustomers.find([&](Customer* customer) {
        return customer->getUsername() == username;
    });
}

Admin* findAdminByUsername(const string& username) {
    return allAdmins.find([&](Admin* admin) {
        return admin->getUsername() == username;
    });
}

Account* findAccountByCardNumber(const string& cardNumber) {
    return allAccounts.find([&](Account* account) {
        return account->getCardNumber() == cardNumber;
    });
}
