#include "transferdialog.h"
#include <QApplication>

TransferDialog::TransferDialog(Customer* customer, QWidget *parent)
    : QDialog(parent), currentCustomer(customer)
{
    setupUI();
    populateFromAccounts();
    setModal(true);
    setFixedSize(450, 300);
    setWindowTitle("Card to Card Transfer");
}

void TransferDialog::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    // Form layout
    QGridLayout* formLayout = new QGridLayout();
    
    // From account
    formLayout->addWidget(new QLabel("From Account:"), 0, 0);
    fromAccountCombo = new QComboBox();
    formLayout->addWidget(fromAccountCombo, 0, 1);
    
    // To card number
    formLayout->addWidget(new QLabel("To Card Number:"), 1, 0);
    toCardEdit = new QLineEdit();
    toCardEdit->setPlaceholderText("Enter 16-digit card number");
    toCardEdit->setMaxLength(16);
    formLayout->addWidget(toCardEdit, 1, 1);
    
    // Amount
    formLayout->addWidget(new QLabel("Amount:"), 2, 0);
    amountEdit = new QLineEdit();
    amountEdit->setPlaceholderText("Enter amount in Toman");
    formLayout->addWidget(amountEdit, 2, 1);
    
    // Password
    formLayout->addWidget(new QLabel("Account Password:"), 3, 0);
    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("Enter account password");
    formLayout->addWidget(passwordEdit, 3, 1);
    
    mainLayout->addLayout(formLayout);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    transferBtn = new QPushButton("Transfer");
    cancelBtn = new QPushButton("Cancel");
    
    connect(transferBtn, &QPushButton::clicked, this, &TransferDialog::onTransferClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &TransferDialog::onCancelClicked);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(transferBtn);
    buttonLayout->addWidget(cancelBtn);
    
    mainLayout->addLayout(buttonLayout);
}

void TransferDialog::populateFromAccounts()
{
    fromAccountCombo->clear();
    
    auto* accountNode = currentCustomer->getAccounts().getHead();
    while (accountNode != nullptr) {
        Account* account = accountNode->getData();
        QString displayText = QString("Card: %1 - Balance: %2 Toman")
                             .arg(QString::fromStdString(account->getCardNumber()))
                             .arg(account->getBalance());
        fromAccountCombo->addItem(displayText, QVariant::fromValue(static_cast<void*>(account)));
        accountNode = accountNode->getNext();
    }
}

void TransferDialog::onTransferClicked()
{
    // Validate inputs
    if (fromAccountCombo->currentIndex() == -1) {
        QMessageBox::warning(this, "Error", "Please select a source account.");
        return;
    }
    
    QString toCardNumber = toCardEdit->text().trimmed();
    if (toCardNumber.length() != 16) {
        QMessageBox::warning(this, "Error", "Please enter a valid 16-digit card number.");
        return;
    }
    
    QString amountStr = amountEdit->text().trimmed();
    if (amountStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter an amount.");
        return;
    }
    
    bool ok;
    double amount = amountStr.toDouble(&ok);
    if (!ok || amount <= 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid amount.");
        return;
    }
    
    QString password = passwordEdit->text();
    if (password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter your account password.");
        return;
    }
    
    // Get selected account
    Account* fromAccount = static_cast<Account*>(fromAccountCombo->currentData().value<void*>());
    if (!fromAccount) {
        QMessageBox::critical(this, "Error", "Invalid account selection.");
        return;
    }
    
    try {
        // Perform transfer using Customer's method
        bool success = currentCustomer->performCardToCardTransfer(
            fromAccount->getCardNumber(),
            toCardNumber.toStdString(),
            amount,
            password.toStdString()
        );
        
        if (success) {
            QMessageBox::information(this, "Success", "Transfer completed successfully!");
            accept(); // Close dialog with success
        } else {
            QMessageBox::critical(this, "Error", "Transfer failed. Please check your inputs.");
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Transfer error: %1").arg(e.what()));
    }
}

void TransferDialog::onCancelClicked()
{
    reject(); // Close dialog without success
}
