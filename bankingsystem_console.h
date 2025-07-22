#ifndef BANKINGSYSTEM_CONSOLE_H
#define BANKINGSYSTEM_CONSOLE_H

#include "LinkedList.h"
#include "Customer.h"
#include "Admin.h"
#include "Account.h"
#include <string>

class BankingSystemConsole
{
public:
    static BankingSystemConsole& getInstance();
    
    void initializeSystem();
    
    // Authentication methods
    Customer* authenticateCustomer(const std::string& username, const std::string& password);
    Admin* authenticateAdmin(const std::string& username, const std::string& password);
    
    // Registration and user management
    bool registerCustomer(const std::string& firstName, const std::string& lastName, 
                         const std::string& nationalId, int age, 
                         const std::string& username, const std::string& password);
    
    // Data access methods
    LinkedList<Customer*>& getAllCustomers() { return allCustomers; }
    LinkedList<Admin*>& getAllAdmins() { return allAdmins; }
    LinkedList<Account*>& getAllAccounts() { return allAccounts; }
    
    // Search methods
    Customer* findCustomerByUsername(const std::string& username);
    Admin* findAdminByUsername(const std::string& username);
    Account* findAccountByCardNumber(const std::string& cardNumber);
    std::string getCardHolderName(const std::string& cardNumber);

private:
    BankingSystemConsole();
    ~BankingSystemConsole();
    
    // Singleton instance
    static BankingSystemConsole* instance;
    
    // Data storage
    LinkedList<Customer*> allCustomers;
    LinkedList<Admin*> allAdmins;
    LinkedList<Account*> allAccounts;
    
    void createSampleData();
};

#endif // BANKINGSYSTEM_CONSOLE_H
