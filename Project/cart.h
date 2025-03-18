#ifndef CART_H
#define CART_H

#include "medicine.h"
#include <vector>

struct CartItem {
    Medicine medicine;
    int quantity;
    float subtotal;
    CartItem(Medicine med, int qty) : medicine(med), quantity(qty) {
        subtotal = med.getPrice() * qty;
    }
};

class Cart {
private:
    std::vector<CartItem> items;
    float total;

public:
    Cart() : total(0.0f) {}

    void addItem(Medicine med, int quantity);
    void printReceipt(const char* date);
    void displayCart();
    void printReceipt();
    float getTotal() const { return total; }
    const std::vector<CartItem>& getItems() const { return items; }
    void clear() { items.clear(); total = 0.0f; }
};

#endif // CART_H