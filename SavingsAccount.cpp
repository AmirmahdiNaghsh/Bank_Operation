#include "SavingsAccount.h"
#include <iostream>
using namespace std;

SavingsAccount::SavingsAccount(const string& accNum, const string& cardNum, const string& sheba, 
                               const string& pin, const string& pin2, double rate)
    : Account(accNum, cardNum, sheba, pin, pin2), interestRate(rate) {
}

void SavingsAccount::displayAccountTypeDifference() const {
    cout << "Account Type: Savings Account" << endl;
    cout << "Interest Rate: " << interestRate << "%" << endl;
    cout << "Features: Earns interest on deposits" << endl;
}

void SavingsAccount::applyInterest() {
    balance = balance * (1 + interestRate / 100);
    cout << "Interest applied. New balance: " << balance << endl;
}
