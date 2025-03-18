#include "supplier_ranks.h"
#include <algorithm>
#include <fstream>

const char* SupplierRanking::SUPPLIER_RANKS_FILE = "supplier_ranks.txt";

SupplierRanking::SupplierRanking() {
    loadRanks();
}

void SupplierRanking::loadRanks() {
    std::ifstream file(SUPPLIER_RANKS_FILE);
    if (!file) return;

    char supplier[50];
    int count;
    while (file >> supplier >> count) {
        ranks.push_back(SupplierRank(supplier, count));
    }
    file.close();
}

void SupplierRanking::saveRanks() const {
    std::ofstream file(SUPPLIER_RANKS_FILE);
    if (!file) {
        setTextColorLightViolet();
        std::cout << "Error saving supplier ranks!" << std::endl;
        resetTextColor();
        return;
    }

    for (const auto& rank : ranks) {
        file << rank.supplier << " " << rank.salesCount << std::endl;
    }
    file.close();
}

int SupplierRanking::findSupplierIndex(const char* supplier) const {
    for (size_t i = 0; i < ranks.size(); i++) {
        if (strcmp(ranks[i].supplier, supplier) == 0) {
            return i;
        }
    }
    return -1;
}

void SupplierRanking::incrementSales(const char* supplier, int quantity) {
    int index = findSupplierIndex(supplier);
    if (index >= 0) {
        ranks[index].salesCount += quantity;
    } else {
        ranks.push_back(SupplierRank(supplier, quantity));
    }
    saveRanks();
}

void SupplierRanking::displayRanking() const {
    if (ranks.empty()) {
        setTextColorLightViolet();
        std::cout << "No supplier rankings available yet." << std::endl;
        resetTextColor();
        return;
    }

    std::vector<SupplierRank> sortedRanks = ranks;
    std::sort(sortedRanks.begin(), sortedRanks.end(),
              [](const SupplierRank& a, const SupplierRank& b) {
                  return a.salesCount > b.salesCount;
              });

    std::cout << "\n+====================================+" << std::endl;
    setTextColorCyan();
    std::cout << "|         SUPPLIER RANKINGS          |" << std::endl;
    resetTextColor();
    std::cout << "+====================================+" << std::endl;
    std::cout << "| Supplier           | Sales Count  |" << std::endl;
    std::cout << "+------------------------------------+" << std::endl;

    for (const auto& rank : sortedRanks) {
        printf("| %-18s | %-11d |\n", rank.supplier, rank.salesCount);
    }
    std::cout << "+====================================+" << std::endl;
}