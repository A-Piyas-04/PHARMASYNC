#include "supplier_ranks.h"
#include <fstream>
#include <cstring>
#include <iostream>
#include "utility.h"

SupplierRanking::SupplierRanking() : supplierCount(0) {
    loadRankings();
}

void SupplierRanking::loadRankings() {
    std::ifstream file("supplier_ranks.txt");
    if (!file) {
        return;
    }

    char line[100];
    supplierCount = 0;

    // Skip header lines
    for (int i = 0; i < 4; i++) {
        file.getline(line, sizeof(line));
    }

    while (file.getline(line, sizeof(line)) && supplierCount < MAX_SUPPLIERS) {
        if (line[0] == '+' || strlen(line) < 2) continue;

        char* token = strtok(line, "|");
        if (token) {
            // Trim whitespace
            while (*token == ' ') token++;
            strcpy(suppliers[supplierCount], token);
            
            token = strtok(NULL, "|");
            if (token) {
                salesCount[supplierCount] = atoi(token);
            }
            supplierCount++;
        }
    }
    file.close();
}

void SupplierRanking::saveRankings() {
    std::ofstream file("supplier_ranks.txt");
    if (!file) return;

    file << "+====================================+\n";
    file << "|         SUPPLIER RANKINGS          |\n";
    file << "+====================================+\n";
    file << "| Supplier           | Sales Count   |\n";
    file << "+------------------------------------+\n";

    for (int i = 0; i < supplierCount; i++) {
        file << "| " << suppliers[i];
        for (int j = strlen(suppliers[i]); j < 17; j++) file << " ";
        file << "| " << salesCount[i];
        for (int j = std::to_string(salesCount[i]).length(); j < 12; j++) file << " ";
        file << "|\n";
    }

    file << "+====================================+\n";
    file.close();
}

int SupplierRanking::findSupplierIndex(const char* supplier) {
    for (int i = 0; i < supplierCount; i++) {
        if (strcmp(suppliers[i], supplier) == 0) {
            return i;
        }
    }
    
    if (supplierCount < MAX_SUPPLIERS) {
        strcpy(suppliers[supplierCount], supplier);
        salesCount[supplierCount] = 0;
        return supplierCount++;
    }
    return -1;
}

void SupplierRanking::updateSupplierSales(const char* supplier, int quantity) {
    int index = findSupplierIndex(supplier);
    if (index != -1) {
        salesCount[index] += quantity;
        saveRankings();
    }
}

void SupplierRanking::displayRankings() {
    std::ifstream file("supplier_ranks.txt");
    if (!file) return;

    char line[100];
    bool isTitle = false;
    while (file.getline(line, sizeof(line))) {
        if (strstr(line, "SUPPLIER RANKINGS")) {
            setTextColorLightGreen();
            std::cout << line << std::endl;
            resetTextColor();
            isTitle = true;
        } else {
            std::cout << line << std::endl;
        }
    }
    file.close();
}