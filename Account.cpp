#include "Account.h"
#include<iostream>
#include<cstdlib>
#include<ctime>

Account::Account(const string& accNum, const string & cardNum, const string& sheba, const string& pin,const string& pin2)
: accountNumber(accNum),
cardNumber(cardNum),
shebaNumber(sheba),
pin1(pin),
pin2_static(pin2),
balance(0.0),
cvv2(to_string(rand()% 900 + 100)),
pin2_dynamic("")
{
    time_t now = time(0);
    tm *ltm - localtime(&now);
    ltm->tm_year += 5;
    this->expirationDate = mktime(ltm);
}

Account::~Account(){}

string Account::getCardNumber() const{
    return cardNumber;
}

string Account::getAccountNumber() const{
    return accountNumber;
}

string Account::getBalance() const{
    return balance;
}

bool Account::isExpired() const{
    return time(0) > expirationDate;
}