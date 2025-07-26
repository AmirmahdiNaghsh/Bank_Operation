#ifndef QARZACCOUNT_H
#define QARZACCOUNT_H

#include "Account.h"
#include <string>

using namespace std;

class QarzAccount : public Account {
private:
    int loanTermMonths;

public:
    QarzAccount(const string& cardNum, const string& accNum, const string& iban,
              const string& primaryPass, const string& staticSecondPass,
              double initialBalance = 0.0, int loanTerm = 12);
    
    void displayAccountTypeDifference() const override;
};

#endif // QARZACCOUNT_H
