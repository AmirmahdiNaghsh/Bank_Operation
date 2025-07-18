#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "customerwindow.h"
#include "adminwindow.h"
#include "bankingsystem.h"
#include <QInputDialog>
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    
    // Set window properties
    setFixedSize(600, 500);
    setWindowIcon(QIcon(":/icons/bank.png")); // You can add an icon later
    
    // Connect signals and slots
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(ui->registerButton, &QPushButton::clicked, this, &LoginWindow::onRegisterClicked);
    
    // Set focus to username field
    ui->usernameLineEdit->setFocus();
    
    // Add sample credentials info
    ui->statusLabel->setText(
        "Sample Accounts:\n"
        "Admin: admin/admin123\n"
        "Customer: ali_ahmadi/pass123"
    );
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::onLoginClicked()
{
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter both username and password.");
        return;
    }
    
    // Try to authenticate as admin first
    Admin* admin = BankingSystem::getInstance().authenticateAdmin(username, password);
    if (admin) {
        ui->statusLabel->setText("Admin login successful!");
        showAdminWindow(admin);
        return;
    }
    
    // Try to authenticate as customer
    Customer* customer = BankingSystem::getInstance().authenticateCustomer(username, password);
    if (customer) {
        ui->statusLabel->setText("Customer login successful!");
        showCustomerWindow(customer);
        return;
    }
    
    // Login failed
    QMessageBox::critical(this, "Login Failed", "Invalid username or password.");
    ui->statusLabel->setText("Login failed. Please check your credentials.");
    ui->passwordLineEdit->clear();
    ui->passwordLineEdit->setFocus();
}

void LoginWindow::onRegisterClicked()
{
    showRegisterDialog();
}

void LoginWindow::showCustomerWindow(Customer* customer)
{
    CustomerWindow* customerWindow = new CustomerWindow(customer, this);
    customerWindow->show();
    this->hide();
}

void LoginWindow::showAdminWindow(Admin* admin)
{
    AdminWindow* adminWindow = new AdminWindow(admin, this);
    adminWindow->show();
    this->hide();
}

void LoginWindow::showRegisterDialog()
{
    bool ok;
    QString firstName = QInputDialog::getText(this, "Register Customer", 
                                            "First Name:", QLineEdit::Normal, "", &ok);
    if (!ok || firstName.isEmpty()) return;
    
    QString lastName = QInputDialog::getText(this, "Register Customer", 
                                           "Last Name:", QLineEdit::Normal, "", &ok);
    if (!ok || lastName.isEmpty()) return;
    
    QString nationalId = QInputDialog::getText(this, "Register Customer", 
                                             "National ID:", QLineEdit::Normal, "", &ok);
    if (!ok || nationalId.isEmpty()) return;
    
    int age = QInputDialog::getInt(this, "Register Customer", 
                                  "Age:", 25, 18, 100, 1, &ok);
    if (!ok) return;
    
    QString username = QInputDialog::getText(this, "Register Customer", 
                                           "Username:", QLineEdit::Normal, "", &ok);
    if (!ok || username.isEmpty()) return;
    
    QString password = QInputDialog::getText(this, "Register Customer", 
                                           "Password:", QLineEdit::Password, "", &ok);
    if (!ok || password.isEmpty()) return;
    
    // Register the customer
    if (BankingSystem::getInstance().registerCustomer(firstName, lastName, nationalId, age, username, password)) {
        QMessageBox::information(this, "Registration Successful", 
                               "Customer registered successfully! You can now login.");
        ui->usernameLineEdit->setText(username);
        ui->passwordLineEdit->clear();
        ui->statusLabel->setText("Registration successful! Please login.");
    } else {
        QMessageBox::critical(this, "Registration Failed", 
                            "Username already exists. Please choose a different username.");
    }
}
