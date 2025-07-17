#include "Bank.h"
#include "Admin.h"
#include "Customer.h"
#include "SavingAccount.h"
#include "CurrentAccount.h"
#include <iostream>
#include <limits>

using namespace std;

Bank::Bank() : currentUser(nullptr) {
    srand(time(NULL));
    cout << "Welcome to the Bank Management System!" << endl;
}