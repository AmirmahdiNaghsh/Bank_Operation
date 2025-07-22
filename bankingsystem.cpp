#include "bankingsystem.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "LoanAccount.h"
#include <QString>
#include <QDebug>

BankingSystem* BankingSystem::instance = nullptr;

BankingSystem::BankingSystem(QObject *parent)
    : QObject(parent)
{
}

BankingSystem::~BankingSystem()
{
    // Clean up customers
    auto* customerNode = allCustomers.getHead();
    while (customerNode != nullptr) {
        delete customerNode->getData();
        customerNode = customerNode->getNext();
    }
    
    // Clean up admins
    auto* adminNode = allAdmins.getHead();
    while (adminNode != nullptr) {
        delete adminNode->getData();
        adminNode = adminNode->getNext();
    }
}

BankingSystem& BankingSystem::getInstance()
{
    if (instance == nullptr) {
        instance = new BankingSystem();
    }
    return *instance;
}

void BankingSystem::initializeSystem()
{
    qDebug() << "Starting createSampleData...";
    createSampleData();
    qDebug() << "createSampleData completed...";
}

Customer* BankingSystem::authenticateCustomer(const QString& username, const QString& password)
{
    return allCustomers.find([&](Customer* customer) {
        return customer->getUsername() == username.toStdString() && 
               customer->checkPassword(password.toStdString());
    });
}

Admin* BankingSystem::authenticateAdmin(const QString& username, const QString& password)
{
    return allAdmins.find([&](Admin* admin) {
        return admin->getUsername() == username.toStdString() && 
               admin->checkPassword(password.toStdString());
    });
}

bool BankingSystem::registerCustomer(const QString& firstName, const QString& lastName, 
                                    const QString& nationalId, int age, 
                                    const QString& username, const QString& password)
{
    // Check if username already exists
    if (findCustomerByUsername(username) != nullptr) {
        return false;
    }
    
    Customer* newCustomer = new Customer(firstName.toStdString(), lastName.toStdString(),
                                       nationalId.toStdString(), age,
                                       username.toStdString(), password.toStdString());
    allCustomers.add(newCustomer);
    return true;
}

Customer* BankingSystem::findCustomerByUsername(const QString& username)
{
    return allCustomers.find([&](Customer* customer) {
        return customer->getUsername() == username.toStdString();
    });
}

Admin* BankingSystem::findAdminByUsername(const QString& username)
{
    return allAdmins.find([&](Admin* admin) {
        return admin->getUsername() == username.toStdString();
    });
}

Account* BankingSystem::findAccountByCardNumber(const QString& cardNumber)
{
    return allAccounts.find([&](Account* account) {
        return account->getCardNumber() == cardNumber.toStdString();
    });
}

QString BankingSystem::getCardHolderName(const QString& cardNumber)
{
    // Find the customer who owns this card
    auto* customerNode = allCustomers.getHead();
    while (customerNode != nullptr) {
        Customer* customer = customerNode->getData();
        Account* account = customer->findAccountByCardNumber(cardNumber.toStdString());
        if (account) {
            return QString::fromStdString(customer->getFullName());
        }
        customerNode = customerNode->getNext();
    }
    return QString(); // Empty string if not found
}

void BankingSystem::createSampleData()
{
    qDebug() << "Creating sample admin...";
    // Create sample admin
    Admin* sampleAdmin = new Admin("Admin", "User", "1234567890", 30, "admin", "admin123");
    allAdmins.add(sampleAdmin);
    qDebug() << "Admin created and added...";
    
    qDebug() << "Creating sample customers...";
    // Create sample customers
    Customer* customer1 = new Customer("Ali", "Ahmadi", "0123456789", 25, "ali_ahmadi", "pass123");
    Customer* customer2 = new Customer("Sara", "Hosseini", "0987654321", 28, "sara_h", "pass456");
    
    allCustomers.add(customer1);
    allCustomers.add(customer2);
    
    // Create sample accounts for customer1
    DepositAccount* depositAcc = new DepositAccount("1234567812345678", "ACC001", "IR123456789", "1234", "5678", 0.15);
    depositAcc->deposit(1000000); // 1M Toman initial balance
    
    CurrentAccount* currentAcc = new CurrentAccount("1234567887654321", "ACC002", "IR987654321", "4321", "8765", 500000);
    currentAcc->deposit(500000); // 500K Toman initial balance
    
    QarzAccount* loanAcc = new QarzAccount("1234567855556666", "ACC003", "IR555666777", "6666", "7777");
    loanAcc->requestLoan(2000000, 24); // 2M Toman loan for 24 months
    
    customer1->addAccount(depositAcc);
    customer1->addAccount(currentAcc);
    customer1->addAccount(loanAcc);
    
    allAccounts.add(depositAcc);
    allAccounts.add(currentAcc);
    allAccounts.add(loanAcc);
    
    // Create sample account for customer2
    DepositAccount* depositAcc2 = new DepositAccount("9876543212345678", "ACC004", "IR999888777", "9999", "8888", 0.12);
    depositAcc2->deposit(750000); // 750K Toman initial balance
    
    customer2->addAccount(depositAcc2);
    allAccounts.add(depositAcc2);
}
