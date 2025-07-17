#include "CurrentAccount.h"
#include <iostream>
using namespace std;

CurrentAccount::CurrentAccount(const string& accNum, const string& cardNum, const string& sheba, 
                               const string& pin, const string& pin2)
    : Account(accNum, cardNum, sheba, pin, pin2), hasCheckbook(false) {
}

void CurrentAccount::displayAccountTypeDifference() const {
    cout << "Account Type: Current Account" << endl;
    cout << "Checkbook Available: " << (hasCheckbook ? "Yes" : "No") << endl;
    cout << "Features: Suitable for daily transactions, overdraft facility" << endl;
}

void CurrentAccount::issueCheckbook() {
    hasCheckbook = true;
    cout << "Checkbook issued successfully!" << endl;
}
