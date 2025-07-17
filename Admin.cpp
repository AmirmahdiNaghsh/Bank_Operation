#include "Admin.h"
#include "Customer.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "LoanAccount.h"
#include <iostream>

using namespace std;
Admin::Admin(const string& fname, const string& lname, const string& natId, int userAge, const string& uname, const string& pass)
    : User(fname, lname, natId, userAge, uname, pass) {}
void Admin::viewAllUsers(const LinkedList<User*>& users) const {
    cout << "--- System Users List ---" << endl;
    users.display();
}
void Admin::addCustomer(LinkedList<User*>& users, const string& fname, const string& lname, const string& natId, int age, const string& uname, const string& pass) {
    
    if (users.find([&](User* u){ return u->getUsername() == uname; })) {
        cout << "Error: Username '" << uname << "' already exists." << endl;
        return;
    }
    Customer* newCustomer = new Customer(fname, lname, natId, age, uname, pass);
    users.add(newCustomer);
    cout << "Customer '" << uname << "' added successfully." << endl;
}

bool Admin::removeCustomer(LinkedList<User*>& users, const string& username) { 
    User* userToRemove = users.find([&](User* u){ return u->getUsername() == username; });

    if (userToRemove == nullptr) {
        cout << "Error: User '" << username << "' not found." << endl;
        return false;
    }

    if (dynamic_cast<Customer*>(userToRemove)) {
        users.remove([&](User* u){ return u->getUsername() == username; });
        delete userToRemove;
        cout << "Customer '" << username << "' removed successfully." << endl;
        return true;
    } else {
        cout << "Error: Admins cannot be removed." << endl;
        return false;
    }
}

void Admin::addAccountToCustomer(Customer* customer, int accountType, const string& accNum, const string& cardNum, const string& sheba, const string& pin, const string& pin2) {
    if (!customer) {
        cout << "Error: Customer not found." << endl;
        return;
    }

    Account* newAccount = nullptr;
    switch (accountType) {
        case 1:
            newAccount = new SavingsAccount(accNum, cardNum, sheba, pin, pin2, 1.5);
            break;
        case 2:
            newAccount = new CurrentAccount(accNum, cardNum, sheba, pin, pin2);
            break;
        case 3:
            newAccount = new LoanAccount(accNum, cardNum, sheba, pin, pin2);
            break;
        default:
            cout << "Error: Invalid account type." << endl;
            return;
    }

    customer->addAccount(newAccount);
    cout << "Account created and added to customer '" << customer->getUsername() << "' successfully." << endl;
}

void Admin::changeUserInfo(User* userToChange, const string& newFirstName, const string& newLastName, int newAge) {
    if (userToChange) {
        userToChange->changeInfo(newFirstName, newLastName, newAge);
        cout << "User '" << userToChange->getUsername() << "' information updated." << endl;
    }
}