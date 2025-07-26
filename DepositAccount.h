#ifndef DEPOSITACCOUNT_H
#define DEPOSITACCOUNT_H

#include "Account.h"
#include <string>

using namespace std;

class DepositAccount : public Account {
public:
    DepositAccount(const string& cardNum, const string& accNum, const string& iban,
                  const string& primaryPass, const string& staticSecondPass,
                  double initialBalance = 0.0);
    
    void displayAccountTypeDifference() const override;
};

#endif // DEPOSITACCOUNT_H
