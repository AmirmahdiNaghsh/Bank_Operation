#ifndef TRANSFERDIALOG_H
#define TRANSFERDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "Customer.h"
#include "Account.h"
#include "BankSystem.h"

class TransferDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransferDialog(Customer* customer, QWidget *parent = nullptr);

private slots:
    void onTransferClicked();
    void onCancelClicked();

private:
    void setupUI();
    void populateFromAccounts(); // Will use BankingSystem's account list

    Customer* currentCustomer;

    QComboBox* fromAccountCombo;
    QLineEdit* toCardEdit;
    QLineEdit* amountEdit;
    QLineEdit* passwordEdit;
    QPushButton* transferBtn;
    QPushButton* cancelBtn;
};

#endif // TRANSFERDIALOG_H
