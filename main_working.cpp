#include <iostream>
#include <string>
#include "bankingsystem_console.h"
#include "Customer.h"
#include "Admin.h"

using namespace std;

void showMainMenu() {
    cout << "\n=== Banking Management System ===" << endl;
    cout << "1. Customer Login" << endl;
    cout << "2. Admin Login" << endl;
    cout << "3. Register New Customer" << endl;
    cout << "4. Exit" << endl;
    cout << "Select an option: ";
}

void customerMenu(Customer* customer) {
    int choice;
    do {
        cout << "\n=== Customer Menu ===" << endl;
        cout << "Welcome, " << customer->getFirstName() << " " << customer->getLastName() << "!" << endl;
        cout << "1. View All Accounts" << endl;
        cout << "2. View Specific Account" << endl;
        cout << "3. Card to Card Transfer" << endl;
        cout << "4. Change Account Password" << endl;
        cout << "5. Generate Dynamic Password" << endl;
        cout << "6. Update Personal Information" << endl;
        cout << "7. Logout" << endl;
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                customer->viewAllAccounts();
                break;
            case 2: {
                string cardNumber;
                cout << "Enter card number: ";
                cin >> cardNumber;
                customer->viewSpecificAccount(cardNumber);
                break;
            }
            case 3: {
                string fromCard, toCard, password;
                double amount;
                cout << "Enter source card number: ";
                cin >> fromCard;
                cout << "Enter destination card number: ";
                cin >> toCard;
                cout << "Enter amount: ";
                cin >> amount;
                cout << "Enter second password: ";
                cin >> password;
                
                if (customer->performCardToCardTransfer(fromCard, toCard, amount, password)) {
                    cout << "Transfer successful!" << endl;
                } else {
                    cout << "Transfer failed!" << endl;
                }
                break;
            }
            case 4: {
                string cardNumber, passwordType, oldPass, newPass;
                cout << "Enter card number: ";
                cin >> cardNumber;
                cout << "Enter password type (primary/second): ";
                cin >> passwordType;
                cout << "Enter old password: ";
                cin >> oldPass;
                cout << "Enter new password: ";
                cin >> newPass;
                
                if (customer->changeAccountPassword(cardNumber, passwordType, oldPass, newPass)) {
                    cout << "Password changed successfully!" << endl;
                } else {
                    cout << "Password change failed!" << endl;
                }
                break;
            }
            case 5: {
                string cardNumber;
                cout << "Enter card number: ";
                cin >> cardNumber;
                string dynamicPass = customer->generateDynamicPassword(cardNumber);
                if (!dynamicPass.empty()) {
                    cout << "Dynamic Password: " << dynamicPass << endl;
                } else {
                    cout << "Failed to generate dynamic password!" << endl;
                }
                break;
            }
            case 6: {
                string firstName, lastName;
                int age;
                cout << "Enter new first name: ";
                cin >> firstName;
                cout << "Enter new last name: ";
                cin >> lastName;
                cout << "Enter new age: ";
                cin >> age;
                customer->changeInfo(firstName, lastName, age);
                cout << "Information updated successfully!" << endl;
                break;
            }
            case 7:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid option!" << endl;
        }
    } while (choice != 7);
}

void adminMenu(Admin* admin) {
    int choice;
    do {
        cout << "\n=== Admin Menu ===" << endl;
        cout << "Welcome, " << admin->getFirstName() << " " << admin->getLastName() << "!" << endl;
        cout << "1. View All Customers" << endl;
        cout << "2. View Customer Details" << endl;
        cout << "3. Create Account for Customer" << endl;
        cout << "4. View All Accounts" << endl;
        cout << "5. Logout" << endl;
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                admin->viewAllCustomers();
                break;
            case 2: {
                string username;
                cout << "Enter customer username: ";
                cin >> username;
                Customer* customer = admin->findCustomer(username);
                if (customer) {
                    customer->displayInfo();
                } else {
                    cout << "Customer not found!" << endl;
                }
                break;
            }
            case 3: {
                string username, accountType, cardNum, accNum, iban, primaryPass, secondPass;
                cout << "Enter customer username: ";
                cin >> username;
                cout << "Enter account type (deposit/current/loan): ";
                cin >> accountType;
                cout << "Enter card number: ";
                cin >> cardNum;
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter IBAN: ";
                cin >> iban;
                cout << "Enter primary password: ";
                cin >> primaryPass;
                cout << "Enter second password: ";
                cin >> secondPass;
                
                if (admin->createAccount(username, accountType, cardNum, accNum, iban, primaryPass, secondPass)) {
                    cout << "Account created successfully!" << endl;
                } else {
                    cout << "Failed to create account!" << endl;
                }
                break;
            }
            case 4:
                admin->viewAllAccounts();
                break;
            case 5:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid option!" << endl;
        }
    } while (choice != 5);
}

int main() {
    BankingSystemConsole& system = BankingSystemConsole::getInstance();
    system.initializeSystem();
    
    cout << "Banking Management System Initialized!" << endl;
    cout << "Sample Data Created:" << endl;
    cout << "Customer: ali_ahmadi / pass123" << endl;
    cout << "Customer: sara_h / pass456" << endl;
    cout << "Admin: admin / admin123" << endl;
    
    int choice;
    do {
        showMainMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                
                Customer* customer = system.authenticateCustomer(username, password);
                if (customer) {
                    customerMenu(customer);
                } else {
                    cout << "Invalid credentials!" << endl;
                }
                break;
            }
            case 2: {
                string username, password;
                cout << "Enter admin username: ";
                cin >> username;
                cout << "Enter admin password: ";
                cin >> password;
                
                Admin* admin = system.authenticateAdmin(username, password);
                if (admin) {
                    adminMenu(admin);
                } else {
                    cout << "Invalid admin credentials!" << endl;
                }
                break;
            }
            case 3: {
                string firstName, lastName, nationalId, username, password;
                int age;
                cout << "Enter first name: ";
                cin >> firstName;
                cout << "Enter last name: ";
                cin >> lastName;
                cout << "Enter national ID: ";
                cin >> nationalId;
                cout << "Enter age: ";
                cin >> age;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                
                if (system.registerCustomer(firstName, lastName, nationalId, age, username, password)) {
                    cout << "Customer registered successfully!" << endl;
                } else {
                    cout << "Registration failed! Username might already exist." << endl;
                }
                break;
            }
            case 4:
                cout << "Thank you for using Banking Management System!" << endl;
                break;
            default:
                cout << "Invalid option!" << endl;
        }
    } while (choice != 4);
    
    return 0;
}
