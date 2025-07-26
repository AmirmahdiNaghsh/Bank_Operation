#ifndef BANKINGSYSTEM_H
#define BANKINGSYSTEM_H

#include "LinkedList.h"
#include "Customer.h"
#include "Admin.h"
#include "Account.h"
#include <QObject>

class BankingSystem : public QObject
{
    Q_OBJECT

public:
    static BankingSystem& getInstance();
    
    void initializeSystem();
    
    // Authentication
    Customer* authenticateCustomer(const QString& username, const QString& password);
    Admin* authenticateAdmin(const QString& username, const QString& password);
    
    // Customer management
    bool registerCustomer(const QString& firstName, const QString& lastName, 
                         const QString& nationalId, int age, 
                         const QString& username, const QString& password);
    
    // Data access
    LinkedList<Customer*>& getAllCustomers() { return allCustomers; }
    LinkedList<Admin*>& getAllAdmins() { return allAdmins; }
    LinkedList<Account*>& getAllAccounts() { return allAccounts; }
    
    // Utility functions
    Customer* findCustomerByUsername(const QString& username);
    Admin* findAdminByUsername(const QString& username);
    Account* findAccountByCardNumber(const QString& cardNumber);
    QString getCardHolderName(const QString& cardNumber);

private:
    BankingSystem(QObject *parent = nullptr);
    ~BankingSystem();
    
    // Singleton pattern
    static BankingSystem* instance;
    
    // Data storage
    LinkedList<Customer*> allCustomers;
    LinkedList<Admin*> allAdmins;
    LinkedList<Account*> allAccounts;
    
    void createSampleData();
};

#endif // BANKINGSYSTEM_H
