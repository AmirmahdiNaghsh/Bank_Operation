#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
#include <ctime>
using namespace std;

class Account {
protected:
    string cardNumber;           // Unique card number
    string accountNumber;        // Account number
    string iban;                // IBAN
    string cvv2;                // CVV2
    time_t expirationDate;      // Expiration date
    double balance;             // Balance
    string primaryPassword;     // Primary password
    string staticSecondPassword; // Static second password
    string dynamicSecondPassword; // Dynamic second password
    double dailyTransferAmount; // Daily transfer tracking
    time_t lastTransferDate;    // Last transfer date for daily limit reset

public:
    // Constructors
    Account();
    Account(const string& cardNum, const string& accNum, const string& ibanNum, 
           const string& primaryPass, const string& staticSecondPass);
    
    // Virtual destructor
    virtual ~Account();
    
    // Getters
    string getCardNumber() const;
    string getAccountNumber() const;
    string getIban() const;
    string getCvv2() const;
    time_t getExpirationDate() const;
    double getBalance() const;
    string getPrimaryPassword() const;
    string getStaticSecondPassword() const;
    string getDynamicSecondPassword() const;
    
    // Setters
    void setPrimaryPassword(const string& newPass);
    void setStaticSecondPassword(const string& newPass);
    void setDynamicSecondPassword(const string& newPass);
    
    // Account operations
    bool deposit(double amount);
    virtual bool withdraw(double amount);
    bool transfer(Account* toAccount, double amount, const string& secondPassword);
    
    // Display functions
    virtual void displayAccountInfo() const;
    virtual void displayAccountTypeDifference() const = 0; // Pure virtual for account type differences
    
    // Validation functions
    bool isValidAmount(double amount) const;
    bool hasSufficientBalance(double amount) const;
    bool isExpired() const;
    bool checkPrimaryPassword(const string& pass) const;
    bool checkSecondPassword(const string& pass, double amount) const;
    
    // Transfer limit checking
    bool checkTransferLimits(double amount) const;
    void updateDailyTransferAmount(double amount);
    void resetDailyLimitIfNeeded();
    
    // Dynamic password generation
    string generateDynamicPassword();
    void clearDynamicPassword();
};

#endif
