#include "CurrentAccount.h"
#include <iostream>
using namespace std;

CurrentAccount::CurrentAccount(const string& cardNum, const string& accNum, const string& ibanNum, 
                              const string& primaryPass, const string& staticSecondPass, 
                              double overdraftLim)
    : Account(cardNum, accNum, ibanNum, primaryPass, staticSecondPass), 
      hasCheckbook(false), overdraftLimit(overdraftLim), usedOverdraft(0.0) {
}

void CurrentAccount::displayAccountTypeDifference() const {
    cout << "=== Current Account Features ===" << endl;
    cout << "Account Type: Current Account (Jari)" << endl;
    cout << "Checkbook Available: " << (hasCheckbook ? "Yes" : "No") << endl;
    cout << "Overdraft Limit: " << overdraftLimit << " Toman" << endl;
    cout << "Used Overdraft: " << usedOverdraft << " Toman" << endl;
    cout << "Available Overdraft: " << (overdraftLimit - usedOverdraft) << " Toman" << endl;
    cout << "Special Feature: Overdraft facility and checkbook services" << endl;
    cout << "Total Available Balance: " << getAvailableBalance() << " Toman" << endl;
}

void CurrentAccount::issueCheckbook() {
    if (!hasCheckbook) {
        hasCheckbook = true;
        cout << "Checkbook issued successfully!" << endl;
        cout << "You can now write checks from this account." << endl;
    } else {
        cout << "Checkbook already issued for this account." << endl;
    }
}

bool CurrentAccount::withdraw(double amount) {
    if (!isValidAmount(amount)) {
        cout << "Invalid amount." << endl;
        return false;
    }
    
    if (amount <= balance) {
        // Normal withdrawal from balance
        balance -= amount;
        cout << "Successfully withdrew " << amount << " Toman from balance." << endl;
        return true;
    } else if (hasOverdraftAvailable(amount - balance)) {
        // Use overdraft
        double overdraftNeeded = amount - balance;
        usedOverdraft += overdraftNeeded;
        balance = 0;
        cout << "Successfully withdrew " << amount << " Toman (used " 
             << overdraftNeeded << " Toman overdraft)." << endl;
        return true;
    } else {
        cout << "Insufficient funds (including overdraft limit)." << endl;
        return false;
    }
}

bool CurrentAccount::hasOverdraftAvailable(double amount) const {
    return (usedOverdraft + amount) <= overdraftLimit;
}

double CurrentAccount::getAvailableBalance() const {
    return balance + (overdraftLimit - usedOverdraft);
}

double CurrentAccount::getOverdraftLimit() const {
    return overdraftLimit;
}

double CurrentAccount::getUsedOverdraft() const {
    return usedOverdraft;
}

void CurrentAccount::repayOverdraft(double amount) {
    if (amount <= 0) {
        cout << "Invalid repayment amount." << endl;
        return;
    }
    
    if (amount > usedOverdraft) {
        cout << "Repayment amount exceeds used overdraft." << endl;
        return;
    }
    
    usedOverdraft -= amount;
    cout << "Overdraft repaid: " << amount << " Toman. Remaining overdraft debt: " 
         << usedOverdraft << " Toman" << endl;
}
