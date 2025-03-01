#ifndef DATE_UTILITY_H
#define DATE_UTILITY_H

#include <ctime>
#include <cstring>
#include <cstdio>

class DateUtility {
public:
    static bool isNearExpiry(const char* expiryDate, int monthsThreshold = 4) {
        // Parse the expiry date
        int year, month, day;
        if (sscanf(expiryDate, "%d-%d-%d", &year, &month, &day) != 3) {
            return false;
        }

        // Get current date
        time_t now = time(0);
        tm* ltm = localtime(&now);
        
        // Calculate date difference in months
        int monthsDiff = (year - (1900 + ltm->tm_year)) * 12 + (month - (1 + ltm->tm_mon));
        
        return monthsDiff <= monthsThreshold && monthsDiff >= 0;
    }

    static char* getCurrentDate() {
        static char date[11];
        time_t now = time(0);
        tm* ltm = localtime(&now);
        snprintf(date, sizeof(date), "%d-%02d-%02d", 
                1900 + ltm->tm_year,
                1 + ltm->tm_mon,
                ltm->tm_mday);
        return date;
    }

    static int monthsBetween(const char* date1, const char* date2) {
        int year1, month1, day1;
        int year2, month2, day2;
        
        if (sscanf(date1, "%d-%d-%d", &year1, &month1, &day1) != 3 ||
            sscanf(date2, "%d-%d-%d", &year2, &month2, &day2) != 3) {
            return 0;
        }
        
        return (year2 - year1) * 12 + (month2 - month1);
    }
};

#endif // DATE_UTILITY_H