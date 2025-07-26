#ifndef CUSTOMERWINDOW_H
#define CUSTOMERWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "Customer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CustomerWindow; }
QT_END_NAMESPACE

class CustomerWindow : public QMainWindow
{
    Q_OBJECT

public:
    CustomerWindow(Customer* customer, QWidget *parent = nullptr);
    ~CustomerWindow();

private slots:
    void onViewAccountsClicked();
    void onTransferClicked();
    void onChangePasswordClicked();
    void onGenerateDynamicPasswordClicked();
    void onUpdateInfoClicked();
    void onLogoutClicked();
    void onAccountSelected(QListWidgetItem* item);

private:
    Ui::CustomerWindow *ui;
    Customer* currentCustomer;
    
    void loadAccountsList();
    void showAccountDetails(Account* account);
    void refreshAccountsList();
};

#endif // CUSTOMERWINDOW_H
