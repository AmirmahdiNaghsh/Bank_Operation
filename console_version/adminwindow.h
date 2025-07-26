#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QGroupBox>
#include <QTabWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>
#include "Admin.h"
#include "bankingsystem.h"

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    AdminWindow(Admin* admin, BankingSystem* bankSystem, QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void addCustomer();
    void removeCustomer();
    void editCustomer();
    void createAccount();
    void viewAllCustomers();
    void refreshCustomerList();
    void onCustomerSelectionChanged();
    void logout();

private:
    void setupUI();
    void setupCustomerManagementTab();
    void setupAccountManagementTab();
    void setupViewDataTab();
    void updateCustomerTable();
    void updateAccountsTable();
    
    Admin* currentAdmin;
    BankingSystem* bankingSystem;
    
    // UI components
    QTabWidget* tabWidget;
    
    // Customer Management Tab
    QWidget* customerTab;
    QLineEdit* firstNameEdit;
    QLineEdit* lastNameEdit;
    QLineEdit* nationalIdEdit;
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QPushButton* addCustomerBtn;
    QPushButton* removeCustomerBtn;
    QPushButton* editCustomerBtn;
    QTableWidget* customersTable;
    
    // Account Management Tab
    QWidget* accountTab;
    QComboBox* customerCombo;
    QComboBox* accountTypeCombo;
    QLineEdit* initialBalanceEdit;
    QPushButton* createAccountBtn;
    QTableWidget* accountsTable;
    
    // View Data Tab
    QWidget* viewTab;
    QTextEdit* dataDisplay;
    QPushButton* refreshBtn;
    
    // Selected customer for operations
    Customer* selectedCustomer;
};

#endif // ADMINWINDOW_H
