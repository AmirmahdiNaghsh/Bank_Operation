#include "SavingsAccount.h"
#include <iostream>
#include <ctime>

using namespace std;

DepositAccount::DepositAccount(const string& cardNum, const string& accNum, const string& ibanNum, 
                              const string& primaryPass, const string& staticSecondPass, double rate)
    : Account(cardNum, accNum, ibanNum, primaryPass, staticSecondPass), 
      interestRate(rate), lastInterestDate(time(0)) {
}

void DepositAccount::displayAccountTypeDifference() const {
    cout << "=== Deposit Account Features ===" << endl;
    cout << "Account Type: Deposit Account (Sepordeh)" << endl;
    cout << "Interest Rate: " << (interestRate * 100) << "% per year" << endl;
    cout << "Interest earned so far: " << calculateInterest() << " Toman" << endl;
    cout << "Special Feature: Earns interest on deposited amount" << endl;
    cout << "Minimum Balance: 50,000 Toman" << endl;
}

void DepositAccount::applyInterest() {
    time_t now = time(0);
    tm* nowTm = localtime(&now);
    tm* lastTm = localtime(&lastInterestDate);
    
    
    if (nowTm->tm_mon != lastTm->tm_mon || nowTm->tm_year != lastTm->tm_year) {
        double monthlyInterest = balance * (interestRate / 12.0);
        balance += monthlyInterest;
        lastInterestDate = now;
        
        cout << "Monthly interest applied: " << monthlyInterest << " Toman" << endl;
        cout << "New balance: " << balance << " Toman" << endl;
    }
}

double DepositAccount::calculateInterest() const {
    
    return balance * (interestRate / 12.0);
}

double DepositAccount::getInterestRate() const {
    return interestRate;
}

void DepositAccount::setInterestRate(double rate) {
    if (rate >= 0 && rate <= 1.0) {
        interestRate = rate;
    }
}
