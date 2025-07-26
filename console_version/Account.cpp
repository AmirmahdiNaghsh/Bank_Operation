#include "Account.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;


Account::Account() 
    : cardNumber(""), accountNumber(""), iban(""), cvv2(""), expirationDate(0),
      balance(0.0), primaryPassword(""), staticSecondPassword(""), 
      dynamicSecondPassword(""), dailyTransferAmount(0.0), lastTransferDate(0) {
}


Account::Account(const string& cardNum, const string& accNum, const string& ibanNum,
                   const string& primaryPass, const string& staticSecondPass,
                   double initialBalance)
    : cardNumber(cardNum), accountNumber(accNum), iban(ibanNum),
      primaryPassword(primaryPass), staticSecondPassword(staticSecondPass),
      balance(initialBalance), dynamicSecondPassword(""), dailyTransferAmount(0.0), lastTransferDate(0) {    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(100, 999);
    cvv2 = to_string(dis(gen));
    
    
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    timeinfo->tm_year += 5;
    expirationDate = mktime(timeinfo);
}


Account::~Account() {}


string Account::getCardNumber() const { return cardNumber; }
string Account::getAccountNumber() const { return accountNumber; }
string Account::getIban() const { return iban; }
string Account::getCvv2() const { return cvv2; }
time_t Account::getExpirationDate() const { return expirationDate; }
double Account::getBalance() const { return balance; }
string Account::getPrimaryPassword() const { return primaryPassword; }
string Account::getStaticSecondPassword() const { return staticSecondPassword; }
string Account::getDynamicSecondPassword() const { return dynamicSecondPassword; }


void Account::setPrimaryPassword(const string& newPass) {
    primaryPassword = newPass;
}

void Account::setStaticSecondPassword(const string& newPass) {
    staticSecondPassword = newPass;
}

void Account::setDynamicSecondPassword(const string& newPass) {
    dynamicSecondPassword = newPass;
}


bool Account::deposit(double amount) {
    if (amount <= 0) {
        cout << "Invalid amount. Amount must be positive." << endl;
        return false;
    }
    balance += amount;
    cout << "Successfully deposited " << amount << " Toman." << endl;
    return true;
}

bool Account::withdraw(double amount) {
    if (!isValidAmount(amount)) {
        cout << "Invalid amount." << endl;
        return false;
    }
    if (!hasSufficientBalance(amount)) {
        cout << "Insufficient balance." << endl;
        return false;
    }
    balance -= amount;
    cout << "Successfully withdrew " << amount << " Toman." << endl;
    return true;
}

bool Account::transfer(Account* toAccount, double amount, const string& secondPassword) {
    if (!toAccount) {
        cout << "Invalid destination account." << endl;
        return false;
    }
    
    if (isExpired()) {
        cout << "Card has expired. Cannot perform transfer." << endl;
        return false;
    }
    
    if (!isValidAmount(amount)) {
        cout << "Invalid transfer amount." << endl;
        return false;
    }
    
    if (!checkTransferLimits(amount)) {
        cout << "Transfer amount exceeds daily or per-transaction limits." << endl;
        return false;
    }
    
    if (!checkSecondPassword(secondPassword, amount)) {
        cout << "Invalid second password." << endl;
        return false;
    }
    
    
    double fee = amount * 0.0001;
    double totalAmount = amount + fee;
    
    if (!hasSufficientBalance(totalAmount)) {
        cout << "Insufficient balance including transfer fee." << endl;
        return false;
    }
    
    
    balance -= totalAmount;
    toAccount->deposit(amount);
    updateDailyTransferAmount(amount);
    
    
    if (amount > 100000) {
        clearDynamicPassword();
    }
    
    cout << "Transfer successful. Amount: " << amount << " Toman, Fee: " << fee << " Toman" << endl;
    return true;
}


void Account::displayAccountInfo() const {
    cout << "=== Account Information ===" << endl;
    cout << "Card Number: " << cardNumber << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "IBAN: " << iban << endl;
    cout << "CVV2: " << cvv2 << endl;
    cout << "Balance: " << balance << " Toman" << endl;
    
    
    tm* timeinfo = localtime(&expirationDate);
    cout << "Expiration Date: " << (timeinfo->tm_mon + 1) << "/" 
         << (timeinfo->tm_year + 1900) << endl;
    
    cout << "Status: " << (isExpired() ? "Expired" : "Active") << endl;
}


bool Account::isValidAmount(double amount) const {
    return amount > 0;
}

bool Account::hasSufficientBalance(double amount) const {
    return balance >= amount;
}

bool Account::isExpired() const {
    return time(0) > expirationDate;
}

bool Account::checkPrimaryPassword(const string& pass) const {
    return primaryPassword == pass;
}

bool Account::checkSecondPassword(const string& pass, double amount) const {
    if (amount <= 100000) {
        
        return staticSecondPassword == pass;
    } else {
        
        return dynamicSecondPassword == pass && !dynamicSecondPassword.empty();
    }
}


bool Account::checkTransferLimits(double amount) const {
    
    if (amount > 3000000) {
        return false;
    }
    
    
    const_cast<Account*>(this)->resetDailyLimitIfNeeded();
    if (dailyTransferAmount + amount > 10000000) {
        return false;
    }
    
    return true;
}

void Account::updateDailyTransferAmount(double amount) {
    resetDailyLimitIfNeeded();
    dailyTransferAmount += amount;
    lastTransferDate = time(0);
}

void Account::resetDailyLimitIfNeeded() {
    time_t now = time(0);
    tm* nowTm = localtime(&now);
    tm* lastTm = localtime(&lastTransferDate);
    
    
    if (nowTm->tm_yday != lastTm->tm_yday || nowTm->tm_year != lastTm->tm_year) {
        dailyTransferAmount = 0.0;
    }
}


string Account::generateDynamicPassword() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(100000, 999999);
    dynamicSecondPassword = to_string(dis(gen));
    return dynamicSecondPassword;
}

void Account::clearDynamicPassword() {
    dynamicSecondPassword = "";
}
