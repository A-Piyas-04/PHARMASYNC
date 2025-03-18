#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "cart.h"
#include "date_utility.h"
#include <iostream>

class Transaction {
private:
    static const char* TRANSACTION_FILE;

public:
    static void recordTransaction(const Cart& cart, const char* date);
    static void displayTransactionHistory();

private:
    static void writeTransactionToFile(const Cart& cart, const char* date);
};

#endif // TRANSACTION_H