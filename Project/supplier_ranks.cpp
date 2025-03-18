#include "supplier_ranks.h"
#include <iostream>
#include <cstring>
#include <iomanip>

SupplierRanking::SupplierRanking() {
    supplierCount = 0;
    loadRankings();
}

void SupplierRanking::loadRankings() {
    ifstream file("supplier_ranks.txt");
    if (!file) {
        return;
    }

    char line[256];
    bool headerSkipped = false;
    supplierCount = 0;

    while (file.getline(line, sizeof(line))) {
        if (!headerSkipped) {
            if (strstr(line, "SUPPLIER RANKINGS")) {
                headerSkipped = true;
                // Skip the next two lines (border and header)
                file.getline(line, sizeof(line));
                file.getline(line, sizeof(line));
            }
            continue;
        }

        if (line[0] == '+') continue;

        char supplier[50];
        int count;
        sscanf(line, "| %[^|]| %d", supplier, &count);

        // Remove trailing spaces
        char* end = supplier + strlen(supplier) - 1;
        while (end > supplier && *end == ' ') end--;
        *(end + 1) = '\0';

        int index = findSupplier(supplier);
        if (index == -1 && supplierCount < MAX_SUPPLIERS) {
            strcpy(suppliers[supplierCount], supplier);
            salesCount[supplierCount] = count;
            supplierCount++;
        } else if (index != -1) {
            salesCount[index] = count;
        }
    }
    file.close();
}

void SupplierRanking::saveRankings() const {
    // First, sort suppliers by sales count in descending order
    int sortedIndices[MAX_SUPPLIERS];
    for (int i = 0; i < supplierCount; i++) sortedIndices[i] = i;
    
    for (int i = 0; i < supplierCount - 1; i++) {
        for (int j = 0; j < supplierCount - i - 1; j++) {
            if (salesCount[sortedIndices[j]] < salesCount[sortedIndices[j + 1]]) {
                int temp = sortedIndices[j];
                sortedIndices[j] = sortedIndices[j + 1];
                sortedIndices[j + 1] = temp;
            }
        }
    }

    ofstream file("supplier_ranks.txt");
    if (!file) {
        cout << "Error: Unable to save supplier rankings\n";
        return;
    }

    // Write table headers
    file << "+====================================+\n";
    file << "|         SUPPLIER RANKINGS          |\n";
    file << "+====================================+\n";
    file << "| Supplier             | Sales Count |\n";
    file << "+------------------------------------+\n";

    // Write sorted supplier data
    for (int i = 0; i < supplierCount; i++) {
        int idx = sortedIndices[i];
        if (salesCount[idx] > 0) {
            file << "| " << left << setw(20) << suppliers[idx] 
                 << " | " << right << setw(11) << salesCount[idx] << " |\n";
            
            // Add appropriate footer based on position
            if (i == supplierCount - 1) {
                file << "+====================================+\n";
            } else {
                file << "+------------------------------------+\n";
            }
        }
    }
    file.close();
}

int SupplierRanking::findSupplier(const char* supplier) const {
    for (int i = 0; i < supplierCount; i++) {
        if (strcmp(suppliers[i], supplier) == 0) {
            return i;
        }
    }
    return -1;
}

void SupplierRanking::updateSupplierSales(const char* supplier, int quantity) {
    int index = findSupplier(supplier);
    if (index != -1) {
        salesCount[index] += quantity;
    } else if (supplierCount < MAX_SUPPLIERS) {
        strcpy(suppliers[supplierCount], supplier);
        salesCount[supplierCount] = quantity;
        supplierCount++;
    }
    saveRankings();
}

void SupplierRanking::displayRankings() const {
    ifstream file("supplier_ranks.txt");
    if (!file) {
        cout << "Error: Unable to read supplier rankings\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.find("SUPPLIER RANKINGS") != string::npos) {
            setTextColorLightGreen();
            cout << line << "\n";
            resetTextColor();
        } else {
            cout << line << "\n";
        }
    }
    file.close();
}