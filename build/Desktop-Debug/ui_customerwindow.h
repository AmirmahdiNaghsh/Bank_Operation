/********************************************************************************
** Form generated from reading UI file 'customerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMERWINDOW_H
#define UI_CUSTOMERWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomerWindow
{
public:
    QAction *actionView_Accounts;
    QAction *actionTransfer;
    QAction *actionChange_Password;
    QAction *actionUpdate_Info;
    QAction *actionLogout;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *leftLayout;
    QLabel *welcomeLabel;
    QGroupBox *actionsGroupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *viewAccountsButton;
    QPushButton *transferButton;
    QPushButton *changePasswordButton;
    QPushButton *generateDynamicPasswordButton;
    QPushButton *updateInfoButton;
    QSpacerItem *verticalSpacer;
    QPushButton *logoutButton;
    QVBoxLayout *rightLayout;
    QGroupBox *accountsGroupBox;
    QVBoxLayout *verticalLayout_2;
    QListWidget *accountsListWidget;
    QGroupBox *detailsGroupBox;
    QVBoxLayout *verticalLayout_3;
    QLabel *detailsLabel;
    QMenuBar *menubar;
    QMenu *menuAccount;
    QMenu *menuSettings;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CustomerWindow)
    {
        if (CustomerWindow->objectName().isEmpty())
            CustomerWindow->setObjectName("CustomerWindow");
        CustomerWindow->resize(1000, 700);
        actionView_Accounts = new QAction(CustomerWindow);
        actionView_Accounts->setObjectName("actionView_Accounts");
        actionTransfer = new QAction(CustomerWindow);
        actionTransfer->setObjectName("actionTransfer");
        actionChange_Password = new QAction(CustomerWindow);
        actionChange_Password->setObjectName("actionChange_Password");
        actionUpdate_Info = new QAction(CustomerWindow);
        actionUpdate_Info->setObjectName("actionUpdate_Info");
        actionLogout = new QAction(CustomerWindow);
        actionLogout->setObjectName("actionLogout");
        centralwidget = new QWidget(CustomerWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        leftLayout = new QVBoxLayout();
        leftLayout->setSpacing(10);
        leftLayout->setObjectName("leftLayout");
        welcomeLabel = new QLabel(centralwidget);
        welcomeLabel->setObjectName("welcomeLabel");

        leftLayout->addWidget(welcomeLabel);

        actionsGroupBox = new QGroupBox(centralwidget);
        actionsGroupBox->setObjectName("actionsGroupBox");
        verticalLayout = new QVBoxLayout(actionsGroupBox);
        verticalLayout->setObjectName("verticalLayout");
        viewAccountsButton = new QPushButton(actionsGroupBox);
        viewAccountsButton->setObjectName("viewAccountsButton");

        verticalLayout->addWidget(viewAccountsButton);

        transferButton = new QPushButton(actionsGroupBox);
        transferButton->setObjectName("transferButton");

        verticalLayout->addWidget(transferButton);

        changePasswordButton = new QPushButton(actionsGroupBox);
        changePasswordButton->setObjectName("changePasswordButton");

        verticalLayout->addWidget(changePasswordButton);

        generateDynamicPasswordButton = new QPushButton(actionsGroupBox);
        generateDynamicPasswordButton->setObjectName("generateDynamicPasswordButton");

        verticalLayout->addWidget(generateDynamicPasswordButton);

        updateInfoButton = new QPushButton(actionsGroupBox);
        updateInfoButton->setObjectName("updateInfoButton");

        verticalLayout->addWidget(updateInfoButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        logoutButton = new QPushButton(actionsGroupBox);
        logoutButton->setObjectName("logoutButton");

        verticalLayout->addWidget(logoutButton);


        leftLayout->addWidget(actionsGroupBox);


        horizontalLayout_3->addLayout(leftLayout);

        rightLayout = new QVBoxLayout();
        rightLayout->setObjectName("rightLayout");
        accountsGroupBox = new QGroupBox(centralwidget);
        accountsGroupBox->setObjectName("accountsGroupBox");
        verticalLayout_2 = new QVBoxLayout(accountsGroupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        accountsListWidget = new QListWidget(accountsGroupBox);
        accountsListWidget->setObjectName("accountsListWidget");
        accountsListWidget->setAlternatingRowColors(true);

        verticalLayout_2->addWidget(accountsListWidget);


        rightLayout->addWidget(accountsGroupBox);

        detailsGroupBox = new QGroupBox(centralwidget);
        detailsGroupBox->setObjectName("detailsGroupBox");
        verticalLayout_3 = new QVBoxLayout(detailsGroupBox);
        verticalLayout_3->setObjectName("verticalLayout_3");
        detailsLabel = new QLabel(detailsGroupBox);
        detailsLabel->setObjectName("detailsLabel");
        detailsLabel->setAlignment(Qt::AlignTop);
        detailsLabel->setWordWrap(true);

        verticalLayout_3->addWidget(detailsLabel);


        rightLayout->addWidget(detailsGroupBox);


        horizontalLayout_3->addLayout(rightLayout);

        CustomerWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CustomerWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 22));
        menuAccount = new QMenu(menubar);
        menuAccount->setObjectName("menuAccount");
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName("menuSettings");
        CustomerWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CustomerWindow);
        statusbar->setObjectName("statusbar");
        CustomerWindow->setStatusBar(statusbar);

        menubar->addAction(menuAccount->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menuAccount->addAction(actionView_Accounts);
        menuAccount->addAction(actionTransfer);
        menuAccount->addSeparator();
        menuAccount->addAction(actionLogout);
        menuSettings->addAction(actionChange_Password);
        menuSettings->addAction(actionUpdate_Info);

        retranslateUi(CustomerWindow);

        QMetaObject::connectSlotsByName(CustomerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CustomerWindow)
    {
        CustomerWindow->setWindowTitle(QCoreApplication::translate("CustomerWindow", "Banking System - Customer Dashboard", nullptr));
        CustomerWindow->setStyleSheet(QCoreApplication::translate("CustomerWindow", "QMainWindow {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                               stop: 0 #f8f9fa, stop: 1 #e9ecef);\n"
"}\n"
"\n"
"QPushButton {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                               stop: 0 #007bff, stop: 1 #0056b3);\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"    padding: 10px 20px;\n"
"    min-width: 120px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                               stop: 0 #0099ff, stop: 1 #007bff);\n"
"}\n"
"\n"
"QListWidget {\n"
"    background: white;\n"
"    border: 1px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    font-size: 14px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QListWidget::item {\n"
"    padding: 10px;\n"
"    border-bottom: 1px solid #f1f3f4;\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    background: #e3f2fd;\n"
"    color: #1976d2;\n"
""
                        "}\n"
"\n"
"QLabel {\n"
"    color: #495057;\n"
"    font-size: 16px;\n"
"}\n"
"\n"
"QGroupBox {\n"
"    font-weight: bold;\n"
"    font-size: 16px;\n"
"    color: #343a40;\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding-top: 10px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 5px 0 5px;\n"
"}", nullptr));
        actionView_Accounts->setText(QCoreApplication::translate("CustomerWindow", "View Accounts", nullptr));
        actionTransfer->setText(QCoreApplication::translate("CustomerWindow", "Transfer Money", nullptr));
        actionChange_Password->setText(QCoreApplication::translate("CustomerWindow", "Change Password", nullptr));
        actionUpdate_Info->setText(QCoreApplication::translate("CustomerWindow", "Update Personal Info", nullptr));
        actionLogout->setText(QCoreApplication::translate("CustomerWindow", "Logout", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("CustomerWindow", "Welcome, Customer!", nullptr));
        welcomeLabel->setStyleSheet(QCoreApplication::translate("CustomerWindow", "QLabel {\n"
"    font-size: 20px;\n"
"    font-weight: bold;\n"
"    color: #007bff;\n"
"    margin-bottom: 10px;\n"
"}", nullptr));
        actionsGroupBox->setTitle(QCoreApplication::translate("CustomerWindow", "Account Actions", nullptr));
        viewAccountsButton->setText(QCoreApplication::translate("CustomerWindow", "\360\237\223\213 View All Accounts", nullptr));
        transferButton->setText(QCoreApplication::translate("CustomerWindow", "\360\237\222\270 Card to Card Transfer", nullptr));
        changePasswordButton->setText(QCoreApplication::translate("CustomerWindow", "\360\237\224\221 Change Password", nullptr));
        generateDynamicPasswordButton->setText(QCoreApplication::translate("CustomerWindow", "\360\237\216\262 Generate Dynamic Password", nullptr));
        updateInfoButton->setText(QCoreApplication::translate("CustomerWindow", "\342\234\217\357\270\217 Update Personal Info", nullptr));
        logoutButton->setText(QCoreApplication::translate("CustomerWindow", "\360\237\232\252 Logout", nullptr));
        logoutButton->setStyleSheet(QCoreApplication::translate("CustomerWindow", "QPushButton {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                               stop: 0 #dc3545, stop: 1 #c82333);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                               stop: 0 #e45563, stop: 1 #dc3545);\n"
"}", nullptr));
        accountsGroupBox->setTitle(QCoreApplication::translate("CustomerWindow", "Your Bank Accounts", nullptr));
        detailsGroupBox->setTitle(QCoreApplication::translate("CustomerWindow", "Account Details", nullptr));
        detailsLabel->setText(QCoreApplication::translate("CustomerWindow", "Select an account to view details", nullptr));
        detailsLabel->setStyleSheet(QCoreApplication::translate("CustomerWindow", "QLabel {\n"
"    background: #f8f9fa;\n"
"    border: 1px solid #dee2e6;\n"
"    border-radius: 4px;\n"
"    padding: 15px;\n"
"    font-family: 'Courier New', monospace;\n"
"    font-size: 12px;\n"
"}", nullptr));
        menuAccount->setTitle(QCoreApplication::translate("CustomerWindow", "Account", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("CustomerWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomerWindow: public Ui_CustomerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMERWINDOW_H
