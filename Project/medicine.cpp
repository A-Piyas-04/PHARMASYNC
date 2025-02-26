#include "medicine.h"
#include <iostream>

using namespace std;

Medicine::Medicine() {}

Medicine::Medicine(const char* n, const char* gName, const char* supp, const char* batch, float pr, int qty, const char* exp) {
    myStrcpy(name, n);
    myStrcpy(genericName, gName);
    myStrcpy(supplier, supp);
    myStrcpy(batchID, batch);
    price = pr;
    quantity = qty;
    myStrcpy(expiryDate, exp);
}

const char* Medicine::getName() { return name; }
const char* Medicine::getGenericName() { return genericName; }
const char* Medicine::getSupplier() { return supplier; }
const char* Medicine::getBatchID() { return batchID; }
const char* Medicine::getExpiryDate() { return expiryDate; }
float Medicine::getPrice() { return price; }
int Medicine::getQuantity() { return quantity; }
void Medicine::setPrice(float newPrice) { price = newPrice; }
void Medicine::setQuantity(int newQuantity) { quantity = newQuantity; }

void Medicine::display() {
    char namePad[50], genericNamePad[50], supplierPad[50], batchIDPad[20], priceStr[10], quantityStr[10];
    myStrcpy(namePad, name);
    myStrcpy(genericNamePad, genericName);
    myStrcpy(supplierPad, supplier);
    myStrcpy(batchIDPad, batchID);
    padString(namePad, 15);
    padString(genericNamePad, 15);
    padString(supplierPad, 20);
    padString(batchIDPad, 10);
    intToStr(price, priceStr, 8);
    intToStr(quantity, quantityStr, 8);
    char expiryDatePad[15];
    myStrcpy(expiryDatePad, expiryDate);
    padString(expiryDatePad, 12);
    cout << "| " << namePad << "| " << genericNamePad << "| " << supplierPad << "| " << batchIDPad << "| " << priceStr << "| " << quantityStr << "| " << expiryDatePad << "|" << endl;
}

int Medicine::compareExpiryDate(const char* otherExpiryDate) const {
    int result = myStrcmp(expiryDate, otherExpiryDate);
    if (result == 0) {
        return 0;
    }
    return (result > 0) ? 1 : -1;
}