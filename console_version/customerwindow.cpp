#include "customerwindow.h"
#include "ui_customerwindow.h"
#include "transferdialog.h"
#include "bankingsystem.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QTextStream>
#include <QDateTime>

CustomerWindow::CustomerWindow(Customer* customer, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CustomerWindow)
    , currentCustomer(customer)
{
    ui->setupUi(this);
    
    // Set window properties
    setFixedSize(1000, 700);
    
    // Update welcome label
    QString welcomeText = QString("Welcome, %1!").arg(QString::fromStdString(customer->getFullName()));
    ui->welcomeLabel->setText(welcomeText);
    
    // Connect signals and slots
    connect(ui->viewAccountsButton, &QPushButton::clicked, this, &CustomerWindow::onViewAccountsClicked);
    connect(ui->transferButton, &QPushButton::clicked, this, &CustomerWindow::onTransferClicked);
    connect(ui->changePasswordButton, &QPushButton::clicked, this, &CustomerWindow::onChangePasswordClicked);
    connect(ui->generateDynamicPasswordButton, &QPushButton::clicked, this, &CustomerWindow::onGenerateDynamicPasswordClicked);
    connect(ui->updateInfoButton, &QPushButton::clicked, this, &CustomerWindow::onUpdateInfoClicked);
    connect(ui->logoutButton, &QPushButton::clicked, this, &CustomerWindow::onLogoutClicked);
    connect(ui->accountsListWidget, &QListWidget::itemClicked, this, &CustomerWindow::onAccountSelected);
    
    // Load accounts on startup
    loadAccountsList();
}

CustomerWindow::~CustomerWindow()
{
    delete ui;
}

void CustomerWindow::onViewAccountsClicked()
{
    refreshAccountsList();
    ui->statusbar->showMessage("Accounts refreshed", 2000);
}

void CustomerWindow::onTransferClicked()
{
    if (currentCustomer->getAccountCount() == 0) {
        QMessageBox::warning(this, "No Accounts", "You don't have any accounts to transfer from.");
        return;
    }
    
    TransferDialog* transferDialog = new TransferDialog(currentCustomer, this);
    if (transferDialog->exec() == QDialog::Accepted) {
        refreshAccountsList();
        ui->statusbar->showMessage("Transfer completed successfully", 3000);
    }
    transferDialog->deleteLater();
}

void CustomerWindow::onChangePasswordClicked()
{
    if (currentCustomer->getAccountCount() == 0) {
        QMessageBox::warning(this, "No Accounts", "You don't have any accounts.");
        return;
    }
    
    // Get card number
    QStringList cardNumbers;
    auto* currentNode = currentCustomer->getAccounts().getHead();
    while (currentNode != nullptr) {
        Account* account = currentNode->getData();
        cardNumbers << QString::fromStdString(account->getCardNumber());
        currentNode = currentNode->getNext();
    }
    
    bool ok;
    QString cardNumber = QInputDialog::getItem(this, "Select Account", "Card Number:", cardNumbers, 0, false, &ok);
    if (!ok) return;
    
    QString passwordType = QInputDialog::getItem(this, "Password Type", "Select password type:", 
                                               QStringList() << "primary" << "second", 0, false, &ok);
    if (!ok) return;
    
    QString oldPassword = QInputDialog::getText(this, "Change Password", "Old Password:", 
                                              QLineEdit::Password, "", &ok);
    if (!ok) return;
    
    QString newPassword = QInputDialog::getText(this, "Change Password", "New Password:", 
                                              QLineEdit::Password, "", &ok);
    if (!ok) return;
    
    if (currentCustomer->changeAccountPassword(cardNumber.toStdString(), passwordType.toStdString(),
                                             oldPassword.toStdString(), newPassword.toStdString())) {
        QMessageBox::information(this, "Success", "Password changed successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to change password. Please check your old password.");
    }
}

void CustomerWindow::onGenerateDynamicPasswordClicked()
{
    if (currentCustomer->getAccountCount() == 0) {
        QMessageBox::warning(this, "No Accounts", "You don't have any accounts.");
        return;
    }
    
    // Get card number
    QStringList cardNumbers;
    auto* currentNode = currentCustomer->getAccounts().getHead();
    while (currentNode != nullptr) {
        Account* account = currentNode->getData();
        cardNumbers << QString::fromStdString(account->getCardNumber());
        currentNode = currentNode->getNext();
    }
    
    bool ok;
    QString cardNumber = QInputDialog::getItem(this, "Select Account", "Card Number:", cardNumbers, 0, false, &ok);
    if (!ok) return;
    
    QString dynamicPassword = QString::fromStdString(currentCustomer->generateDynamicPassword(cardNumber.toStdString()));
    if (!dynamicPassword.isEmpty()) {
        QMessageBox::information(this, "Dynamic Password Generated", 
                               QString("Your one-time dynamic password is:\n\n%1\n\nThis password is valid for one transaction only.")
                               .arg(dynamicPassword));
    }
}

void CustomerWindow::onUpdateInfoClicked()
{
    bool ok;
    QString newFirstName = QInputDialog::getText(this, "Update Info", "New First Name:", 
                                               QLineEdit::Normal, QString::fromStdString(currentCustomer->getFirstName()), &ok);
    if (!ok) return;
    
    QString newLastName = QInputDialog::getText(this, "Update Info", "New Last Name:", 
                                              QLineEdit::Normal, QString::fromStdString(currentCustomer->getLastName()), &ok);
    if (!ok) return;
    
    int newAge = QInputDialog::getInt(this, "Update Info", "New Age:", 
                                    currentCustomer->getAge(), 18, 100, 1, &ok);
    if (!ok) return;
    
    currentCustomer->changeInfo(newFirstName.toStdString(), newLastName.toStdString(), newAge);
    
    QString welcomeText = QString("Welcome, %1!").arg(QString::fromStdString(currentCustomer->getFullName()));
    ui->welcomeLabel->setText(welcomeText);
    
    QMessageBox::information(this, "Success", "Personal information updated successfully!");
}

void CustomerWindow::onLogoutClicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Logout", 
                                                            "Are you sure you want to logout?",
                                                            QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->close();
        parentWidget()->show(); // Show login window
    }
}

void CustomerWindow::onAccountSelected(QListWidgetItem* item)
{
    if (!item) return;
    
    QString cardNumber = item->data(Qt::UserRole).toString();
    Account* account = currentCustomer->findAccountByCardNumber(cardNumber.toStdString());
    
    if (account) {
        showAccountDetails(account);
    }
}

void CustomerWindow::loadAccountsList()
{
    ui->accountsListWidget->clear();
    
    auto* currentNode = currentCustomer->getAccounts().getHead();
    while (currentNode != nullptr) {
        Account* account = currentNode->getData();
        
        QString accountText = QString("💳 %1 - Balance: %2 Toman")
                             .arg(QString::fromStdString(account->getCardNumber()))
                             .arg(account->getBalance(), 0, 'f', 0);
        
        QListWidgetItem* item = new QListWidgetItem(accountText);
        item->setData(Qt::UserRole, QString::fromStdString(account->getCardNumber()));
        ui->accountsListWidget->addItem(item);
        
        currentNode = currentNode->getNext();
    }
    
    if (currentCustomer->getAccountCount() == 0) {
        QListWidgetItem* item = new QListWidgetItem("No accounts found. Contact admin to create accounts.");
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
        ui->accountsListWidget->addItem(item);
    }
}

void CustomerWindow::showAccountDetails(Account* account)
{
    QString details;
    QTextStream stream(&details);
    
    stream << "=== Account Information ===\n";
    stream << "Card Number: " << QString::fromStdString(account->getCardNumber()) << "\n";
    stream << "Account Number: " << QString::fromStdString(account->getAccountNumber()) << "\n";
    stream << "IBAN: " << QString::fromStdString(account->getIban()) << "\n";
    stream << "CVV2: " << QString::fromStdString(account->getCvv2()) << "\n";
    stream << "Balance: " << account->getBalance() << " Toman\n";
    
    // Show expiration date
    time_t expDate = account->getExpirationDate();
    QDateTime expDateTime = QDateTime::fromSecsSinceEpoch(expDate);
    stream << "Expiration Date: " << expDateTime.toString("MM/yyyy") << "\n";
    stream << "Status: " << (account->isExpired() ? "Expired" : "Active") << "\n\n";
    
    // Add account type specific information
    stream << "=== Account Type Details ===\n";
    // This would normally call displayAccountTypeDifference() but we need to capture the output
    // For now, we'll add basic type information
    stream << "Please check console output for detailed account type information.";
    
    ui->detailsLabel->setText(details);
    
    // Also print to console for complete information
    account->displayAccountTypeDifference();
}

void CustomerWindow::refreshAccountsList()
{
    loadAccountsList();
    ui->detailsLabel->setText("Select an account to view details");
}
