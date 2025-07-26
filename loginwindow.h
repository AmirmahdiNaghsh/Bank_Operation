#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "Customer.h"
#include "Admin.h"
#include "adminwindow.h"
#include "customerwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void onLoginClicked();
    void onRegisterClicked();

private:
    Ui::LoginWindow *ui;
    void showCustomerWindow(Customer* customer);
    void showAdminWindow(Admin* admin);
    void showRegisterDialog();
};

#endif // LOGINWINDOW_H
