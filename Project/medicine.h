#ifndef MEDICINE_H
#define MEDICINE_H

#include "utility.h"

using namespace std;

class Medicine {
private:
    char name[50];
    char genericName[50];
    char supplier[50];
    char batchID[20];
    float price;
    int quantity;
    char expiryDate[15]; // Format: YYYY-MM-DD

public:
    Medicine();
    Medicine(const char* n, const char* gName, const char* supp, const char* batch, float pr, int qty, const char* exp);

    const char* getName();
    const char* getGenericName();
    const char* getSupplier();
    const char* getBatchID();
    const char* getExpiryDate();
    float getPrice();
    int getQuantity();
    void setPrice(float newPrice);
    void setQuantity(int newQuantity);

    void display();
    int compareExpiryDate(const char* otherExpiryDate) const;
};

#endif // MEDICINE_H