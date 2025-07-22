#include "adminwindow.h"
#include <QApplication>

AdminWindow::AdminWindow(Admin* admin, BankingSystem* bankSystem, QWidget *parent)
    : QMainWindow(parent), currentAdmin(admin), bankingSystem(bankSystem), selectedCustomer(nullptr)
{
    setupUI();
    updateCustomerTable();
    setWindowTitle(QString("Admin Panel - %1").arg(QString::fromStdString(currentAdmin->getFirstName())));
    resize(800, 600);
}

AdminWindow::~AdminWindow()
{
    // Don't delete admin or bankingSystem as they're managed elsewhere
}

void AdminWindow::setupUI()
{
    // Create central widget and main layout
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    
    // Setup tab widget
    tabWidget = new QTabWidget(this);
    
    setupCustomerManagementTab();
    setupAccountManagementTab();
    setupViewDataTab();
    
    tabWidget->addTab(customerTab, "Customer Management");
    tabWidget->addTab(accountTab, "Account Management");
    tabWidget->addTab(viewTab, "View Data");
    
    mainLayout->addWidget(tabWidget);
    
    // Logout button
    QPushButton* logoutBtn = new QPushButton("Logout", this);
    connect(logoutBtn, &QPushButton::clicked, this, &AdminWindow::logout);
    mainLayout->addWidget(logoutBtn);
}

void AdminWindow::setupCustomerManagementTab()
{
    customerTab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(customerTab);
    
    // Customer form
    QGroupBox* formGroup = new QGroupBox("Customer Information");
    QGridLayout* formLayout = new QGridLayout(formGroup);
    
    formLayout->addWidget(new QLabel("First Name:"), 0, 0);
    firstNameEdit = new QLineEdit();
    formLayout->addWidget(firstNameEdit, 0, 1);
    
    formLayout->addWidget(new QLabel("Last Name:"), 1, 0);
    lastNameEdit = new QLineEdit();
    formLayout->addWidget(lastNameEdit, 1, 1);
    
    formLayout->addWidget(new QLabel("National ID:"), 2, 0);
    nationalIdEdit = new QLineEdit();
    formLayout->addWidget(nationalIdEdit, 2, 1);
    
    formLayout->addWidget(new QLabel("Username:"), 3, 0);
    usernameEdit = new QLineEdit();
    formLayout->addWidget(usernameEdit, 3, 1);
    
    formLayout->addWidget(new QLabel("Password:"), 4, 0);
    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    formLayout->addWidget(passwordEdit, 4, 1);
    
    layout->addWidget(formGroup);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    addCustomerBtn = new QPushButton("Add Customer");
    removeCustomerBtn = new QPushButton("Remove Customer");
    editCustomerBtn = new QPushButton("Edit Customer");
    
    connect(addCustomerBtn, &QPushButton::clicked, this, &AdminWindow::addCustomer);
    connect(removeCustomerBtn, &QPushButton::clicked, this, &AdminWindow::removeCustomer);
    connect(editCustomerBtn, &QPushButton::clicked, this, &AdminWindow::editCustomer);
    
    buttonLayout->addWidget(addCustomerBtn);
    buttonLayout->addWidget(removeCustomerBtn);
    buttonLayout->addWidget(editCustomerBtn);
    layout->addLayout(buttonLayout);
    
    // Customers table
    customersTable = new QTableWidget();
    customersTable->setColumnCount(4);
    QStringList headers = {"First Name", "Last Name", "National ID", "Username"};
    customersTable->setHorizontalHeaderLabels(headers);
    customersTable->horizontalHeader()->setStretchLastSection(true);
    customersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    
    connect(customersTable, &QTableWidget::itemSelectionChanged, 
            this, &AdminWindow::onCustomerSelectionChanged);
    
    layout->addWidget(customersTable);
}

void AdminWindow::setupAccountManagementTab()
{
    accountTab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(accountTab);
    
    // Account creation form
    QGroupBox* formGroup = new QGroupBox("Create Account");
    QGridLayout* formLayout = new QGridLayout(formGroup);
    
    formLayout->addWidget(new QLabel("Customer:"), 0, 0);
    customerCombo = new QComboBox();
    formLayout->addWidget(customerCombo, 0, 1);
    
    formLayout->addWidget(new QLabel("Account Type:"), 1, 0);
    accountTypeCombo = new QComboBox();
    accountTypeCombo->addItems({"Savings Account", "Current Account", "Loan Account"});
    formLayout->addWidget(accountTypeCombo, 1, 1);
    
    formLayout->addWidget(new QLabel("Initial Balance:"), 2, 0);
    initialBalanceEdit = new QLineEdit();
    formLayout->addWidget(initialBalanceEdit, 2, 1);
    
    createAccountBtn = new QPushButton("Create Account");
    connect(createAccountBtn, &QPushButton::clicked, this, &AdminWindow::createAccount);
    formLayout->addWidget(createAccountBtn, 3, 0, 1, 2);
    
    layout->addWidget(formGroup);
    
    // Accounts table
    accountsTable = new QTableWidget();
    accountsTable->setColumnCount(5);
    QStringList accountHeaders = {"Customer", "Account Type", "Card Number", "IBAN", "Balance"};
    accountsTable->setHorizontalHeaderLabels(accountHeaders);
    accountsTable->horizontalHeader()->setStretchLastSection(true);
    
    layout->addWidget(accountsTable);
}

void AdminWindow::setupViewDataTab()
{
    viewTab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(viewTab);
    
    refreshBtn = new QPushButton("Refresh Data");
    connect(refreshBtn, &QPushButton::clicked, this, &AdminWindow::viewAllCustomers);
    layout->addWidget(refreshBtn);
    
    dataDisplay = new QTextEdit();
    dataDisplay->setReadOnly(true);
    layout->addWidget(dataDisplay);
}

void AdminWindow::addCustomer()
{
    QString firstName = firstNameEdit->text().trimmed();
    QString lastName = lastNameEdit->text().trimmed();
    QString nationalId = nationalIdEdit->text().trimmed();
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();
    
    if (firstName.isEmpty() || lastName.isEmpty() || nationalId.isEmpty() || 
        username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill in all fields.");
        return;
    }
    
    try {
        // Convert QString to int for age (using default age for simplicity)
        int defaultAge = 25; // Default age
        if (currentAdmin->addCustomer(firstName.toStdString(), lastName.toStdString(),
                                    nationalId.toStdString(), defaultAge, username.toStdString(),
                                    password.toStdString())) {
            
            QMessageBox::information(this, "Success", "Customer added successfully!");
            
            // Clear form
            firstNameEdit->clear();
            lastNameEdit->clear();
            nationalIdEdit->clear();
            usernameEdit->clear();
            passwordEdit->clear();
            
            updateCustomerTable();
            refreshCustomerList();
        } else {
            QMessageBox::critical(this, "Error", "Failed to add customer. Username might already exist.");
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to add customer: %1").arg(e.what()));
    }
}

void AdminWindow::removeCustomer()
{
    if (!selectedCustomer) {
        QMessageBox::warning(this, "Error", "Please select a customer to remove.");
        return;
    }
    
    int ret = QMessageBox::question(this, "Confirm Deletion",
                                   QString("Are you sure you want to delete customer %1 %2?")
                                   .arg(QString::fromStdString(selectedCustomer->getFirstName()))
                                   .arg(QString::fromStdString(selectedCustomer->getLastName())),
                                   QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        try {
            if (currentAdmin->removeCustomer(selectedCustomer->getUsername())) {
                selectedCustomer = nullptr;
                updateCustomerTable();
                refreshCustomerList();
                QMessageBox::information(this, "Success", "Customer deleted successfully!");
            } else {
                QMessageBox::critical(this, "Error", "Failed to delete customer.");
            }
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Failed to delete customer: %1").arg(e.what()));
        }
    }
}

void AdminWindow::editCustomer()
{
    if (!selectedCustomer) {
        QMessageBox::warning(this, "Error", "Please select a customer to edit.");
        return;
    }
    
    // Populate form with current data
    firstNameEdit->setText(QString::fromStdString(selectedCustomer->getFirstName()));
    lastNameEdit->setText(QString::fromStdString(selectedCustomer->getLastName()));
    nationalIdEdit->setText(QString::fromStdString(selectedCustomer->getNationalId()));
    usernameEdit->setText(QString::fromStdString(selectedCustomer->getUsername()));
    
    QMessageBox::information(this, "Edit Mode", "Customer data loaded. Modify fields and click 'Add Customer' to update.");
}

void AdminWindow::createAccount()
{
    if (customerCombo->currentIndex() == -1) {
        QMessageBox::warning(this, "Error", "Please select a customer.");
        return;
    }
    
    QString customerUsername = customerCombo->currentData().toString();
    QString accountType = accountTypeCombo->currentText();
    QString initialBalanceStr = initialBalanceEdit->text().trimmed();
    
    if (initialBalanceStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter initial balance.");
        return;
    }
    
    bool ok;
    double initialBalance = initialBalanceStr.toDouble(&ok);
    if (!ok || initialBalance < 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid initial balance.");
        return;
    }
    
    try {
        // Find customer
        Customer* customer = currentAdmin->findCustomer(customerUsername.toStdString());
        if (!customer) {
            QMessageBox::critical(this, "Error", "Customer not found.");
            return;
        }
        
        // Create account based on type
        std::string type;
        if (accountType == "Savings Account") type = "DepositAccount";
        else if (accountType == "Current Account") type = "CurrentAccount";
        else if (accountType == "Loan Account") type = "QarzAccount";
        
        // Generate required account details
        std::string cardNum = "1234567812345678"; // Generate random
        std::string accNum = "AC" + std::to_string(rand() % 1000000);
        std::string iban = "IR" + std::to_string(rand() % 1000000000);
        std::string primaryPass = "1234";
        std::string secondPass = "5678";
        
        if (currentAdmin->createAccount(customer->getUsername(), type, cardNum, 
                                      accNum, iban, primaryPass, secondPass)) {
            QMessageBox::information(this, "Success", "Account created successfully!");
            initialBalanceEdit->clear();
            updateAccountsTable();
        } else {
            QMessageBox::critical(this, "Error", "Failed to create account.");
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to create account: %1").arg(e.what()));
    }
}

void AdminWindow::viewAllCustomers()
{
    dataDisplay->clear();
    dataDisplay->append("=== ALL CUSTOMERS ===\n");
    
    auto* node = bankingSystem->getAllCustomers().getHead();
    int count = 1;
    
    while (node != nullptr) {
        Customer* customer = node->getData();
        dataDisplay->append(QString("Customer %1:").arg(count++));
        dataDisplay->append(QString("  Name: %1 %2")
                           .arg(QString::fromStdString(customer->getFirstName()))
                           .arg(QString::fromStdString(customer->getLastName())));
        dataDisplay->append(QString("  National ID: %1").arg(QString::fromStdString(customer->getNationalId())));
        dataDisplay->append(QString("  Username: %1").arg(QString::fromStdString(customer->getUsername())));
        dataDisplay->append(QString("  Number of Accounts: %1").arg(customer->getAccounts().getCount()));
        dataDisplay->append("");
        
        node = node->getNext();
    }
}

void AdminWindow::refreshCustomerList()
{
    customerCombo->clear();
    auto* node = bankingSystem->getAllCustomers().getHead();
    
    while (node != nullptr) {
        Customer* customer = node->getData();
        QString displayName = QString("%1 %2 (%3)")
                             .arg(QString::fromStdString(customer->getFirstName()))
                             .arg(QString::fromStdString(customer->getLastName()))
                             .arg(QString::fromStdString(customer->getUsername()));
        customerCombo->addItem(displayName, QString::fromStdString(customer->getUsername()));
        node = node->getNext();
    }
}

void AdminWindow::updateCustomerTable()
{
    customersTable->setRowCount(0);
    
    auto* node = bankingSystem->getAllCustomers().getHead();
    int row = 0;
    
    while (node != nullptr) {
        Customer* customer = node->getData();
        customersTable->insertRow(row);
        
        customersTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(customer->getFirstName())));
        customersTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(customer->getLastName())));
        customersTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(customer->getNationalId())));
        customersTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(customer->getUsername())));
        
        // Store customer pointer in the first item
        customersTable->item(row, 0)->setData(Qt::UserRole, QVariant::fromValue(static_cast<void*>(customer)));
        
        row++;
        node = node->getNext();
    }
    
    refreshCustomerList();
}

void AdminWindow::updateAccountsTable()
{
    accountsTable->setRowCount(0);
    
    auto* customerNode = bankingSystem->getAllCustomers().getHead();
    int row = 0;
    
    while (customerNode != nullptr) {
        Customer* customer = customerNode->getData();
        auto* accountNode = customer->getAccounts().getHead();
        
        while (accountNode != nullptr) {
            Account* account = accountNode->getData();
            accountsTable->insertRow(row);
            
            QString customerName = QString("%1 %2")
                                 .arg(QString::fromStdString(customer->getFirstName()))
                                 .arg(QString::fromStdString(customer->getLastName()));
            
            accountsTable->setItem(row, 0, new QTableWidgetItem(customerName));
            accountsTable->setItem(row, 1, new QTableWidgetItem("Account")); // Account type would need RTTI
            accountsTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(account->getCardNumber())));
            accountsTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(account->getIban())));
            accountsTable->setItem(row, 4, new QTableWidgetItem(QString::number(account->getBalance(), 'f', 2)));
            
            row++;
            accountNode = accountNode->getNext();
        }
        
        customerNode = customerNode->getNext();
    }
}

void AdminWindow::onCustomerSelectionChanged()
{
    int currentRow = customersTable->currentRow();
    if (currentRow >= 0) {
        QTableWidgetItem* item = customersTable->item(currentRow, 0);
        if (item) {
            selectedCustomer = static_cast<Customer*>(item->data(Qt::UserRole).value<void*>());
        }
    } else {
        selectedCustomer = nullptr;
    }
}

void AdminWindow::logout()
{
    close();
}
