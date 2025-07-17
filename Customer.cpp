#include "Customer.h"
#include "Account.h" 
#include <iostream>

void Customer::displayInfo() const {
    User::displayInfo(); 
    
    cout << "--- Bank Accounts ---" << endl;
    if (bankAccounts.getCount() == 0) {
        cout << "This customer has no bank accounts." << endl;
    } else {
        bankAccounts.display(); 
    }
}