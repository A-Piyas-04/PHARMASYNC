#include <iostream>
#include <cassert>
#include "../medicine.h"
#include "../pharmacy.h"
#include "../cart.h"
#include "../notification.h"
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

int main() {
    std::cout << "Running Unit Tests...\n\n";
    
    testMedicineCreation();
    testCartOperations();
    testNotificationSystem();
    testMedicinePrice();
    testSupplierInfo();
    testMedicineSearch();
    testTransaction();
    testMedicineDeletion();
    
    std::cout << "\nAll tests passed successfully!\n";
    std::cout << "\nPress any key to exit...";
    std::cin.get();
    return 0;
}