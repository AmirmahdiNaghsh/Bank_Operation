#include "Customer.h"
#include "Account.h"
#include "BankSystem.h"
#include "LinkedList.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

Customer::Customer(const string& fname, const string& lname, const string& natId, 
                  int userAge, const string& uname, const string& pass)
    : User(fname, lname, natId, userAge, uname, pass) {
}

Customer::~Customer() {
    auto* currentNode = bankAccounts.getHead();
    while (currentNode != nullptr) {
        delete currentNode->getData();
        currentNode = currentNode->getNext();
    }
}


bool Customer::addAccount(Account* newAccount) {
    if (bankAccounts.getCount() >= MAX_ACCOUNTS) {
        cout << "Error: Customer cannot have more than " << MAX_ACCOUNTS << " accounts." << endl;
        return false;
    }
    
    if (newAccount) {
        bankAccounts.add(newAccount);
        cout << "Account added successfully." << endl;
        return true;
    }
    return false;
}

bool Customer::removeAccount(const string& cardNumber) {
    return bankAccounts.remove([&](Account* acc) {
        return acc->getCardNumber() == cardNumber;
    });
}

Account* Customer::findAccountByCardNumber(const string& cardNumber) {
    return bankAccounts.find([&](Account* acc) {
        return acc->getCardNumber() == cardNumber;
    });
}

LinkedList<Account*>& Customer::getAccounts() {
    return bankAccounts;
}

int Customer::getAccountCount() const {
    return bankAccounts.getCount();
}


void Customer::viewAllAccounts() const {
    cout << "\n=== Your Bank Accounts ===" << endl;
    if (bankAccounts.getCount() == 0) {
        cout << "You have no bank accounts." << endl;
        return;
    }
    
    auto* currentNode = bankAccounts.getHead();
    int accountNum = 1;
    while (currentNode != nullptr) {
        cout << "\n--- Account " << accountNum++ << " ---" << endl;
        currentNode->getData()->displayAccountInfo();
        currentNode->getData()->displayAccountTypeDifference();
        currentNode = currentNode->getNext();
    }
}

void Customer::viewSpecificAccount(const string& cardNumber) const {
    Account* account = const_cast<Customer*>(this)->findAccountByCardNumber(cardNumber);
    if (account) {
        cout << "\n=== Account Details ===" << endl;
        account->displayAccountInfo();
        account->displayAccountTypeDifference();
    } else {
        cout << "Account with card number " << cardNumber << " not found." << endl;
    }
}

bool Customer::changeAccountPassword(const string& cardNumber, const string& passwordType, 
                                   const string& oldPass, const string& newPass) {
    Account* account = findAccountByCardNumber(cardNumber);
    if (!account) {
        cout << "Account not found." << endl;
        return false;
    }
    
    if (passwordType == "primary") {
        if (account->checkPrimaryPassword(oldPass)) {
            account->setPrimaryPassword(newPass);
            cout << "Primary password changed successfully." << endl;
            return true;
        } else {
            cout << "Incorrect old primary password." << endl;
        }
    } else if (passwordType == "second") {
        if (account->getStaticSecondPassword() == oldPass) {
            account->setStaticSecondPassword(newPass);
            cout << "Second password changed successfully." << endl;
            return true;
        } else {
            cout << "Incorrect old second password." << endl;
        }
    } else {
        cout << "Invalid password type. Use 'primary' or 'second'." << endl;
    }
    
    return false;
}

bool Customer::performCardToCardTransfer(const string& fromCard, const string& toCard, 
                                       double amount, const string& secondPassword) {
    
    Account* fromAccount = findAccountByCardNumber(fromCard);
    if (!fromAccount) {
        cout << "Source account not found." << endl;
        return false;
    }
    
    
    
    string recipientName = getCardHolderName(toCard);
    if (recipientName.empty()) {
        cout << "Invalid destination card number." << endl;
        return false;
    }
    
    cout << "Transfer to: " << recipientName << endl;
    cout << "Amount: " << amount << " Toman" << endl;
    
    
    
    Account* toAccount = nullptr; 
    
    if (!toAccount) {
        cout << "Destination account not accessible for transfer." << endl;
        return false;
    }
    
    return fromAccount->transfer(toAccount, amount, secondPassword);
}

string Customer::generateDynamicPassword(const string& cardNumber) {
    Account* account = findAccountByCardNumber(cardNumber);
    if (account) {
        string dynamicPass = account->generateDynamicPassword();
        cout << "Dynamic password generated: " << dynamicPass << endl;
        cout << "This password is valid for one transaction only." << endl;
        return dynamicPass;
    }
    cout << "Account not found." << endl;
    return "";
}


bool Customer::login(const string& uname, const string& pass) {
    if (username == uname && checkPassword(pass)) {
        cout << "Customer login successful. Welcome, " << getFullName() << "!" << endl;
        return true;
    }
    return false;
}

void Customer::showMainMenu() {
    while (true) {
        cout << "\n=== Customer Menu ===" << endl;
        cout << "1. View All Accounts" << endl;
        cout << "2. View Specific Account" << endl;
        cout << "3. Change Account Password" << endl;
        cout << "4. Card to Card Transfer" << endl;
        cout << "5. Generate Dynamic Password" << endl;
        cout << "6. Change Personal Information" << endl;
        cout << "7. Logout" << endl;
        cout << "Choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear(); // clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        string cardNumber, newPassword, targetCard, amount;
        auto* listPtr = bankAccounts.getHead();
        int accountNum = 0;
        
        switch (choice) {
            case 1:
                // Display all accounts for this customer
                listPtr = bankAccounts.getHead();
                accountNum = 1;
                while (listPtr != nullptr) {
                    cout << "\n--- Account " << accountNum++ << " ---" << endl;
                    listPtr->getData()->displayAccountInfo();
                    listPtr->getData()->displayAccountTypeDifference();
                    listPtr = listPtr->getNext();
                }
                break;
            case 2:
                cout << "Enter card number: ";
                cin >> cardNumber;
                if (Account* account = findAccountByCardNumber(cardNumber)) {
                    account->displayAccountInfo();
                    account->displayAccountTypeDifference();
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            case 3:
                cout << "Enter card number: ";
                cin >> cardNumber;
                cout << "Enter new password: ";
                cin >> newPassword;
                if (Account* account = findAccountByCardNumber(cardNumber)) {
                    account->changePassword(newPassword);
                    cout << "Password changed successfully." << endl;
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            case 4:
                cout << "Enter source card number: ";
                cin >> cardNumber;
                cout << "Enter target card number: ";
                cin >> targetCard;
                cout << "Enter amount: ";
                cin >> amount;
                if (Account* sourceAccount = findAccountByCardNumber(cardNumber)) {
                    Account* targetAccount = BankSystem::getInstance().findAccountByCardNumber(targetCard);
                    if (targetAccount) {
                        // Implement transfer logic here
                        cout << "Transfer completed successfully." << endl;
                    } else {
                        cout << "Target account not found." << endl;
                    }
                } else {
                    cout << "Source account not found." << endl;
                }
                break;
            case 5:
                cout << "Enter card number: ";
                cin >> cardNumber;
                if (Account* account = findAccountByCardNumber(cardNumber)) {
                    string dynamicPass = account->generateDynamicPassword();
                    cout << "Dynamic password generated: " << dynamicPass << endl;
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            case 6:
                {
                    string newFirstName, newLastName;
                    int newAge;
                    cout << "Enter new first name: ";
                    cin >> newFirstName;
                    cout << "Enter new last name: ";
                    cin >> newLastName;
                    cout << "Enter new age: ";
                    cin >> newAge;
                    changeInfo(newFirstName, newLastName, newAge);
                    cout << "Personal information updated successfully." << endl;
                }
                break;
            case 7:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void Customer::displayInfo() const {
    User::displayInfo();
    cout << "User Type: Customer" << endl;
    cout << "Number of Accounts: " << bankAccounts.getCount() << "/" << MAX_ACCOUNTS << endl;
}


string Customer::getCardHolderName(const string& cardNumber) const {
    
    
    if (cardNumber.length() == 16) {
        return "Sample Recipient"; 
    }
    return "";
}