#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include "Customer.h"
#include "Admin.h"
#include "Account.h"
#include "LinkedList.h"
#include <string>

class BankSystem {
private:
    LinkedList<Customer*> allCustomers;
    LinkedList<Admin*> allAdmins;
    LinkedList<Account*> allAccounts;
    BankSystem() {}
    BankSystem(const BankSystem&) = delete;
    BankSystem& operator=(const BankSystem&) = delete;
public:
    static BankSystem& getInstance() {
        static BankSystem instance;
        return instance;
    }
    LinkedList<Customer*>& getAllCustomers() { return allCustomers; }
    LinkedList<Admin*>& getAllAdmins() { return allAdmins; }
    LinkedList<Account*>& getAllAccounts() { return allAccounts; }
    void registerCustomer(Customer* customer) { allCustomers.add(customer); }
    void registerAdmin(Admin* admin) { allAdmins.add(admin); }
    void registerAccount(Account* account) { allAccounts.add(account); }
    Customer* findCustomerByUsername(const std::string& username) {
        return allCustomers.find([&](Customer* c){ return c->getUsername() == username; });
    }
    Account* findAccountByCardNumber(const std::string& cardNumber) {
        return allAccounts.find([&](Account* a){ return a->getCardNumber() == cardNumber; });
    }
};

#endif // BANKSYSTEM_H
