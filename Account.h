#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <ctime>

using namespace std;

class Account {
protected:
    string cardNumber;
    string shebaNumber;
    string accountNumber;
    string cvv2;
    double balance;
    time_t expirationDate;
    string pin1;
    string pin2_static;
    string pin2_dynamic;

public:
    Account(const string& accNum, const string& cardNum, const string& sheba, const string& pin, const string& pin2);
    virtual ~Account();

    string getCardNumber() const;
    string getAccountNumber() const;

    double getBalance() const;

    bool isExpired() const;

    void setDynamicPin(const string& newDynamicPin);

    void deposit(double amount);

    bool withdraw(double amount);

    bool checkPin1(const string& p) const;
    bool checkPin2Static(const string& p) const;

    bool checkPin2Dynamic(const string& p) const;

    void changePins(const string& newPin1, const string& newPin2);

    virtual void displayInfo() const;
    virtual void displayAccountTypeDifference() const = 0;
};

#endif 