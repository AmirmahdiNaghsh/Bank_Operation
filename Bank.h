#define BANK_H

#include "LinkedList.h"
#include <string>

class User;
class Customer;
class Admin;
class Account;

using namespace std;

class Bank {
private:
    LinkedList<User*> users; 
    User* currentUser;
    User* findUserByUsername(const string& username);
    Account* findAccountByCardNumber(const string& cardNumber);
    
public:
    Bank();
    ~Bank();
    void run();
private:
    void showMainMenu();
    void handleLogin();
    void handleLogout();
    void showAdminMenu(Admin* admin);
    void showCustomerMenu(Customer* customer);
    void performCardToCard(Customer* customer);
    void changeAccountPassword(Customer* customer);
    void viewCustomerAccounts(Customer* customer);
    void setupInitialData();
};
