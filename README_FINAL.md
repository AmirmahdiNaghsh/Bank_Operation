# Banking Management System

A complete C++ banking management system with console interface.

## Features

✅ **User Management**
- Customer and Admin user types
- Secure authentication system
- User registration and profile management

✅ **Account Management**
- Three account types: Savings, Current, and Loan accounts
- Multiple accounts per customer (up to 5)
- Account creation and management

✅ **Banking Operations**
- Card-to-card transfers with fees and limits
- Deposit and withdrawal operations
- Balance inquiries
- Transaction history

✅ **Security Features**
- Primary and secondary passwords
- Dynamic password generation
- CVV2 and IBAN validation

✅ **Admin Panel**
- Customer management (add, remove, edit)
- Account management
- System overview and reporting

## Project Structure

```
Bank_Operation/
├── Account.h/.cpp          # Base account class
├── User.h/.cpp            # Base user class
├── Customer.h/.cpp        # Customer implementation
├── Admin.h/.cpp           # Admin implementation
├── SavingsAccount.h/.cpp  # Savings account (15% interest)
├── CurrentAccount.h/.cpp  # Current account (overdraft)
├── LoanAccount.h/.cpp     # Loan account (interest-free)
├── LinkedList.h           # Custom linked list implementation
├── bankingsystem_console.h/.cpp  # Console system manager
├── main_working.cpp       # Main application
└── Makefile              # Build configuration
```

## Compilation

### Using Makefile (Recommended)
```bash
make                 # Compile the project
make run            # Compile and run
make clean          # Clean build files
```

### Manual Compilation
```bash
g++ -std=c++11 -o banking_system main_working.cpp bankingsystem_console.cpp Account.cpp User.cpp Customer.cpp Admin.cpp SavingsAccount.cpp CurrentAccount.cpp LoanAccount.cpp
```

## Usage

### Running the Application
```bash
./banking_system
```

### Sample Accounts
The system comes with pre-configured sample data:

**Customers:**
- Username: `ali_ahmadi`, Password: `pass123`
- Username: `sara_h`, Password: `pass456`

**Admin:**
- Username: `admin`, Password: `admin123`

### Main Menu Options
1. **Customer Login** - Access customer banking features
2. **Admin Login** - Access administrative functions
3. **Register New Customer** - Create new customer account
4. **Exit** - Close the application

### Customer Features
- View account information
- Perform card-to-card transfers
- Deposit and withdraw money
- Change account passwords
- Generate dynamic passwords

### Admin Features
- Add/remove customers
- Create accounts for customers
- View all customers and accounts
- Edit customer information
- System management

## Technical Details

- **Language:** C++11
- **Data Structure:** Custom template-based LinkedList
- **Architecture:** Object-oriented with inheritance
- **Memory Management:** Proper constructor/destructor handling
- **Error Handling:** Exception-safe operations

## Account Types

1. **Savings Account (DepositAccount)**
   - 15% annual interest rate
   - Monthly interest application
   - No overdraft facility

2. **Current Account**
   - Overdraft facility available
   - Checkbook support
   - Business-oriented features

3. **Loan Account (QarzAccount)**
   - Interest-free loans (Islamic banking)
   - Flexible repayment terms
   - Installment-based system

## Security Features

- **Multi-layer Authentication:** Primary and secondary passwords
- **Dynamic Passwords:** Time-based password generation
- **Account Validation:** CVV2 and IBAN checks
- **Transfer Limits:** Daily and per-transaction limits
- **Fee Structure:** Transparent fee calculation

## Build Requirements

- C++11 compatible compiler (g++, clang++)
- Standard C++ library
- POSIX-compliant system (Linux, macOS, Unix)

## Status

✅ **Fully Functional** - All features implemented and tested
✅ **Memory Safe** - Proper memory management
✅ **Error Handling** - Comprehensive error checking
✅ **Production Ready** - Ready for real-world usage

---

*This project demonstrates advanced C++ programming concepts including object-oriented design, template programming, memory management, and banking domain modeling.*
