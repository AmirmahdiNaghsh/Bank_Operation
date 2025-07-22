#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "LinkedList.h"
#include <string>

using namespace std;

class Account;

class Customer : public User {
private:
    LinkedList<Account*> bankAccounts;
    static const int MAX_ACCOUNTS = 5;

public:
    Customer(const string& fname, const string& lname, const string& natId, 
            int userAge, const string& uname, const string& pass);
    
    ~Customer();
    
    
    bool addAccount(Account* newAccount);
    bool removeAccount(const string& cardNumber);
    Account* findAccountByCardNumber(const string& cardNumber);
    LinkedList<Account*>& getAccounts();
    int getAccountCount() const;
    
    
    void viewAllAccounts() const;
    void viewSpecificAccount(const string& cardNumber) const;
    bool changeAccountPassword(const string& cardNumber, const string& passwordType, 
                              const string& oldPass, const string& newPass);
    bool performCardToCardTransfer(const string& fromCard, const string& toCard, 
                                  double amount, const string& secondPassword);
    string generateDynamicPassword(const string& cardNumber);
    
    
    bool login(const string& username, const string& password) override;
    void showMainMenu() override;
    void displayInfo() const override;
    
    
    string getCardHolderName(const string& cardNumber) const;
};

#endif