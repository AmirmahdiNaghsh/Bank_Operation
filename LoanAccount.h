#ifndef QARZACCOUNT_H
#define QARZACCOUNT_H

#include "Account.h"

// QarzAccount (Gharz-ol-hasaneh) - Interest-free loan account
class QarzAccount : public Account {
private:
    double loanAmount;
    double remainingLoan;
    time_t loanStartDate;
    time_t loanDueDate;
    int installments;
    double monthlyInstallment;

public:
    QarzAccount(const string& cardNum, const string& accNum, const string& ibanNum, 
               const string& primaryPass, const string& staticSecondPass,
               double loanAmt = 0, int installmentCount = 12);
    
    void displayAccountTypeDifference() const override;
    bool requestLoan(double amount, int months);
    bool payInstallment(double amount);
    double calculateMonthlyInstallment() const;
    bool isLoanDue() const;
    double getRemainingLoan() const;
    double getMonthlyInstallment() const;
    int getRemainingInstallments() const;
    time_t getLoanDueDate() const;
};

#endif