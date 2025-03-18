#include <iostream>
#include <cassert>
#include <fstream>
#include "../medicine.h"
#include "../pharmacy.h"
#include "../cart.h"
#include "../notification.h"
#include "../supplier_ranks.h"

using namespace std;


// Test Case 1: Medicine Creation and Basic Properties
void testMedicineCreation() {
    Medicine med("Paracetamol", "Generic Paracetamol", "ABC Pharma", "B123", 10.5f, 100, "2024-12-31");
    assert(myStrcmp(med.getName(), "Paracetamol") == 0);
    assert(myStrcmp(med.getBatchID(), "B123") == 0);
    assert(med.getQuantity() == 100);
    std::cout << "Test Case 1: Medicine Creation - Passed\n";
}

// Test Case 2: Cart Operations
void testCartOperations() {
    Medicine med("Aspirin", "Generic Aspirin", "XYZ Pharma", "B456", 15.0f, 50, "2024-12-31");
    Cart cart;
    cart.addItem(med, 2);
    assert(cart.getTotal() == 30.0f);
    assert(cart.getItems().size() == 1);
    std::cout << "Test Case 2: Cart Operations - Passed\n";
}

// Test Case 3: Notification Check
void testNotificationSystem() {
    Medicine medicines[1] = {
        Medicine("Vitamin C", "Ascorbic Acid", "Health Corp", "B789", 20.0f, 5, "2024-01-31")
    };
    NotificationManager notifManager;
    int pendingNotifs = notifManager.countPendingNotifications(medicines, 1);
    assert(pendingNotifs > 0); // Should have notifications due to low stock (5 < 10)
    std::cout << "Test Case 3: Notification System - Passed\n";
}

// Test Case 4: Medicine Price Validation
void testMedicinePrice() {
    Medicine med("Ibuprofen", "Pain Relief", "MedCorp", "B101", 25.99f, 75, "2024-06-30");
    assert(med.getPrice() == 25.99f);
    std::cout << "Test Case 4: Medicine Price - Passed\n";
}

// Test Case 5: Supplier Information
void testSupplierInfo() {
    Medicine med("Amoxicillin", "Antibiotic", "PharmaCare", "B202", 45.50f, 30, "2024-09-30");
    assert(myStrcmp(med.getSupplier(), "PharmaCare") == 0);
    std::cout << "Test Case 5: Supplier Info - Passed\n";
}

// Test Case 6: Medicine Search Functionality
void testMedicineSearch() {
    Pharmacy pharmacy;
    Medicine med1("Paracetamol", "Pain Relief", "ABC Pharma", "B123", 10.5f, 100, "2024-12-31");
    Medicine med2("Aspirin", "Pain Relief", "XYZ Pharma", "B456", 15.0f, 50, "2024-12-31");
    
    pharmacy.addMedicine(med1);
    pharmacy.addMedicine(med2);
    
    Medicine* found = pharmacy.findMedicine("Paracetamol", "B123");
    assert(found != nullptr);
    assert(myStrcmp(found->getName(), "Paracetamol") == 0);
    assert(myStrcmp(found->getBatchID(), "B123") == 0);
    assert(found->getPrice() == 10.5f);
    
    // Test for non-existent medicine
    found = pharmacy.findMedicine("NonExistent", "B999");
    assert(found == nullptr);
    
    std::cout << "Test Case 6: Medicine Search - Passed\n";
}

// Test Case 7: Transaction Recording
void testTransaction() {
    Medicine med("Cetirizine", "Antihistamine", "AllergyCare", "B303", 15.75f, 60, "2024-08-31");
    Cart cart;
    cart.addItem(med, 3);
    assert(cart.getTotal() == 47.25f);
    std::cout << "Test Case 7: Transaction - Passed\n";
}

// Test Case 8: Medicine Deletion
void testMedicineDeletion() {
    Pharmacy pharmacy;
    Medicine med("Omeprazole", "Antacid", "GastroHealth", "B404", 35.25f, 40, "2024-07-31");
    pharmacy.addMedicine(med);
    pharmacy.deleteMedicineFromList("Omeprazole", "B404");
    assert(pharmacy.findMedicine("Omeprazole", "B404") == nullptr);
    std::cout << "Test Case 8: Medicine Deletion - Passed\n";
}

// Test Case 9: Empty Cart Validation
void testEmptyCart() {
    Cart cart;
    assert(cart.getTotal() == 0.0f);
    assert(cart.getItems().empty());
    cout << "Test Case 9: Empty Cart - Passed\n";
}

// Test Case 10: Multiple Items in Cart
void testMultipleCartItems() {
    Cart cart;
    Medicine med1("Aspirin", "Pain Relief", "XYZ Pharma", "B456", 15.0f, 50, "2024-12-31");
    Medicine med2("Paracetamol", "Fever Relief", "ABC Pharma", "B123", 10.0f, 100, "2024-12-31");
    cart.addItem(med1, 2);
    cart.addItem(med2, 3);
    assert(cart.getTotal() == 60.0f);
    assert(cart.getItems().size() == 2);
    cout << "Test Case 10: Multiple Cart Items - Passed\n";
}

// Test Case 11: Zero Quantity Medicine
void testZeroQuantityMedicine() {
    Medicine med("Test Med", "Test Generic", "Test Pharma", "T123", 10.0f, 0, "2024-12-31");
    assert(med.getQuantity() == 0);
    cout << "Test Case 11: Zero Quantity Medicine - Passed\n";
}

// Test Case 12: Medicine Generic Name
void testMedicineGenericName() {
    Medicine med("Brand Med", "Generic Med", "Test Pharma", "T123", 10.0f, 50, "2024-12-31");
    assert(myStrcmp(med.getGenericName(), "Generic Med") == 0);
    cout << "Test Case 12: Medicine Generic Name - Passed\n";
}

// Test Case 13: Multiple Notifications
void testMultipleNotifications() {
    Medicine medicines[2] = {
        Medicine("Med1", "Gen1", "Pharma1", "B1", 10.0f, 5, "2024-01-31"),
        Medicine("Med2", "Gen2", "Pharma2", "B2", 20.0f, 3, "2024-02-28")
    };
    NotificationManager notifManager;
    int pendingNotifs = notifManager.countPendingNotifications(medicines, 2);
    assert(pendingNotifs == 2);
    cout << "Test Case 13: Multiple Notifications - Passed\n";
}

// Test Case 14: Medicine Batch Validation
void testMedicineBatch() {
    Medicine med("TestMed", "TestGen", "TestPharma", "BATCH123", 15.0f, 50, "2024-12-31");
    assert(myStrcmp(med.getBatchID(), "BATCH123") == 0);
    cout << "Test Case 14: Medicine Batch - Passed\n";
}

// Test Case 15: Multiple Medicine Deletion
void testMultipleMedicineDeletion() {
    Pharmacy pharmacy;
    Medicine med1("Med1", "Gen1", "Pharma1", "B1", 10.0f, 50, "2024-12-31");
    Medicine med2("Med2", "Gen2", "Pharma2", "B2", 20.0f, 50, "2024-12-31");
    pharmacy.addMedicine(med1);
    pharmacy.addMedicine(med2);
    pharmacy.deleteMedicineFromList("Med1", "B1");
    pharmacy.deleteMedicineFromList("Med2", "B2");
    assert(pharmacy.findMedicine("Med1", "B1") == nullptr);
    assert(pharmacy.findMedicine("Med2", "B2") == nullptr);
    cout << "Test Case 15: Multiple Medicine Deletion - Passed\n";
}

// Test Case 16: Cart Total Precision
void testCartTotalPrecision() {
    Cart cart;
    Medicine med("PrecisionMed", "GenericPrec", "PrecPharma", "P123", 10.33f, 50, "2024-12-31");
    cart.addItem(med, 3);
    assert(cart.getTotal() == 30.99f);
    cout << "Test Case 16: Cart Total Precision - Passed\n";
}

// Test Case 17: Medicine Name Length
void testMedicineNameLength() {
    Medicine med("VeryLongMedicineName", "LongGenericName", "LongPharmaName", "L123", 10.0f, 50, "2024-12-31");
    assert(myStrlen(med.getName()) > 0);
    cout << "Test Case 17: Medicine Name Length - Passed\n";
}

// Test Case 18: Multiple Medicine Search
void testMultipleMedicineSearch() {
    Pharmacy pharmacy;
    Medicine med1("SearchMed1", "Gen1", "Pharma1", "S1", 10.0f, 50, "2024-12-31");
    Medicine med2("SearchMed2", "Gen2", "Pharma2", "S2", 20.0f, 50, "2024-12-31");
    pharmacy.addMedicine(med1);
    pharmacy.addMedicine(med2);
    Medicine* found1 = pharmacy.findMedicine("SearchMed1", "S1");
    Medicine* found2 = pharmacy.findMedicine("SearchMed2", "S2");
    assert(found1 != nullptr && found2 != nullptr);
    cout << "Test Case 18: Multiple Medicine Search - Passed\n";
}

// Test Case 19: Cart Item Count
void testCartItemCount() {
    Cart cart;
    Medicine med("CountMed", "GenCount", "CountPharma", "C123", 5.0f, 100, "2024-12-31");
    cart.addItem(med, 5);
    assert(cart.getItems().size() == 1);
    cout << "Test Case 19: Cart Item Count - Passed\n";
}

// Test Case 20: Medicine Price Zero
void testMedicinePriceZero() {
    Medicine med("FreeMed", "FreeGen", "FreePharma", "F123", 0.0f, 50, "2024-12-31");
    assert(med.getPrice() == 0.0f);
    cout << "Test Case 20: Medicine Price Zero - Passed\n";
}

// Test Case 21: Large Quantity Medicine
void testLargeQuantityMedicine() {
    Medicine med("BulkMed", "BulkGen", "BulkPharma", "BK123", 10.0f, 1000, "2024-12-31");
    assert(med.getQuantity() == 1000);
    cout << "Test Case 21: Large Quantity Medicine - Passed\n";
}

// Test Case 22: Cart Multiple Same Item
void testCartMultipleSameItem() {
    Cart cart;
    Medicine med("DupMed", "DupGen", "DupPharma", "D123", 10.0f, 100, "2024-12-31");
    cart.addItem(med, 2);
    cart.addItem(med, 3);
    assert(cart.getTotal() == 50.0f);
    cout << "Test Case 22: Cart Multiple Same Item - Passed\n";
}

// Test Case 23: Medicine Expiry Format
void testMedicineExpiryFormat() {
    Medicine med("ExpMed", "ExpGen", "ExpPharma", "E123", 10.0f, 50, "2024-12-31");
    assert(myStrlen(med.getExpiryDate()) == 10);
    cout << "Test Case 23: Medicine Expiry Format - Passed\n";
}

// Test Case 24: Pharmacy Empty Check
void testPharmacyEmpty() {
    Pharmacy pharmacy;
    Medicine* found = pharmacy.findMedicine("NonExistent", "NE123");
    assert(found == nullptr);
    cout << "Test Case 24: Pharmacy Empty - Passed\n";
}

// Test Case 25: Medicine Copy
void testMedicineCopy() {
    Medicine med1("CopyMed", "CopyGen", "CopyPharma", "CP123", 10.0f, 50, "2024-12-31");
    Medicine med2 = med1;
    assert(myStrcmp(med1.getName(), med2.getName()) == 0);
    assert(med1.getPrice() == med2.getPrice());
    cout << "Test Case 25: Medicine Copy - Passed\n";
}

// Test Case 26: Cart Clear
void testCartClear() {
    Cart cart;
    Medicine med("ClearMed", "ClearGen", "ClearPharma", "CL123", 10.0f, 50, "2024-12-31");
    cart.addItem(med, 2);
    cart.clear();
    assert(cart.getTotal() == 0.0f);
    assert(cart.getItems().empty());
    cout << "Test Case 26: Cart Clear - Passed\n";
}

// Test Case 27: Supplier Ranking Basic Operations
void testSupplierRankingBasic() {
    SupplierRanking ranking;
    ranking.updateSupplierSales("TestSupplier", 10);
    ranking.updateSupplierSales("TestSupplier", 5);
    // Verify the file exists after update
    ifstream file("supplier_ranks.txt");
    assert(file.good());
    file.close();
    cout << "Test Case 27: Supplier Ranking Basic - Passed\n";
}

// Test Case 28: Multiple Supplier Rankings
void testMultipleSuppliers() {
    SupplierRanking ranking;
    ranking.updateSupplierSales("Supplier1", 10);
    ranking.updateSupplierSales("Supplier2", 20);
    ranking.updateSupplierSales("Supplier3", 15);
    // Verify the file exists and contains data
    ifstream file("supplier_ranks.txt");
    assert(file.good());
    string content;
    bool found = false;
    while (getline(file, content)) {
        if (content.find("Supplier2") != string::npos) {
            found = true;
            break;
        }
    }
    assert(found);
    file.close();
    cout << "Test Case 28: Multiple Suppliers - Passed\n";
}

// Test Case 29: Zero Sales Supplier
void testZeroSalesSupplier() {
    SupplierRanking ranking;
    ranking.updateSupplierSales("ZeroSupplier", 0);
    cout << "Test Case 29: Zero Sales Supplier - Passed\n";
}

// Test Case 30: Medicine Update
void testMedicineUpdate() {
    Pharmacy pharmacy;
    Medicine med("UpdateMed", "UpdateGen", "UpdatePharma", "U123", 10.0f, 50, "2024-12-31");
    pharmacy.addMedicine(med);
    pharmacy.updateMedicineQuantity("UpdateMed", "U123", -10);
    Medicine* updated = pharmacy.findMedicine("UpdateMed", "U123");
    assert(updated != nullptr);
    assert(updated->getQuantity() == 40);
    cout << "Test Case 30: Medicine Update - Passed\n";
}

int main() {
    cout << "Running Unit Tests...\n\n";
    
    testMedicineCreation();
    testCartOperations();
    testNotificationSystem();
    testMedicinePrice();
    testSupplierInfo();
    testMedicineSearch();
    testTransaction();
    testMedicineDeletion();
    testEmptyCart();
    testMultipleCartItems();
    testZeroQuantityMedicine();
    testMedicineGenericName();
    testMultipleNotifications();
    testMedicineBatch();
    testMultipleMedicineDeletion();
    testCartTotalPrecision();
    testMedicineNameLength();
    testMultipleMedicineSearch();
    testCartItemCount();
    testMedicinePriceZero();
    testLargeQuantityMedicine();
    testCartMultipleSameItem();
    testMedicineExpiryFormat();
    testPharmacyEmpty();
    testMedicineCopy();
    testCartClear();
    testSupplierRankingBasic();
    testMultipleSuppliers();
    testZeroSalesSupplier();
    testMedicineUpdate();
    
    cout << "\nAll tests passed successfully!\n";
    cout << "\nPress any key to exit....";
    cin.get();
    return 0;
}