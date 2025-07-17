//Jari
#ifndef CURRENTACCOUNT_H
#define CURRENTACCOUNT_H

#include "Account.h"

class CurrentAccount : public Account {
private:
    bool hasCheckbook;

public:
    CurrentAccount(const string& accNum, const string& cardNum, const string& sheba, const string& pin, const string& pin2);
    void displayAccountTypeDifference() const override;
    void issueCheckbook();
};

#endif