/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QFrame *loginFrame;
    QVBoxLayout *verticalLayout_3;
    QLabel *titleLabel;
    QVBoxLayout *verticalLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QVBoxLayout *verticalLayout_2;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QLabel *statusLabel;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(600, 500);
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        loginFrame = new QFrame(centralwidget);
        loginFrame->setObjectName("loginFrame");
        loginFrame->setFrameShape(QFrame::StyledPanel);
        verticalLayout_3 = new QVBoxLayout(loginFrame);
        verticalLayout_3->setSpacing(20);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(40, 40, 40, 40);
        titleLabel = new QLabel(loginFrame);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(titleLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        usernameLabel = new QLabel(loginFrame);
        usernameLabel->setObjectName("usernameLabel");

        verticalLayout->addWidget(usernameLabel);

        usernameLineEdit = new QLineEdit(loginFrame);
        usernameLineEdit->setObjectName("usernameLineEdit");

        verticalLayout->addWidget(usernameLineEdit);


        verticalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(15);
        verticalLayout_2->setObjectName("verticalLayout_2");
        passwordLabel = new QLabel(loginFrame);
        passwordLabel->setObjectName("passwordLabel");

        verticalLayout_2->addWidget(passwordLabel);

        passwordLineEdit = new QLineEdit(loginFrame);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(passwordLineEdit);


        verticalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        loginButton = new QPushButton(loginFrame);
        loginButton->setObjectName("loginButton");

        horizontalLayout->addWidget(loginButton);

        registerButton = new QPushButton(loginFrame);
        registerButton->setObjectName("registerButton");

        horizontalLayout->addWidget(registerButton);


        verticalLayout_3->addLayout(horizontalLayout);

        statusLabel = new QLabel(loginFrame);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignCenter);
        statusLabel->setWordWrap(true);

        verticalLayout_3->addWidget(statusLabel);


        horizontalLayout_3->addWidget(loginFrame);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        LoginWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 600, 22));
        LoginWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(LoginWindow);
        statusbar->setObjectName("statusbar");
        LoginWindow->setStatusBar(statusbar);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Banking Management System - Login", nullptr));
        LoginWindow->setStyleSheet(QCoreApplication::translate("LoginWindow", "QMainWindow {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                               stop: 0 #2c3e50, stop: 1 #34495e);\n"
"}\n"
"\n"
"QWidget {\n"
"    color: white;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                               stop: 0 #3498db, stop: 1 #2980b9);\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"    padding: 12px;\n"
"    min-width: 120px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                               stop: 0 #5dade2, stop: 1 #3498db);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                               stop: 0 #2980b9, stop: 1 #21618c);\n"
"}\n"
"\n"
"QLineEdit {\n"
"    background: rgba(255, 255, 255, 0.9);\n"
"    border: 2px solid #bd"
                        "c3c7;\n"
"    border-radius: 8px;\n"
"    color: #2c3e50;\n"
"    font-size: 14px;\n"
"    padding: 12px;\n"
"    min-height: 20px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #3498db;\n"
"    background: white;\n"
"}\n"
"\n"
"QLabel {\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    color: #ecf0f1;\n"
"}", nullptr));
        loginFrame->setStyleSheet(QCoreApplication::translate("LoginWindow", "QFrame {\n"
"    background: rgba(255, 255, 255, 0.1);\n"
"    border-radius: 20px;\n"
"    border: 2px solid rgba(255, 255, 255, 0.2);\n"
"}", nullptr));
        titleLabel->setText(QCoreApplication::translate("LoginWindow", "\360\237\217\246 Banking Management System", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("LoginWindow", "QLabel {\n"
"    font-size: 24px;\n"
"    font-weight: bold;\n"
"    color: #ecf0f1;\n"
"    margin-bottom: 20px;\n"
"}", nullptr));
        usernameLabel->setText(QCoreApplication::translate("LoginWindow", "Username:", nullptr));
        usernameLineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Enter your username", nullptr));
        passwordLabel->setText(QCoreApplication::translate("LoginWindow", "Password:", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Enter your password", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginWindow", "Register", nullptr));
        registerButton->setStyleSheet(QCoreApplication::translate("LoginWindow", "QPushButton {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                               stop: 0 #27ae60, stop: 1 #229954);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                               stop: 0 #58d68d, stop: 1 #27ae60);\n"
"}", nullptr));
        statusLabel->setText(QCoreApplication::translate("LoginWindow", "Welcome! Please login or register as a new customer.", nullptr));
        statusLabel->setStyleSheet(QCoreApplication::translate("LoginWindow", "QLabel {\n"
"    color: #bdc3c7;\n"
"    font-size: 12px;\n"
"    font-weight: normal;\n"
"}", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
