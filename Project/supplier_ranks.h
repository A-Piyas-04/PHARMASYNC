#ifndef SUPPLIER_RANKS_H
#define SUPPLIER_RANKS_H

#include <fstream>
#include <cstring>
#include "utility.h"

using namespace std;

class SupplierRanking {
private:
    static const int MAX_SUPPLIERS = 100;
    char suppliers[MAX_SUPPLIERS][50];
    int salesCount[MAX_SUPPLIERS];
    int supplierCount;

    void loadRankings();
    void saveRankings() const;
    int findSupplier(const char* supplier) const;

public:
    SupplierRanking();
    void updateSupplierSales(const char* supplier, int quantity);
    void displayRankings() const;
};

#endif