#ifndef PHARMACY_H
#define PHARMACY_H

#include "medicine.h"
#include "notification.h"

using namespace std;

struct Node {
    Medicine data;
    Node* next;
    Node(Medicine med) : data(med), next(nullptr) {}
};

class Pharmacy {
private:
    Node* head;
    int medicineCount;
    NotificationManager notificationManager;

    void printHeader();
    void printFooter();
    void swap(Node* a, Node* b);

public:
    Pharmacy();
    ~Pharmacy();

    void loadData(const char* filename);
    void addMedicine(const Medicine& med);
    void displayAllMedicines();
    void searchMedicine();
    void sortMedicines(int sortBy, bool ascending);
    void filterByQuantity(int minQty, int maxQty);
    void addMedicineToFile(const char* filename);
    void updateMedicine(const char* filename);
    void searchBySupplier();
    
    // New methods for sales functionality
    Medicine* findMedicine(const char* name, const char* batchID);
    void updateMedicineQuantity(const char* name, const char* batchID, int quantityChange);
    void saveToFile(const char* filename);
    
    // Notification system methods
    void checkAndDisplayNotifications();
    int getNotificationCount() const { 
        return notificationManager.getNotificationCount(); 
    }
    int countPendingNotifications();
};

#endif // PHARMACY_H