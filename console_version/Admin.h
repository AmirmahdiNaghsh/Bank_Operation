#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "LinkedList.h"
#include <string>

using namespace std;

class Customer;
class Account;

class Admin : public User {
// ...existing code...

public:
    Admin(const string& fname, const string& lname, const string& natId, 
          int userAge, const string& uname, const string& pass);
    ~Admin();

    bool addCustomer(const string& fname, const string& lname, const string& natId,
                    int age, const string& uname, const string& pass);
    bool removeCustomer(const string& username);
    Customer* findCustomer(const string& username);
    void viewAllCustomers() const;

    bool addAdmin(const string& fname, const string& lname, const string& natId,
                 int age, const string& uname, const string& pass);
    void viewAllAdmins() const;

    bool createAccount(const string& customerUsername, const string& accountType,
                      const string& cardNum, const string& accNum, const string& iban,
                      const string& primaryPass, const string& staticSecondPass);
    void viewAllAccounts() const;
    void viewSpecificAccount(const string& cardNumber) const;

    bool editUserInfo(const string& username, const string& newFirstName,
                     const string& newLastName, int newAge);
    void viewUsersByType() const;

    bool login(const string& username, const string& password) override;
    void showMainMenu() override;
    void displayInfo() const override;
    
    
    static void initializeDefaultData();
};

#endif