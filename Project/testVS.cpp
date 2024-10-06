#include <iostream>
#define MAX_MEDICINES 100

using namespace std;

void myStrcpy(char* destination, const char* source) {
    int i = 0;
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

int myStrcmp(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

int myStrlen(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void padString(char* str, int width) {
    int len = myStrlen(str);
    for (int i = len; i < width; i++) {
        str[i] = ' ';
    }
    str[width] = '\0';
}


void toLowerCase(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + ('a' - 'A');
        }
        i++;
    }
}


void trim(char* str) {
    int start = 0, end = myStrlen(str) - 1;

    while (str[start] == ' ') {
        start++;
    }

    while (end >= start && str[end] == ' ') {
        end--;
    }

    int i = 0;
    while (start <= end) {
        str[i++] = str[start++];
    }
    str[i] = '\0'; 
}



class Medicine {
private:
    char name[50];
    char genericName[50];
    char supplier[50];
    float price;
    int quantity;
    char expiryDate[15]; // Format: YYYY-MM-DD

public:
    Medicine() {}

    Medicine(const char* n, const char* gName, const char* supp, float pr, int qty, const char* exp) {
        myStrcpy(name, n);
        myStrcpy(genericName, gName);
        myStrcpy(supplier, supp);
        price = pr;
        quantity = qty;
        myStrcpy(expiryDate, exp);
    }

    const char* getName() { return name; }
    const char* getGenericName() { return genericName; }
    const char* getExpiryDate() { return expiryDate; }
    float getPrice() { return price; }
    int getQuantity() { return quantity; }

    void display() {
        char namePad[50];
        char genericNamePad[50];
        char supplierPad[50];
        padString(name, 15);
        padString(genericName, 15);
        padString(supplier, 20);
        
        snprintf(namePad, sizeof(namePad), "%s", name);
        snprintf(genericNamePad, sizeof(genericNamePad), "%s", genericName);
        snprintf(supplierPad, sizeof(supplierPad), "%s", supplier);

        cout << "| " << namePad 
             << "| " << genericNamePad 
             << "| " << supplierPad 
             << "| " << price 
             << "| " << quantity 
             << "| " << expiryDate 
             << "|" << endl;
    }

    int compareExpiryDate(const char* otherExpiry) {
        return myStrcmp(expiryDate, otherExpiry);
    }
};


class Pharmacy {
private:
    Medicine medicines[MAX_MEDICINES];
    int medicineCount;

public:
    Pharmacy() {
        medicineCount = 0;
    }

    void loadData(const char* filename) {
        FILE* file = fopen(filename, "r");
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }

        char name[50], genericName[50], supplier[50], expiryDate[15];
        float price;
        int quantity;

        while (fscanf(file, "%s %s %s %f %d %s", name, genericName, supplier, &price, &quantity, expiryDate) != EOF) {
            medicines[medicineCount++] = Medicine(name, genericName, supplier, price, quantity, expiryDate);
        }
        fclose(file);
    }

    void printHeader() {
        cout << "+-----------------+-----------------+----------------------+----------+----------+-------------+" << endl;
        cout << "| Name            | Generic Name    | Supplier             | Price    | Quantity | Expiry Date |" << endl;
        cout << "+-----------------+-----------------+----------------------+----------+----------+-------------+" << endl;
    }

    void printFooter() {
        cout << "+-----------------+-----------------+----------------------+----------+----------+-------------+" << endl;
    }







void searchMedicine(const char* searchTerm) {
    char searchLower[50];
    myStrcpy(searchLower, searchTerm);
    trim(searchLower); 
    toLowerCase(searchLower); 
    bool found = false; 

    printHeader();
    for (int i = 0; i < medicineCount; i++) {
      
        char medicineName[50];
        char genericName[50];
        myStrcpy(medicineName, medicines[i].getName());
        myStrcpy(genericName, medicines[i].getGenericName());

        toLowerCase(medicineName);
        toLowerCase(genericName);
        trim(medicineName);
        trim(genericName);

        if (myStrcmp(medicineName, searchLower) == 0 || myStrcmp(genericName, searchLower) == 0) {
            medicines[i].display();
            found = true;
        }
    }
    if (!found) {
        cout << "| No medicines found matching '" << searchTerm << "' |" << endl;
    }
    printFooter();
}








    void swap(Medicine &a, Medicine &b) {
        Medicine temp = a;
        a = b;
        b = temp;
    }

    void sortMedicines(int sortBy, bool ascending) {
        for (int i = 0; i < medicineCount; i++) {
            for (int j = i + 1; j < medicineCount; j++) {
                bool condition = false;
                switch (sortBy) {
                    case 1:
                        condition = (ascending && myStrcmp(medicines[i].getName(), medicines[j].getName()) > 0) ||
                                    (!ascending && myStrcmp(medicines[i].getName(), medicines[j].getName()) < 0);
                        break;
                    case 2:
                        condition = (ascending && myStrcmp(medicines[i].getGenericName(), medicines[j].getGenericName()) > 0) ||
                                    (!ascending && myStrcmp(medicines[i].getGenericName(), medicines[j].getGenericName()) < 0);
                        break;
                    case 3:
                        condition = (ascending && medicines[i].compareExpiryDate(medicines[j].getExpiryDate()) > 0) ||
                                    (!ascending && medicines[i].compareExpiryDate(medicines[j].getExpiryDate()) < 0);
                        break;
                    case 4:
                        condition = (ascending && medicines[i].getQuantity() > medicines[j].getQuantity()) ||
                                    (!ascending && medicines[i].getQuantity() < medicines[j].getQuantity());
                        break;
                }
                if (condition) {
                    swap(medicines[i], medicines[j]);
                }
            }
        }
    }

 
    void filterByPrice(float minPrice, float maxPrice) {
        printHeader();
        for (int i = 0; i < medicineCount; i++) {
            if (medicines[i].getPrice() >= minPrice && medicines[i].getPrice() <= maxPrice) {
                medicines[i].display();
            }
        }
        printFooter();
    }


    void filterByQuantity(int minQty, int maxQty) {
        printHeader();
        for (int i = 0; i < medicineCount; i++) {
            if (medicines[i].getQuantity() >= minQty && medicines[i].getQuantity() <= maxQty) {
                medicines[i].display();
            }
        }
        printFooter();
    }

    void displayAllMedicines() {
        printHeader();
        for (int i = 0; i < medicineCount; i++) {
            medicines[i].display();
        }
        printFooter();
    }
};


int main() {
    Pharmacy pharmacy;


    pharmacy.loadData("medicine_data.txt");


    cout << "\nAll Medicines:\n";
    pharmacy.displayAllMedicines();


    cout << "\nSearch Results for 'Paracetamol':\n";
    pharmacy.searchMedicine("Paracetamol");

    cout << "\nMedicines sorted by Name (Ascending):\n";
    pharmacy.sortMedicines(1, true);
    pharmacy.displayAllMedicines();

    cout << "\nMedicines sorted by Expiry Date (Ascending):\n";
    pharmacy.sortMedicines(3, true);
    pharmacy.displayAllMedicines();

    cout << "\nMedicines sorted by Quantity (Descending):\n";
    pharmacy.sortMedicines(4, false);
    pharmacy.displayAllMedicines();

    cout << "\nMedicines with price between 10 and 50:\n";
    pharmacy.filterByPrice(10, 50);

    cout << "\nMedicines with quantity between 50 and 150:\n";
    pharmacy.filterByQuantity(50, 150);

    return 0;
}