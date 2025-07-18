#include <QApplication>
#include "loginwindow.h"
#include "bankingsystem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("Banking Management System");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Bank of C++");
    
    // Initialize the banking system
    BankingSystem::getInstance().initializeSystem();
    
    // Show login window
    LoginWindow loginWindow;
    loginWindow.show();
    
    return app.exec();
}
