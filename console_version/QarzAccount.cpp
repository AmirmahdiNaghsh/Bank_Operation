#include "QarzAccount.h"

QarzAccount::QarzAccount(const string& cardNum, const string& accNum, const string& iban,
                         const string& primaryPass, const string& staticSecondPass,
                         double initialBalance, int loanTerm)
    : Account(cardNum, accNum, iban, primaryPass, staticSecondPass, initialBalance),
      loanTermMonths(loanTerm) {}

void QarzAccount::displayAccountTypeDifference() const {
    cout << "Account Type: Loan Account (Qarz)" << endl;
    cout << "This account type is for interest-free loans with a fixed term of " 
         << loanTermMonths << " months." << endl;
}
