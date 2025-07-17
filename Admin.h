#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "LinkedList.h"
#include <string>

using namespace std;

class Customer;
class Account;

class Admin : public User {
private:
    static LinkedList<Customer*> allCustomers;
    static LinkedList<Admin*> allAdmins;
    static LinkedList<Account*> allAccounts;

public:
    Admin(const string& fname, const string& lname, const string& natId, 
          int userAge, const string& uname, const string& pass);
    
    ~Admin();
    
    // Customer management
    bool addCustomer(const string& fname, const string& lname, const string& natId,
                    int age, const string& uname, const string& pass);
    bool removeCustomer(const string& username);
    Customer* findCustomer(const string& username);
    void viewAllCustomers() const;
    
    // Admin management
    bool addAdmin(const string& fname, const string& lname, const string& natId,
                 int age, const string& uname, const string& pass);
    void viewAllAdmins() const;
    
    // Account management
    bool createAccount(const string& customerUsername, const string& accountType,
                      const string& cardNum, const string& accNum, const string& iban,
                      const string& primaryPass, const string& staticSecondPass);
    void viewAllAccounts() const;
    void viewSpecificAccount(const string& cardNumber) const;
    
    // User information management
    bool editUserInfo(const string& username, const string& newFirstName,
                     const string& newLastName, int newAge);
    void viewUsersByType() const;
    
    // Static data management
    static void addToCustomerList(Customer* customer);
    static void addToAdminList(Admin* admin);
    static void addToAccountList(Account* account);
    static Customer* findCustomerByUsername(const string& username);
    static Account* findAccountByCardNumber(const string& cardNumber);
    
    // Inherited virtual functions
    bool login(const string& username, const string& password) override;
    void showMainMenu() override;
    void displayInfo() const override;
    
    // Initialization
    static void initializeDefaultData();
};

#endif