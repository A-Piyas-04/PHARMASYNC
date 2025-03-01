#include "notification.h"
#include "date_utility.h"
#include <iostream>

void NotificationManager::checkExpiryDates(const Medicine* medicines, int count) {
    const char* currentDate = DateUtility::getCurrentDate();
    
    for (int i = 0; i < count; i++) {
        if (DateUtility::isNearExpiry(medicines[i].getExpiryDate(), EXPIRY_MONTHS_THRESHOLD) && notificationCount < MAX_NOTIFICATIONS) {
            char msg[200];
            char monthStr[10];
            int monthsUntilExpiry = DateUtility::monthsBetween(currentDate, medicines[i].getExpiryDate());
            intToStr(monthsUntilExpiry, monthStr, 2);
            
            myStrcpy(msg, medicines[i].getName());
            myStrcpy(msg + myStrlen(msg), " (Batch: ");
            myStrcpy(msg + myStrlen(msg), medicines[i].getBatchID());
            myStrcpy(msg + myStrlen(msg), ") will expire in ");
            myStrcpy(msg + myStrlen(msg), monthStr);
            myStrcpy(msg + myStrlen(msg), " months");
            
            notifications[notificationCount].set(msg, "expiry", medicines[i].getName(), medicines[i].getBatchID());
            notificationCount++;
        }
    }
}

void NotificationManager::checkLowStock(const Medicine* medicines, int count) {
    for (int i = 0; i < count; i++) {
        if (medicines[i].getQuantity() <= LOW_STOCK_THRESHOLD && notificationCount < MAX_NOTIFICATIONS) {
            char msg[200];
            char qtyStr[10];
            intToStr(medicines[i].getQuantity(), qtyStr, 2);
            
            myStrcpy(msg, medicines[i].getName());
            myStrcpy(msg + myStrlen(msg), " (Batch: ");
            myStrcpy(msg + myStrlen(msg), medicines[i].getBatchID());
            myStrcpy(msg + myStrlen(msg), ") is running low. Current stock: ");
            myStrcpy(msg + myStrlen(msg), qtyStr);
            
            notifications[notificationCount].set(msg, "stock", medicines[i].getName(), medicines[i].getBatchID());
            notificationCount++;
        }
    }
}

void NotificationManager::displayNotifications() {
    if (notificationCount == 0) {
        std::cout << "\nNo notifications to display.\n";
        return;
    }

    std::cout << "\n=== Notifications (" << notificationCount << ") ===\n";
    
    // Display expiry notifications first
    std::cout << "\nExpiry Alerts:\n";
    std::cout << "--------------\n";
    bool hasExpiry = false;
    for (int i = 0; i < notificationCount; i++) {
        if (myStrcmp(notifications[i].type, "expiry") == 0) {
            std::cout << "- " << notifications[i].message << "\n";
            hasExpiry = true;
        }
    }
    if (!hasExpiry) std::cout << "No expiry alerts\n";

    // Then display stock notifications
    std::cout << "\nLow Stock Alerts:\n";
    std::cout << "----------------\n";
    bool hasStock = false;
    for (int i = 0; i < notificationCount; i++) {
        if (myStrcmp(notifications[i].type, "stock") == 0) {
            std::cout << "- " << notifications[i].message << "\n";
            hasStock = true;
        }
    }
    if (!hasStock) std::cout << "No low stock alerts\n";
    
    std::cout << "\nPress Enter to continue...";
    char input[2];
    std::cin.getline(input, 2);
}