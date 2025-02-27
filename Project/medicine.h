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

    const char* getName() const;
    const char* getGenericName() const;
    const char* getSupplier() const;
    const char* getBatchID() const;
    const char* getExpiryDate() const;
    float getPrice() const;
    int getQuantity() const;
    void setPrice(float newPrice);
    void setQuantity(int newQuantity);

    void display();
    int compareExpiryDate(const char* otherExpiryDate) const;
};

#endif // MEDICINE_H