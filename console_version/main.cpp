#include "BankSystem.h"
#include "Admin.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    // Initialize bank system
    BankSystem& bank = BankSystem::getInstance();
    
    // Create initial admin if none exists
    if (bank.getAllAdmins().getCount() == 0) {
        Admin* admin = new Admin("Admin", "User", "1234567890", 30, "admin", "admin123");
        cout << "Initial admin created. Username: admin, Password: admin123" << endl;
    }
    
    // Main menu
    string username, password;
    bool running = true;
    while (running) {
        cout << "\n=== Banking System ===" << endl;
        cout << "1. Login" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        
        int choice;
        if (!(cin >> choice)) {
            cin.clear(); // clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        
        // Clear any remaining characters in the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (choice == 0) {
            running = false;
        } else if (choice == 1) {
            cout << "Username: ";
            if (!(cin >> username)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input." << endl;
                continue;
            }
            
            cout << "Password: ";
            if (!(cin >> password)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input." << endl;
                continue;
            }
            
            // Clear input buffer after successful read
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            // Try admin login first
            Admin* foundAdmin = bank.getAllAdmins().find([&](Admin* a) {
                return a->getUsername() == username;
            });
            
            if (foundAdmin && foundAdmin->login(username, password)) {
                foundAdmin->showMainMenu();
                // Clear any leftover input after returning from menu
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                // Try customer login
                Customer* foundCustomer = bank.findCustomerByUsername(username);
                if (foundCustomer && foundCustomer->login(username, password)) {
                    foundCustomer->showMainMenu();
                    // Clear any leftover input after returning from menu
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    cout << "Invalid username or password." << endl;
                }
            }
        }
    }
    
    return 0;
}
