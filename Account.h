#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <ctime> 

using namespace std;

class Account {
protected:
    string cardNumber;
    string shebaNumber;
    string accountNumber;
    string cvv2;
    double balance; 
    time_t expirationDate;
    string pin1;
    string pin2_static; 
    string pin2_dynamic;