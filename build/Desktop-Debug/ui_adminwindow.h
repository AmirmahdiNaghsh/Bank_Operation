/********************************************************************************
** Form generated from reading UI file 'adminwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINWINDOW_H
#define UI_ADMINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *customerTab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *customerFormGroup;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *firstNameEdit;
    QLabel *label_2;
    QLineEdit *lastNameEdit;
    QLabel *label_3;
    QLineEdit *nationalIdEdit;
    QLabel *label_4;
    QLineEdit *usernameEdit;
    QLabel *label_5;
    QLineEdit *passwordEdit;
    QHBoxLayout *buttonLayout;
    QPushButton *addCustomerBtn;
    QPushButton *removeCustomerBtn;
    QPushButton *editCustomerBtn;
    QTableWidget *customersTable;
    QWidget *accountTab;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *accountFormGroup;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QComboBox *customerCombo;
    QLabel *label_7;
    QComboBox *accountTypeCombo;
    QLabel *label_8;
    QLineEdit *initialBalanceEdit;
    QPushButton *createAccountBtn;
    QTableWidget *accountsTable;
    QWidget *viewTab;
    QVBoxLayout *verticalLayout_4;
    QPushButton *refreshBtn;
    QTextEdit *dataDisplay;
    QPushButton *logoutBtn;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AdminWindow)
    {
        if (AdminWindow->objectName().isEmpty())
            AdminWindow->setObjectName("AdminWindow");
        AdminWindow->resize(800, 600);
        centralwidget = new QWidget(AdminWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        customerTab = new QWidget();
        customerTab->setObjectName("customerTab");
        verticalLayout_2 = new QVBoxLayout(customerTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        customerFormGroup = new QGroupBox(customerTab);
        customerFormGroup->setObjectName("customerFormGroup");
        gridLayout = new QGridLayout(customerFormGroup);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(customerFormGroup);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        firstNameEdit = new QLineEdit(customerFormGroup);
        firstNameEdit->setObjectName("firstNameEdit");

        gridLayout->addWidget(firstNameEdit, 0, 1, 1, 1);

        label_2 = new QLabel(customerFormGroup);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lastNameEdit = new QLineEdit(customerFormGroup);
        lastNameEdit->setObjectName("lastNameEdit");

        gridLayout->addWidget(lastNameEdit, 1, 1, 1, 1);

        label_3 = new QLabel(customerFormGroup);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        nationalIdEdit = new QLineEdit(customerFormGroup);
        nationalIdEdit->setObjectName("nationalIdEdit");

        gridLayout->addWidget(nationalIdEdit, 2, 1, 1, 1);

        label_4 = new QLabel(customerFormGroup);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        usernameEdit = new QLineEdit(customerFormGroup);
        usernameEdit->setObjectName("usernameEdit");

        gridLayout->addWidget(usernameEdit, 3, 1, 1, 1);

        label_5 = new QLabel(customerFormGroup);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        passwordEdit = new QLineEdit(customerFormGroup);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(passwordEdit, 4, 1, 1, 1);


        verticalLayout_2->addWidget(customerFormGroup);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        addCustomerBtn = new QPushButton(customerTab);
        addCustomerBtn->setObjectName("addCustomerBtn");

        buttonLayout->addWidget(addCustomerBtn);

        removeCustomerBtn = new QPushButton(customerTab);
        removeCustomerBtn->setObjectName("removeCustomerBtn");

        buttonLayout->addWidget(removeCustomerBtn);

        editCustomerBtn = new QPushButton(customerTab);
        editCustomerBtn->setObjectName("editCustomerBtn");

        buttonLayout->addWidget(editCustomerBtn);


        verticalLayout_2->addLayout(buttonLayout);

        customersTable = new QTableWidget(customerTab);
        customersTable->setObjectName("customersTable");

        verticalLayout_2->addWidget(customersTable);

        tabWidget->addTab(customerTab, QString());
        accountTab = new QWidget();
        accountTab->setObjectName("accountTab");
        verticalLayout_3 = new QVBoxLayout(accountTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        accountFormGroup = new QGroupBox(accountTab);
        accountFormGroup->setObjectName("accountFormGroup");
        gridLayout_2 = new QGridLayout(accountFormGroup);
        gridLayout_2->setObjectName("gridLayout_2");
        label_6 = new QLabel(accountFormGroup);
        label_6->setObjectName("label_6");

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        customerCombo = new QComboBox(accountFormGroup);
        customerCombo->setObjectName("customerCombo");

        gridLayout_2->addWidget(customerCombo, 0, 1, 1, 1);

        label_7 = new QLabel(accountFormGroup);
        label_7->setObjectName("label_7");

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        accountTypeCombo = new QComboBox(accountFormGroup);
        accountTypeCombo->setObjectName("accountTypeCombo");

        gridLayout_2->addWidget(accountTypeCombo, 1, 1, 1, 1);

        label_8 = new QLabel(accountFormGroup);
        label_8->setObjectName("label_8");

        gridLayout_2->addWidget(label_8, 2, 0, 1, 1);

        initialBalanceEdit = new QLineEdit(accountFormGroup);
        initialBalanceEdit->setObjectName("initialBalanceEdit");

        gridLayout_2->addWidget(initialBalanceEdit, 2, 1, 1, 1);

        createAccountBtn = new QPushButton(accountFormGroup);
        createAccountBtn->setObjectName("createAccountBtn");

        gridLayout_2->addWidget(createAccountBtn, 3, 0, 1, 2);


        verticalLayout_3->addWidget(accountFormGroup);

        accountsTable = new QTableWidget(accountTab);
        accountsTable->setObjectName("accountsTable");

        verticalLayout_3->addWidget(accountsTable);

        tabWidget->addTab(accountTab, QString());
        viewTab = new QWidget();
        viewTab->setObjectName("viewTab");
        verticalLayout_4 = new QVBoxLayout(viewTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        refreshBtn = new QPushButton(viewTab);
        refreshBtn->setObjectName("refreshBtn");

        verticalLayout_4->addWidget(refreshBtn);

        dataDisplay = new QTextEdit(viewTab);
        dataDisplay->setObjectName("dataDisplay");
        dataDisplay->setReadOnly(true);

        verticalLayout_4->addWidget(dataDisplay);

        tabWidget->addTab(viewTab, QString());

        verticalLayout->addWidget(tabWidget);

        logoutBtn = new QPushButton(centralwidget);
        logoutBtn->setObjectName("logoutBtn");

        verticalLayout->addWidget(logoutBtn);

        AdminWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(AdminWindow);
        statusbar->setObjectName("statusbar");
        AdminWindow->setStatusBar(statusbar);

        retranslateUi(AdminWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AdminWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AdminWindow)
    {
        AdminWindow->setWindowTitle(QCoreApplication::translate("AdminWindow", "Admin Panel", nullptr));
        customerFormGroup->setTitle(QCoreApplication::translate("AdminWindow", "Customer Information", nullptr));
        label->setText(QCoreApplication::translate("AdminWindow", "First Name:", nullptr));
        label_2->setText(QCoreApplication::translate("AdminWindow", "Last Name:", nullptr));
        label_3->setText(QCoreApplication::translate("AdminWindow", "National ID:", nullptr));
        label_4->setText(QCoreApplication::translate("AdminWindow", "Username:", nullptr));
        label_5->setText(QCoreApplication::translate("AdminWindow", "Password:", nullptr));
        addCustomerBtn->setText(QCoreApplication::translate("AdminWindow", "Add Customer", nullptr));
        removeCustomerBtn->setText(QCoreApplication::translate("AdminWindow", "Remove Customer", nullptr));
        editCustomerBtn->setText(QCoreApplication::translate("AdminWindow", "Edit Customer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(customerTab), QCoreApplication::translate("AdminWindow", "Customer Management", nullptr));
        accountFormGroup->setTitle(QCoreApplication::translate("AdminWindow", "Create Account", nullptr));
        label_6->setText(QCoreApplication::translate("AdminWindow", "Customer:", nullptr));
        label_7->setText(QCoreApplication::translate("AdminWindow", "Account Type:", nullptr));
        label_8->setText(QCoreApplication::translate("AdminWindow", "Initial Balance:", nullptr));
        createAccountBtn->setText(QCoreApplication::translate("AdminWindow", "Create Account", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(accountTab), QCoreApplication::translate("AdminWindow", "Account Management", nullptr));
        refreshBtn->setText(QCoreApplication::translate("AdminWindow", "Refresh Data", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(viewTab), QCoreApplication::translate("AdminWindow", "View Data", nullptr));
        logoutBtn->setText(QCoreApplication::translate("AdminWindow", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminWindow: public Ui_AdminWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINWINDOW_H
