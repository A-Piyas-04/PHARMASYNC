#ifndef SUPPLIER_RANKS_H
#define SUPPLIER_RANKS_H

using namespace std;

class SupplierRanking {
private:
    static const int MAX_SUPPLIERS = 50;
    char suppliers[MAX_SUPPLIERS][50];
    int salesCount[MAX_SUPPLIERS];
    int supplierCount;

    void loadRankings();
    void saveRankings();
    int findSupplierIndex(const char* supplier);

public:
    SupplierRanking();
    void updateSupplierSales(const char* supplier, int quantity);
    void displayRankings();
};

#endif