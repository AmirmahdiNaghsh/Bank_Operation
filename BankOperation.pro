QT += core gui widgets

CONFIG += c++11

TARGET = BankOperation
TEMPLATE = app

# For better debugging
CONFIG += debug

# Print the PWD for debugging
message("Current directory: $$PWD")
message("UI files location:")
message("  adminwindow.ui: $$PWD/adminwindow.ui")
message("  customerwindow.ui: $$PWD/customerwindow.ui")
message("  loginwindow.ui: $$PWD/loginwindow.ui")
message("  transferdialog.ui: $$PWD/transferdialog.ui")

# Include the configuration file
include(config.pri)

SOURCES += \
    main_qt.cpp \
    adminwindow.cpp \
    customerwindow.cpp \
    loginwindow.cpp \
    Account.cpp \
    Admin.cpp \
    bankingsystem.cpp \
    Customer.cpp \
    DepositAccount.cpp \
    CurrentAccount.cpp \
    LoanAccount.cpp \
    User.cpp \
    transferdialog.cpp

HEADERS += \
    adminwindow.h \
    customerwindow.h \
    loginwindow.h \
    Account.h \
    Admin.h \
    bankingsystem.h \
    Customer.h \
    DepositAccount.h \
    CurrentAccount.h \
    LoanAccount.h \
    User.h \
    LinkedList.h \
    transferdialog.h

FORMS += \
    $$PWD/adminwindow.ui \
    $$PWD/customerwindow.ui \
    $$PWD/loginwindow.ui \
    $$PWD/transferdialog.ui
