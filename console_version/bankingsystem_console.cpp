#include "bankingsystem_console.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "LoanAccount.h"

BankingSystemConsole* BankingSystemConsole::instance = nullptr;

BankingSystemConsole::BankingSystemConsole()
{
}

BankingSystemConsole::~BankingSystemConsole()
{
    // Clean up memory - customers
    auto* customerNode = allCustomers.getHead();
    while (customerNode != nullptr) {
        delete customerNode->getData();
        customerNode = customerNode->getNext();
    }
    
    // Clean up memory - admins
    auto* adminNode = allAdmins.getHead();
    while (adminNode != nullptr) {
        delete adminNode->getData();
        adminNode = adminNode->getNext();
    }
}

BankingSystemConsole& BankingSystemConsole::getInstance()
{
    if (instance == nullptr) {
        instance = new BankingSystemConsole();
    }
    return *instance;
}

void BankingSystemConsole::initializeSystem()
{
    createSampleData();
}

Customer* BankingSystemConsole::authenticateCustomer(const std::string& username, const std::string& password)
{
    auto* currentNode = allCustomers.getHead();
    while (currentNode != nullptr) {
        Customer* customer = currentNode->getData();
        if (customer->getUsername() == username && 
            customer->checkPassword(password)) {
            return customer;
        }
        currentNode = currentNode->getNext();
    }
    return nullptr;
}

Admin* BankingSystemConsole::authenticateAdmin(const std::string& username, const std::string& password)
{
    auto* currentNode = allAdmins.getHead();
    while (currentNode != nullptr) {
        Admin* admin = currentNode->getData();
        if (admin->getUsername() == username && 
            admin->checkPassword(password)) {
            return admin;
        }
        currentNode = currentNode->getNext();
    }
    return nullptr;
}

bool BankingSystemConsole::registerCustomer(const std::string& firstName, const std::string& lastName, 
                                           const std::string& nationalId, int age, 
                                           const std::string& username, const std::string& password)
{
    // Check if username already exists
    if (findCustomerByUsername(username) != nullptr) {
        return false;
    }
    
    Customer* newCustomer = new Customer(firstName, lastName, nationalId, age, username, password);
    allCustomers.add(newCustomer);
    return true;
}

Customer* BankingSystemConsole::findCustomerByUsername(const std::string& username)
{
    auto* currentNode = allCustomers.getHead();
    while (currentNode != nullptr) {
        Customer* customer = currentNode->getData();
        if (customer->getUsername() == username) {
            return customer;
        }
        currentNode = currentNode->getNext();
    }
    return nullptr;
}

Admin* BankingSystemConsole::findAdminByUsername(const std::string& username)
{
    auto* currentNode = allAdmins.getHead();
    while (currentNode != nullptr) {
        Admin* admin = currentNode->getData();
        if (admin->getUsername() == username) {
            return admin;
        }
        currentNode = currentNode->getNext();
    }
    return nullptr;
}

Account* BankingSystemConsole::findAccountByCardNumber(const std::string& cardNumber)
{
    auto* currentNode = allAccounts.getHead();
    while (currentNode != nullptr) {
        Account* account = currentNode->getData();
        if (account->getCardNumber() == cardNumber) {
            return account;
        }
        currentNode = currentNode->getNext();
    }
    return nullptr;
}

std::string BankingSystemConsole::getCardHolderName(const std::string& cardNumber)
{
    auto* customerNode = allCustomers.getHead();
    while (customerNode != nullptr) {
        Customer* customer = customerNode->getData();
        Account* account = customer->findAccountByCardNumber(cardNumber);
        if (account) {
            return customer->getFirstName() + " " + customer->getLastName();
        }
        customerNode = customerNode->getNext();
    }
    return ""; 
}

void BankingSystemConsole::createSampleData()
{
    // Create sample admin
    Admin* sampleAdmin = new Admin("Admin", "User", "1234567890", 30, "admin", "admin123");
    allAdmins.add(sampleAdmin);
    
    // Create sample customers
    Customer* customer1 = new Customer("Ali", "Ahmadi", "0123456789", 25, "ali_ahmadi", "pass123");
    Customer* customer2 = new Customer("Sara", "Hosseini", "0987654321", 28, "sara_h", "pass456");
    
    allCustomers.add(customer1);
    allCustomers.add(customer2);
    
    // Create accounts for customer1
    DepositAccount* depositAcc = new DepositAccount("1234567812345678", "ACC001", "IR123456789", "1234", "5678", 0.15);
    depositAcc->deposit(1000000); // 1 million Toman
    
    CurrentAccount* currentAcc = new CurrentAccount("1234567887654321", "ACC002", "IR987654321", "4321", "8765", 500000);
    currentAcc->deposit(500000); // 500k Toman
    
    QarzAccount* loanAcc = new QarzAccount("1234567855556666", "ACC003", "IR555666777", "6666", "7777");
    loanAcc->requestLoan(2000000, 24); // 2 million loan for 24 months
    
    customer1->addAccount(depositAcc);
    customer1->addAccount(currentAcc);
    customer1->addAccount(loanAcc);
    
    allAccounts.add(depositAcc);
    allAccounts.add(currentAcc);
    allAccounts.add(loanAcc);
    
    // Create account for customer2
    DepositAccount* depositAcc2 = new DepositAccount("9876543212345678", "ACC004", "IR999888777", "9999", "8888", 0.12);
    depositAcc2->deposit(750000); // 750k Toman
    
    customer2->addAccount(depositAcc2);
    allAccounts.add(depositAcc2);
}
