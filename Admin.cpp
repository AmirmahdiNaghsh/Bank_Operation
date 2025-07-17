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
