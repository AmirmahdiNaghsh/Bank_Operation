#ifndef DEPOSITACCOUNT_H
#define DEPOSITACCOUNT_H

#include "Account.h"


class DepositAccount : public Account {
private:
    double interestRate;
    time_t lastInterestDate;

public:
    DepositAccount(const string& cardNum, const string& accNum, const string& ibanNum, 
                  const string& primaryPass, const string& staticSecondPass, double rate = 0.15);
    
    void displayAccountTypeDifference() const override;
    void applyInterest();
    double calculateInterest() const;
    double getInterestRate() const;
    void setInterestRate(double rate);
};

#endif