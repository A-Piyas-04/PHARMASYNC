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

    // Write transaction box top
    fprintf(file, "\n+====================================================================+\n");
    fprintf(file,   "|                    Transaction Date: %-10s                    |\n", date);
    fprintf(file,   "+====================================================================+\n");
    fprintf(file,   "|  Item                    Batch ID    Quantity    Price (RM)        |\n");
    fprintf(file,   "|  ----------------------------------------------------------------  |\n");
    
    // Write items
    for (const CartItem& item : cart.getItems()) {
        fprintf(file, "|  %-20s    %-8s    %8d    %10.2f        |\n",
            item.medicine.getName(),
            item.medicine.getBatchID(),
            item.quantity,
            item.subtotal);
    }
    
    // Write empty line and total
    fprintf(file, "|                                                                    |\n");
    fprintf(file, "|                                    Total: RM %-9.2f             |\n", cart.getTotal());
    fprintf(file, "+====================================================================+\n");
    
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