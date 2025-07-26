#include "DepositAccount.h"

DepositAccount::DepositAccount(const string& cardNum, const string& accNum, const string& iban,
                             const string& primaryPass, const string& staticSecondPass,
                             double initialBalance)
    : Account(cardNum, accNum, iban, primaryPass, staticSecondPass, initialBalance) {}

void DepositAccount::displayAccountTypeDifference() const {
    cout << "Account Type: Deposit Account" << endl;
    cout << "This account type is suitable for long-term savings with higher interest rates." << endl;
}
