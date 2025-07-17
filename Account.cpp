#include "Account.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Account::Account(const string& accNum, const string& cardNum, const string& sheba, const string& pin, const string& pin2)
    : accountNumber(accNum),
      cardNumber(cardNum),
      shebaNumber(sheba),
      pin1(pin),
      pin2_static(pin2),
      balance(0.0),
      cvv2(to_string(rand() % 900 + 100)),
      pin2_dynamic("") {
    time_t now = time(0);
    tm *ltm = localtime(&now); 
    ltm->tm_year += 5;
    this->expirationDate = mktime(ltm);
}

Account::~Account() {}

string Account::getCardNumber() const {
    return cardNumber;
}

string Account::getAccountNumber() const {
    return accountNumber;
}

double Account::getBalance() const {
    return balance;
}

bool Account::isExpired() const {
    return time(0) > expirationDate;
}

void Account::setDynamicPin(const string& newDynamicPin) {
    this->pin2_dynamic = newDynamicPin;
}

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

bool Account::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

bool Account::checkPin1(const string& p) const {
    return pin1 == p;
}

bool Account::checkPin2Static(const string& p) const {
    return pin2_static == p;
}

bool Account::checkPin2Dynamic(const string& p) const {
    if (!pin2_dynamic.empty() && pin2_dynamic == p) {
        return true;
    }
    return false;
}

void Account::changePins(const string& newPin1, const string& newPin2) {
    this->pin1 = newPin1;
    this->pin2_static = newPin2;
}

void Account::displayInfo() const {
    cout << "Account Number: " << accountNumber << endl;
    cout << "Card Number: " << cardNumber << endl;
    cout << "Sheba: " << shebaNumber << endl;
    cout << "Balance: " << balance << " Toman" << endl;
// Start Gpt codes
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&expirationDate));
    cout << "Expiration Date: " << buffer << endl;
// end Gpt codes
}