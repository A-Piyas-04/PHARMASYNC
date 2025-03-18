#ifndef SUPPLIER_RANKS_H
#define SUPPLIER_RANKS_H

#include <iostream>
#include <cstring>
#include <vector>
#include "utility.h"

struct SupplierRank {
    char supplier[50];
    int salesCount;

    SupplierRank(const char* sup, int count = 0) {
        strcpy(supplier, sup);
        salesCount = count;
    }
};

class SupplierRanking {
private:
    static const char* SUPPLIER_RANKS_FILE;
    std::vector<SupplierRank> ranks;

    void loadRanks();
    void saveRanks() const;
    int findSupplierIndex(const char* supplier) const;

public:
    SupplierRanking();
    void incrementSales(const char* supplier, int quantity = 1);
    void displayRanking() const;
};

#endif