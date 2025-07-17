#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(const string& accNum, const string& cardNum, const string& sheba, const string& pin, const string& pin2, double rate);
    void displayAccountTypeDifference() const override;
    void applyInterest();
};

#endif