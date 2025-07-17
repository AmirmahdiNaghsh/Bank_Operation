//gharzolhasaneh
#ifndef LOANACCOUNT_H
#define LOANACCOUNT_H

#include "Account.h"

class LoanAccount : public Account {
public:
    LoanAccount(const string& accNum, const string& cardNum, const string& sheba, const string& pin, const string& pin2);
    void displayAccountTypeDifference() const override;
};

#endif