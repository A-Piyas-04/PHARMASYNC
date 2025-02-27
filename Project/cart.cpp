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

    cout << "\n================ PHARMASYNC RECEIPT ================" << endl;
    cout << "Date: [Current Date]" << endl;
    cout << "==================================================" << endl;
    cout << "\n";
    cout << left << setw(25) << "Medicine"
         << right << setw(8) << "Qty"
         << right << setw(15) << "Price"
         << right << setw(15) << "Subtotal" << endl;
    cout << "--------------------------------------------------" << endl;

    for (const CartItem& item : items) {
        Medicine tempMed = item.medicine;
        cout << left << setw(25) << tempMed.getName()
             << right << setw(8) << item.quantity
             << right << setw(15) << "$" + to_string(tempMed.getPrice()).substr(0, to_string(tempMed.getPrice()).find(".") + 3)
             << right << setw(15) << "$" + to_string(item.subtotal).substr(0, to_string(item.subtotal).find(".") + 3) << endl;
    }

    cout << "\n";
    cout << "--------------------------------------------------" << endl;
    cout << right << setw(48) << "Subtotal: $" << fixed << setprecision(2) << total << endl;
    cout << "==================================================" << endl;
    cout << "\n                Thank you for shopping!              " << endl;
    cout << "\n==================================================" << endl;
}