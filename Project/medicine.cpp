#include "medicine.h"
#include <iostream>
#include "date_utility.h"

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

const char* Medicine::getName() const { return name; }
const char* Medicine::getGenericName() const { return genericName; }
const char* Medicine::getSupplier() const { return supplier; }
const char* Medicine::getBatchID() const { return batchID; }
const char* Medicine::getExpiryDate() const { return expiryDate; }
float Medicine::getPrice() const { return price; }
int Medicine::getQuantity() const { return quantity; }
void Medicine::setPrice(float newPrice) { price = newPrice; }
void Medicine::setQuantity(int newQuantity) { quantity = newQuantity; }

void Medicine::display() {
    char namePad[50], genericNamePad[50], supplierPad[50], batchIDPad[20], quantityStr[10];
    myStrcpy(namePad, name);
    myStrcpy(genericNamePad, genericName);
    myStrcpy(supplierPad, supplier);
    myStrcpy(batchIDPad, batchID);
    padString(namePad, 15);
    padString(genericNamePad, 15);
    padString(supplierPad, 20);
    padString(batchIDPad, 10);
    char priceStr[10];
    sprintf(priceStr, "%.2f", price);
    padString(priceStr, 8);
    intToStr(quantity, quantityStr, 8);
    char expiryDatePad[15];
    myStrcpy(expiryDatePad, expiryDate);
    padString(expiryDatePad, 12);
    bool isNearExp = DateUtility::isNearExpiry(expiryDate);
    bool isLowStock = quantity <= 15;
    
    cout << "| ";
    if (isNearExp) {
        setTextColorRed();
        cout << namePad;
        resetTextColor();
    } else if (isLowStock) {
        setTextColorDarkYellow();
        cout << namePad;
        resetTextColor();
    } else {
        cout << namePad;
    }
    cout << "| " << genericNamePad << "| " << supplierPad << "| " << batchIDPad << "| " << priceStr << "| " << quantityStr << "| " << expiryDatePad << "|" << endl;
}

int Medicine::compareExpiryDate(const char* otherExpiryDate) const {
    int result = myStrcmp(expiryDate, otherExpiryDate);
    if (result == 0) {
        return 0;
    }
    return (result > 0) ? 1 : -1;
}