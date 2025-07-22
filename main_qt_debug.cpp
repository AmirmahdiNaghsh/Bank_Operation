#include <QApplication>
#include <QDebug>
#include "loginwindow.h"
#include "bankingsystem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    qDebug() << "Application started...";
    
    app.setApplicationName("Banking Management System");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Bank of C++");
    
    qDebug() << "Application properties set...";
    
    // Initialize the banking system
    qDebug() << "Initializing banking system...";
    BankingSystem::getInstance().initializeSystem();
    qDebug() << "Banking system initialized...";
    
    // Show login window
    qDebug() << "Creating login window...";
    LoginWindow loginWindow;
    qDebug() << "Showing login window...";
    loginWindow.show();
    
    qDebug() << "Starting event loop...";
    return app.exec();
}
