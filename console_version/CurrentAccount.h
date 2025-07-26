#ifndef CURRENTACCOUNT_H
#define CURRENTACCOUNT_H

#include "Account.h"


class CurrentAccount : public Account {
private:
    bool hasCheckbook;
    double overdraftLimit;
    double usedOverdraft;

public:
    CurrentAccount(const string& cardNum, const string& accNum, const string& ibanNum, 
                  const string& primaryPass, const string& staticSecondPass, 
                  double overdraftLim = 500000);
    
    void displayAccountTypeDifference() const override;
    void issueCheckbook();
    bool withdraw(double amount) override;
    bool hasOverdraftAvailable(double amount) const;
    double getAvailableBalance() const;
    double getOverdraftLimit() const;
    double getUsedOverdraft() const;
    void repayOverdraft(double amount);
};

#endif