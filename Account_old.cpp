#include "Account.h"
#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

// Default constructor
Account::Account() 
    : cardNumber(""), accountNumber(""), iban(""), cvv2(""), expirationDate(0),
      balance(0.0), primaryPassword(""), staticSecondPassword(""), 
      dynamicSecondPassword(""), dailyTransferAmount(0.0), lastTransferDate(0) {
}

// Parameterized constructor
Account::Account(const string& cardNum, const string& accNum, const string& ibanNum, 
                const string& primaryPass, const string& staticSecondPass)
    : cardNumber(cardNum), accountNumber(accNum), iban(ibanNum),
      primaryPassword(primaryPass), staticSecondPassword(staticSecondPass),
      balance(0.0), dynamicSecondPassword(""), dailyTransferAmount(0.0), lastTransferDate(0) {
    
    // Generate random CVV2
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(100, 999);
    cvv2 = to_string(dis(gen));
    
    // Set expiration date to 5 years from now
    time_t now = time(0);
    tm* timeinfo = localtime(&now);
    timeinfo->tm_year += 5;
    expirationDate = mktime(timeinfo);
}

// Virtual destructor
Account::~Account() {}

// Getters
string Account::getCardNumber() const { return cardNumber; }
string Account::getAccountNumber() const { return accountNumber; }
string Account::getIban() const { return iban; }
string Account::getCvv2() const { return cvv2; }
time_t Account::getExpirationDate() const { return expirationDate; }
double Account::getBalance() const { return balance; }
string Account::getPrimaryPassword() const { return primaryPassword; }
string Account::getStaticSecondPassword() const { return staticSecondPassword; }
string Account::getDynamicSecondPassword() const { return dynamicSecondPassword; }

// Setters
void Account::setPrimaryPassword(const string& newPass) {
    primaryPassword = newPass;
}

void Account::setStaticSecondPassword(const string& newPass) {
    staticSecondPassword = newPass;
}

void Account::setDynamicSecondPassword(const string& newPass) {
    dynamicSecondPassword = newPass;
}

// Account operations
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
    
    // Calculate fee (0.01%)
    double fee = amount * 0.0001;
    double totalAmount = amount + fee;
    
    if (!hasSufficientBalance(totalAmount)) {
        cout << "Insufficient balance including transfer fee." << endl;
        return false;
    }
    
    // Perform transfer
    balance -= totalAmount;
    toAccount->deposit(amount);
    updateDailyTransferAmount(amount);
    
    // Clear dynamic password after use
    if (amount > 100000) {
        clearDynamicPassword();
    }
    
    cout << "Transfer successful. Amount: " << amount << " Toman, Fee: " << fee << " Toman" << endl;
    return true;
}

// Display functions
void Account::displayAccountInfo() const {
    cout << "=== Account Information ===" << endl;
    cout << "Card Number: " << cardNumber << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "IBAN: " << iban << endl;
    cout << "CVV2: " << cvv2 << endl;
    cout << "Balance: " << balance << " Toman" << endl;
    
    // Display expiration date
    tm* timeinfo = localtime(&expirationDate);
    cout << "Expiration Date: " << (timeinfo->tm_mon + 1) << "/" 
         << (timeinfo->tm_year + 1900) << endl;
    
    cout << "Status: " << (isExpired() ? "Expired" : "Active") << endl;
}

// Validation functions
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
        // Use static second password for amounts up to 100,000 Toman
        return staticSecondPassword == pass;
    } else {
        // Use dynamic second password for amounts over 100,000 Toman
        return dynamicSecondPassword == pass && !dynamicSecondPassword.empty();
    }
}

// Transfer limit checking
bool Account::checkTransferLimits(double amount) const {
    // Check per-transaction limit (3,000,000 Toman)
    if (amount > 3000000) {
        return false;
    }
    
    // Check daily limit (10,000,000 Toman)
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
    
    // Reset if it's a different day
    if (nowTm->tm_yday != lastTm->tm_yday || nowTm->tm_year != lastTm->tm_year) {
        dailyTransferAmount = 0.0;
    }
}

// Dynamic password generation
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

bool Account::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

bool Account::checkPin1(const string& p) const {
    return pin1 == p;
}

bool Account::checkPin2Static(const string& p) const {
    return pin2_static == p;
}

bool Account::checkPin2Dynamic(const string& p) const {
    if (!pin2_dynamic.empty() && pin2_dynamic == p) {
        return true;
    }
    return false;
}

void Account::changePins(const string& newPin1, const string& newPin2) {
    this->pin1 = newPin1;
    this->pin2_static = newPin2;
}

void Account::displayInfo() const {
    cout << "Account Number: " << accountNumber << endl;
    cout << "Card Number: " << cardNumber << endl;
    cout << "Sheba: " << shebaNumber << endl;
    cout << "Balance: " << balance << " Toman" << endl;
// Start Gpt codes
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&expirationDate));
    cout << "Expiration Date: " << buffer << endl;
// end Gpt codes
}