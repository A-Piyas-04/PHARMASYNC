#include "cart.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Cart::addItem(Medicine med, int quantity) {
    if (quantity <= 0) {
        cout << "Invalid quantity. Please enter a positive number." << endl;
        return;
    }

    if (quantity > med.getQuantity()) {
        cout << "Error: Not enough stock available. Available quantity: " << med.getQuantity() << endl;
        return;
    }

    CartItem item(med, quantity);
    items.push_back(item);
    total += item.subtotal;
}

void Cart::displayCart() {
    if (items.empty()) {
        cout << "Cart is empty." << endl;
        return;
    }

    cout << "\n=== Shopping Cart ===" << endl;
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
    if (items.empty()) {
        cout << "No items to print receipt for." << endl;
        return;
    }

    cout << "\n==================== PHARMASYNC RECEIPT ====================" << endl;
    cout << "Date: [Current Date]" << endl;
    cout << "==============================================================" << endl;

    // Header with consistent column widths
    cout << left << setw(30) << "Medicine"
         << right << setw(5) << "Qty"
         << right << setw(12) << "Price"
         << right << setw(12) << "Subtotal" << endl;
    cout << string(59, '-') << endl;

    // Print items with consistent decimal places and alignment
    for (const CartItem& item : items) {
        cout << left << setw(30) << item.medicine.getName()
             << right << setw(5) << item.quantity
             << right << setw(12) << "$" + to_string(item.medicine.getPrice()).substr(0, to_string(item.medicine.getPrice()).find(".") + 3)
             << right << setw(12) << "$" + to_string(item.subtotal).substr(0, to_string(item.subtotal).find(".") + 3) << endl;
    }

    // Footer with proper alignment
    cout << string(59, '-') << endl;
    cout << right << setw(47) << "Subtotal: $" << fixed << setprecision(2) << total << endl;
    cout << "==============================================================" << endl;
    cout << setw(35) << right << "     Thank you for shopping!" << endl;
    cout << "==============================================================" << endl;
}