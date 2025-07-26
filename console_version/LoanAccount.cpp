#include "LoanAccount.h"
#include <iostream>
#include <ctime>
using namespace std;

QarzAccount::QarzAccount(const string& cardNum, const string& accNum, const string& ibanNum, 
                        const string& primaryPass, const string& staticSecondPass,
                        double loanAmt, int installmentCount)
    : Account(cardNum, accNum, ibanNum, primaryPass, staticSecondPass),
      loanAmount(loanAmt), remainingLoan(loanAmt), installments(installmentCount),
      loanStartDate(time(0)), monthlyInstallment(0) {
    
    
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    timeinfo->tm_mon += installments;
    loanDueDate = mktime(timeinfo);
    
    if (loanAmount > 0) {
        monthlyInstallment = calculateMonthlyInstallment();
    }
}

void QarzAccount::displayAccountTypeDifference() const {
    cout << "=== Qarz Account Features ===" << endl;
    cout << "Account Type: Qarz Account (Gharz-ol-hasaneh)" << endl;
    cout << "Special Feature: Interest-free Islamic banking loan" << endl;
    cout << "Loan Amount: " << loanAmount << " Toman" << endl;
    cout << "Remaining Loan: " << remainingLoan << " Toman" << endl;
    cout << "Monthly Installment: " << monthlyInstallment << " Toman" << endl;
    cout << "Remaining Installments: " << getRemainingInstallments() << endl;
    cout << "Loan Status: " << (isLoanDue() ? "Overdue" : "Current") << endl;
    cout << "Islamic Banking Compliant: No interest charged" << endl;
}

bool QarzAccount::requestLoan(double amount, int months) {
    if (remainingLoan > 0) {
        cout << "Cannot request new loan. Existing loan must be paid first." << endl;
        return false;
    }
    
    if (amount <= 0 || months <= 0) {
        cout << "Invalid loan parameters." << endl;
        return false;
    }
    
    loanAmount = amount;
    remainingLoan = amount;
    installments = months;
    loanStartDate = time(0);
    
    
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    timeinfo->tm_mon += months;
    loanDueDate = mktime(timeinfo);
    
    monthlyInstallment = calculateMonthlyInstallment();
    
    
    balance += amount;
    
    cout << "Loan approved and disbursed!" << endl;
    cout << "Loan Amount: " << amount << " Toman" << endl;
    cout << "Monthly Installment: " << monthlyInstallment << " Toman" << endl;
    cout << "Installments: " << months << " months" << endl;
    
    return true;
}

bool QarzAccount::payInstallment(double amount) {
    if (remainingLoan <= 0) {
        cout << "No outstanding loan to pay." << endl;
        return false;
    }
    
    if (amount <= 0) {
        cout << "Invalid payment amount." << endl;
        return false;
    }
    
    if (amount > balance) {
        cout << "Insufficient balance for installment payment." << endl;
        return false;
    }
    
    double paymentAmount = min(amount, remainingLoan);
    remainingLoan -= paymentAmount;
    balance -= paymentAmount;
    
    cout << "Installment paid: " << paymentAmount << " Toman" << endl;
    cout << "Remaining loan: " << remainingLoan << " Toman" << endl;
    
    if (remainingLoan <= 0) {
        cout << "Congratulations! Loan fully paid off." << endl;
    }
    
    return true;
}

double QarzAccount::calculateMonthlyInstallment() const {
    if (installments > 0) {
        return loanAmount / installments;
    }
    return 0;
}

bool QarzAccount::isLoanDue() const {
    return time(0) > loanDueDate && remainingLoan > 0;
}

double QarzAccount::getRemainingLoan() const {
    return remainingLoan;
}

double QarzAccount::getMonthlyInstallment() const {
    return monthlyInstallment;
}

int QarzAccount::getRemainingInstallments() const {
    if (monthlyInstallment > 0) {
        return static_cast<int>(remainingLoan / monthlyInstallment);
    }
    return 0;
}

time_t QarzAccount::getLoanDueDate() const {
    return loanDueDate;
}
