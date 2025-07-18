# Banking Management System - Qt GUI Version
QT += core widgets

CONFIG += c++11

TARGET = BankingSystemGUI
TEMPLATE = app

# Source files
SOURCES += \
    main_qt.cpp \
    bankingsystem.cpp \
    loginwindow.cpp \
    customerwindow.cpp \
    adminwindow.cpp \
    accountdialog.cpp \
    transferdialog.cpp \
    Account.cpp \
    User.cpp \
    Customer.cpp \
    Admin.cpp \
    SavingsAccount.cpp \
    CurrentAccount.cpp \
    LoanAccount.cpp

# Header files
HEADERS += \
    bankingsystem.h \
    loginwindow.h \
    customerwindow.h \
    adminwindow.h \
    accountdialog.h \
    transferdialog.h \
    Account.h \
    User.h \
    Customer.h \
    Admin.h \
    SavingsAccount.h \
    CurrentAccount.h \
    LoanAccount.h \
    LinkedList.h

# UI files
FORMS += \
    loginwindow.ui \
    customerwindow.ui \
    adminwindow.ui \
    accountdialog.ui \
    transferdialog.ui
