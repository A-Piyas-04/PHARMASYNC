#include "transaction.h"
#include <ctime>
#include <iomanip>

const char* Transaction::TRANSACTION_FILE = "transaction.txt";

void Transaction::recordTransaction(const Cart& cart, const char* date) {
    writeTransactionToFile(cart, date);
}

void Transaction::writeTransactionToFile(const Cart& cart, const char* date) {
    FILE* file = fopen(TRANSACTION_FILE, "a");
    if (!file) {
        std::cout << "Error opening transaction file for writing!" << std::endl;
        return;
    }

    // Write transaction header
    fprintf(file, "\n=== Transaction Date: %s ===\n", date);
    
    // Write items
    for (const CartItem& item : cart.getItems()) {
        fprintf(file, "%s(%s) - %d --> %.2f\n",
            item.medicine.getName(),
            item.medicine.getBatchID(),
            item.quantity,
            item.subtotal);
    }
    
    // Write total
    fprintf(file, "Total : %.2f\n", cart.getTotal());
    fprintf(file, "====================================\n");
    
    fclose(file);
}

void Transaction::displayTransactionHistory() {
    FILE* file = fopen(TRANSACTION_FILE, "r");
    if (!file) {
        std::cout << "No transaction history found." << std::endl;
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        std::cout << line;
    }

    fclose(file);
}