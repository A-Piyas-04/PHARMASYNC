#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "medicine.h"
#include "utility.h"

struct Notification {
    char message[200];
    char type[10];     // "expiry" or "stock"
    char medicineName[50];
    char batchID[20];
    
    Notification() {
        message[0] = '\0';
        type[0] = '\0';
        medicineName[0] = '\0';
        batchID[0] = '\0';
    }
    
    void set(const char* msg, const char* t, const char* name, const char* batch) {
        myStrcpy(message, msg);
        myStrcpy(type, t);
        myStrcpy(medicineName, name);
        myStrcpy(batchID, batch);
    }
};

class NotificationManager {
private:
    static const int MAX_NOTIFICATIONS = 100;
    Notification notifications[MAX_NOTIFICATIONS];
    int notificationCount;
    const int LOW_STOCK_THRESHOLD = 15;
    const int EXPIRY_MONTHS_THRESHOLD = 4;

public:
    NotificationManager() : notificationCount(0) {}
    void checkExpiryDates(const Medicine* medicines, int count);
    void checkLowStock(const Medicine* medicines, int count);
    void displayNotifications();
    int getNotificationCount() const { return notificationCount; }
    void clearNotifications() { notificationCount = 0; }
};

#endif // NOTIFICATION_H