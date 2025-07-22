#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
#include <ctime>
using namespace std;

class Account {
protected:
    string cardNumber;           
    string accountNumber;        
    string iban;                
    string cvv2;                
    time_t expirationDate;      
    double balance;             
    string primaryPassword;     
    string staticSecondPassword; 
    string dynamicSecondPassword; 
    double dailyTransferAmount; 
    time_t lastTransferDate;    

public:
    
    Account();
    Account(const string& cardNum, const string& accNum, const string& ibanNum, 
           const string& primaryPass, const string& staticSecondPass);
    
    
    virtual ~Account();
    
    
    string getCardNumber() const;
    string getAccountNumber() const;
    string getIban() const;
    string getCvv2() const;
    time_t getExpirationDate() const;
    double getBalance() const;
    string getPrimaryPassword() const;
    string getStaticSecondPassword() const;
    string getDynamicSecondPassword() const;
    
    
    void setPrimaryPassword(const string& newPass);
    void setStaticSecondPassword(const string& newPass);
    void setDynamicSecondPassword(const string& newPass);
    
    
    bool deposit(double amount);
    virtual bool withdraw(double amount);
    bool transfer(Account* toAccount, double amount, const string& secondPassword);
    
    
    virtual void displayAccountInfo() const;
    virtual void displayAccountTypeDifference() const = 0; 
    
    
    bool isValidAmount(double amount) const;
    bool hasSufficientBalance(double amount) const;
    bool isExpired() const;
    bool checkPrimaryPassword(const string& pass) const;
    bool checkSecondPassword(const string& pass, double amount) const;
    
    
    bool checkTransferLimits(double amount) const;
    void updateDailyTransferAmount(double amount);
    void resetDailyLimitIfNeeded();
    
    
    string generateDynamicPassword();
    void clearDynamicPassword();
};

#endif
