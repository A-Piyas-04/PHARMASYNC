#include "cart.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Cart::addItem(Medicine med, int quantity) {
    if (quantity <= 0) {
        setTextColorLightViolet();
cout << "Invalid quantity. Please enter a positive number." << endl;
resetTextColor();
        return;
    }

    if (quantity > med.getQuantity()) {
        setTextColorLightViolet();
cout << "Error: Not enough stock available. Available quantity: " << med.getQuantity() << endl;
resetTextColor();
        return;
    }

    CartItem item(med, quantity);
    items.push_back(item);
    total += item.subtotal;
}

void Cart::displayCart() {
    if (items.empty()) {
        setTextColorLightViolet();
cout << "Cart is empty." << endl;
resetTextColor();
        return;
    }

    cout << "\n";
    setTextColorCyan();
    cout << "=== Shopping Cart ===" << endl;
    resetTextColor();
    cout << "+----------------+----------------+---------+---------+-----------+" << endl;
    cout << "| Medicine Name  | Generic Name   | Price   |Quantity | Subtotal  |" << endl;
    cout << "+----------------+----------------+---------+---------+-----------+" << endl;

    for (const CartItem& item : items) {
        cout << "| " << left << setw(14) << item.medicine.getName()
             << " | " << setw(14) << item.medicine.getGenericName()
             << " | " << right << setw(7) << fixed << setprecision(2) << item.medicine.getPrice()
             << " | " << setw(7) << item.quantity
             << " | " << setw(9) << item.subtotal << " |" << endl;
    }

    cout << "+----------------+----------------+---------+---------+-----------+" << endl;
    cout << "Total Amount: $" << fixed << setprecision(2) << total << endl;
}

void Cart::printReceipt() {
    time_t now = time(0);
    char currentDate[11];
    strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", localtime(&now));
    printReceipt(currentDate);
}

void Cart::printReceipt(const char* date) {
    if (items.empty()) {
        setTextColorLightViolet();
cout << "No items to print receipt for." << endl;
resetTextColor();
        return;
    }

    cout << "\n";
    cout << "+======================================================================+" << endl;
    setTextColorCyan();
    cout << "|                      PHARMASYNC RECEIPT                              |" << endl;
    resetTextColor();
    cout << "|  ------------------------------------------------------------------  |" << endl;
    cout << "|  Date: " << left << setw(58) << date << "    |" << endl;
    cout << "|  ------------------------------------------------------------------  |" << endl;
    cout << "|  " << left << setw(20) << "Medicine"
         << left << setw(15) << "Batch ID"
         << right << setw(10) << "Qty"
         << right << setw(12) << "Price"
         << right << setw(10) << "Total" << " |" << endl;
    cout << "|  ------------------------------------------------------------------  |" << endl;

    for (const CartItem& item : items) {
        cout << "|  " << left << setw(20) << item.medicine.getName()
             << left << setw(15) << item.medicine.getBatchID()
             << right << setw(10) << item.quantity
             << right << setw(12) << fixed << setprecision(2) << item.medicine.getPrice()
             << right << setw(10) << item.subtotal << " |" << endl;
    }

    cout << "|                                                                      |" << endl;
    cout << "|                                    Total:  " << left << setw(8) << fixed << setprecision(2) << total << "                  |" << endl;
    cout << "+======================================================================+" << endl;
    cout << "|                      Thank you for shopping!                         |" << endl;
    cout << "+======================================================================+" << endl;
}