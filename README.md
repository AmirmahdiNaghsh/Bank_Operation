# Banking Management System

A comprehensive C++ Banking Management System with console interface (Qt GUI to be added).

## 🎯 Project Overview

This project implements a complete banking system with object-oriented design principles, featuring:

- **Inheritance-based User System**: Base `User` class with derived `Customer` and `Admin` classes
- **Polymorphic Account Types**: Base `Account` class with three specialized account types
- **Custom Data Structures**: Template-based `LinkedList` implementation (no STL allowed)
- **Advanced Banking Features**: Transfer limits, dynamic passwords, interest calculations
- **Memory-only Storage**: All data stored in memory as per requirements

## 🏗 Class Architecture

### Core Classes

#### 1. User Hierarchy
```
User (abstract base class)
├── Customer (can hold up to 5 accounts)
└── Admin (full system management access)
```

#### 2. Account Hierarchy
```
Account (abstract base class)
├── DepositAccount (Sepordeh) - Interest-bearing savings
├── CurrentAccount (Jari) - Overdraft facility + checkbook
└── QarzAccount (Gharz-ol-hasaneh) - Interest-free loan account
```

#### 3. Data Structure
- `LinkedList<T>` - Custom template-based linked list implementation

## 🔧 Features Implemented

### ✅ Account Features
- **Unique identifiers**: Card number, account number, IBAN, CVV2
- **Security**: Primary password, static second password, dynamic second password
- **Transfer system**: Card-to-card transfers with limits and fees
- **Expiration management**: Card expiry date validation
- **Balance tracking**: Real-time balance updates

### ✅ Transfer System
- **Fee calculation**: 0.01% transfer fee
- **Daily limits**: Maximum 10,000,000 Toman per day
- **Transaction limits**: Maximum 3,000,000 Toman per transaction
- **Password requirements**:
  - ≤ 100,000 Toman: Static second password
  - > 100,000 Toman: Dynamic second password (one-time use)

### ✅ Account Type Specializations

#### DepositAccount (Sepordeh)
- Annual interest rate (default 15%)
- Monthly interest calculation and application
- Minimum balance requirements

#### CurrentAccount (Jari)
- Overdraft facility (default 500,000 Toman)
- Checkbook issuance
- Enhanced withdrawal capabilities

#### QarzAccount (Gharz-ol-hasaneh)
- Interest-free Islamic banking compliant
- Installment-based loan repayment
- Loan tracking and management

### ✅ User Capabilities

#### Customer Features
- View all accounts or specific account details
- Change primary and second passwords
- Perform card-to-card transfers
- Generate dynamic passwords for large transfers
- Update personal information

#### Admin Features
- View and manage all customers and accounts
- Add/remove customers
- Create accounts for customers
- Edit user information
- View system statistics
- Manage other admins

## 🚀 Getting Started

### Prerequisites
- C++ compiler with C++11 support
- No external dependencies (STL containers not allowed as per requirements)

### Building the Project
```bash
# Clone the repository
git clone <repository-url>
cd Bank_Operation

# Compile all source files
g++ -std=c++11 -o bank_system *.cpp

# Run the application
./bank_system
```

### Default Users
The system initializes with sample data:

**Admin Account:**
- Username: `admin`
- Password: `admin123`

**Customer Accounts:**
- Customer 1: `ali_ahmadi` / `pass123` (3 accounts)
- Customer 2: `sara_h` / `pass456` (1 account)

## 📁 File Structure

```
Bank_Operation/
├── Account.h/.cpp           # Base account class
├── SavingsAccount.h/.cpp    # DepositAccount implementation
├── CurrentAccount.h/.cpp    # CurrentAccount with overdraft
├── LoanAccount.h/.cpp       # QarzAccount (interest-free)
├── User.h/.cpp             # Base user class
├── Customer.h/.cpp         # Customer implementation
├── Admin.h/.cpp            # Admin implementation
├── LinkedList.h            # Custom linked list template
├── main.cpp                # Main application entry point
└── README.md               # This file
```

## 🎮 Usage Examples

### Customer Operations
```cpp
// Login as customer
Username: ali_ahmadi
Password: pass123

// View accounts
1. View All Accounts

// Transfer money
4. Card to Card Transfer
Source card: 1234567812345678
Destination card: 9876543212345678
Amount: 50000
Second password: 5678  // Static password for ≤100k
```

### Admin Operations
```cpp
// Login as admin
Username: admin
Password: admin123

// Create new account
5. Create Account
Customer: ali_ahmadi
Type: deposit
Card: 1111222233334444
Account: ACC005
IBAN: IR111222333
Primary password: newpass
Static second password: newsecond
```

## 🔮 Future Enhancements

### Phase 2: Qt GUI Implementation
- Modern graphical user interface using Qt framework
- Form-based data entry and validation
- Rich account dashboards and transaction history
- Interactive transfer wizards

### Phase 3: Advanced Features
- Transaction history and reporting
- Account statements generation
- Enhanced security features
- Multi-language support

## 🛠 Development Guidelines

### Git Workflow (as per requirements)
1. Create separate branches for each major component
2. Make frequent, meaningful commits with clear messages
3. Follow incremental development approach
4. Document all changes in commit messages

### Code Standards
- Object-oriented design principles
- RAII for resource management
- Consistent naming conventions
- Comprehensive error handling
- Memory safety practices

## 📝 Requirements Compliance

✅ **Base class User** with firstName, lastName, nationalId, age, username, password  
✅ **Derived classes** Customer and Admin  
✅ **Customer can hold up to 5 accounts** of any type  
✅ **Admin has full access** to view and manage all users and accounts  
✅ **Account base class** with derived DepositAccount, CurrentAccount, QarzAccount  
✅ **Account fields**: cardNumber, accountNumber, IBAN, CVV2, expirationDate, balance, passwords  
✅ **Transfer system** with limits, fees, and password requirements  
✅ **Custom LinkedList** implementation (no STL)  
✅ **Memory-only storage** (no file persistence)  
✅ **Sample objects** preloaded at startup  

## 📄 License

This project is developed as an educational banking system implementation.

## 👥 Contributors

- [Your Name] - Initial implementation and architecture

---

**Note**: This is the console version of the banking system. Qt GUI implementation will be added in subsequent development phases as per the incremental development approach specified in the requirements.
