#include <QApplication>
#include <QMessageBox>
#include "loginwindow.h"
#include "bankingsystem.h"

int main(int argc, char *argv[])
{
    // Set environment variables to handle TSM server issues
    qputenv("QT_MAC_DISABLE_FOREGROUND_APPLICATION_TRANSFORM", "1");
    
    QApplication app(argc, argv);
    
    // Set default system font
    QFont defaultFont("SF Pro Display", 12);  // Use SF Pro Display which is available on macOS
    app.setFont(defaultFont);
    
    app.setApplicationName("Banking Management System");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Bank of C++");
    
    // Initialize the banking system
    BankingSystem& bank = BankingSystem::getInstance();
    bank.initializeSystem(); // Make sure system is initialized
    
    // Create initial admin if none exists
    int adminCount = bank.getAllAdmins().getCount();
    qDebug() << "Current admin count:" << adminCount;
    
    if (adminCount == 0) {
        Admin* admin = new Admin("Admin", "User", "1234567890", 30, "admin", "admin123");
        bank.getAllAdmins().add(admin); // Make sure admin is added to the list
        QMessageBox::information(nullptr, "Admin Created", 
            "Initial admin account created.\nUsername: admin\nPassword: admin123");
        qDebug() << "New admin created with username: admin";
    }
    
    // Show login window
    LoginWindow loginWindow;
    loginWindow.show();
    
    return app.exec();
}
