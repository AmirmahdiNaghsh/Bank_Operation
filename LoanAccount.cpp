#include "LoanAccount.h"
#include <iostream>
using namespace std;

LoanAccount::LoanAccount(const string& accNum, const string& cardNum, const string& sheba, 
                         const string& pin, const string& pin2)
    : Account(accNum, cardNum, sheba, pin, pin2) {
}

void LoanAccount::displayAccountTypeDifference() const {
    cout << "Account Type: Qard-ul-Hasana (Interest-free Loan Account)" << endl;
    cout << "Features: Islamic banking compliant, no interest charged or paid" << endl;
}
