#include "pharmacy.h"
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

Pharmacy::Pharmacy() : head(nullptr), medicineCount(0) {}

Pharmacy::~Pharmacy() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

void Pharmacy::loadData(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        setTextColorLightViolet();
cout << "Error opening file!" << endl;
resetTextColor();
        return;
    }

    char name[50], genericName[50], supplier[50], batchID[20], expiryDate[15];
    float price;
    int quantity;

    while (fscanf(file, "%s %s %s %s %f %d %s", name, genericName, supplier, batchID, &price, &quantity, expiryDate) != EOF) {
        Medicine med(name, genericName, supplier, batchID, price, quantity, expiryDate);
        addMedicine(med);
    }
    fclose(file);
}

void Pharmacy::addMedicine(const Medicine& med) {
    Node* newNode = new Node(med);
    if (!head) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    medicineCount++;
}

void Pharmacy::printHeader() {
    cout << "+----------------+----------------+---------------------+-----------+---------+---------+-------------+" << endl;
    cout << "| Name           | Generic Name   | Supplier            | Batch ID  | Price   | Quantity| Expiry Date |" << endl;
    cout << "+----------------+----------------+---------------------+-----------+---------+---------+-------------+" << endl;
}

void Pharmacy::printFooter() {
    cout << "+----------------+----------------+---------------------+-----------+---------+---------+-------------+" << endl;
}

void Pharmacy::displayAllMedicines() {
    printHeader();
    Node* current = head;
    while (current) {
        current->data.display();
        current = current->next;
    }
    printFooter();
}

void Pharmacy::searchMedicine() {
    char searchTerm[50];
    cout << "Enter the name or generic name of the medicine to search: ";
    cin.ignore();
    cin.getline(searchTerm, 50);

    char searchLower[50];
    myStrcpy(searchLower, searchTerm);
    trim(searchLower);
    toLowerCase(searchLower);

    bool found = false;
    printHeader();

    Node* current = head;
    while (current) {
        char medicineName[50], genericName[50];
        myStrcpy(medicineName, current->data.getName());
        myStrcpy(genericName, current->data.getGenericName());
        toLowerCase(medicineName);
        toLowerCase(genericName);
        trim(medicineName);
        trim(genericName);

        // Check for exact match or partial match in either name or generic name
        bool isPartialMatch = false;
        char* medNamePtr = medicineName;
        char* genNamePtr = genericName;
        char* searchPtr = searchLower;

        // Check if search term is a substring of medicine name or generic name
        while (*medNamePtr) {
            char* tempMed = medNamePtr;
            char* tempSearch = searchLower;
            bool matchFound = true;

            while (*tempSearch && matchFound) {
                if (*tempMed != *tempSearch) {
                    matchFound = false;
                }
                tempMed++;
                tempSearch++;
            }

            if (matchFound && *tempSearch == '\0') {
                isPartialMatch = true;
                break;
            }
            medNamePtr++;
        }

        if (!isPartialMatch) {
            while (*genNamePtr) {
                char* tempGen = genNamePtr;
                char* tempSearch = searchLower;
                bool matchFound = true;

                while (*tempSearch && matchFound) {
                    if (*tempGen != *tempSearch) {
                        matchFound = false;
                    }
                    tempGen++;
                    tempSearch++;
                }

                if (matchFound && *tempSearch == '\0') {
                    isPartialMatch = true;
                    break;
                }
                genNamePtr++;
            }
        }

        if (isPartialMatch || myStrcmp(medicineName, searchLower) == 0 || myStrcmp(genericName, searchLower) == 0) {
            current->data.display();
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        setTextColorLightViolet();
cout << "| No medicines found matching '" << searchTerm << "' |" << endl;
resetTextColor();
    }

    printFooter();
}

void Pharmacy::swap(Node* a, Node* b) {
    Medicine temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void Pharmacy::sortMedicines(int sortBy, bool ascending) {
    if (!head || !head->next) return;

    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {
            bool condition = false;
            switch (sortBy) {
                case 1:
                    condition = (ascending && myStrcmp(i->data.getName(), j->data.getName()) > 0) ||
                                (!ascending && myStrcmp(i->data.getName(), j->data.getName()) < 0);
                    break;
                case 2:
                    condition = (ascending && myStrcmp(i->data.getGenericName(), j->data.getGenericName()) > 0) ||
                                (!ascending && myStrcmp(i->data.getGenericName(), j->data.getGenericName()) < 0);
                    break;
                case 3:
                    condition = (ascending && i->data.compareExpiryDate(j->data.getExpiryDate()) > 0) ||
                                (!ascending && i->data.compareExpiryDate(j->data.getExpiryDate()) < 0);
                    break;
                case 4:
                    condition = (ascending && i->data.getQuantity() > j->data.getQuantity()) ||
                                (!ascending && i->data.getQuantity() < j->data.getQuantity());
                    break;
            }
            if (condition) {
                swap(i, j);
            }
        }
    }
}

void Pharmacy::filterByQuantity(int minQty, int maxQty) {
    printHeader();
    Node* current = head;
    bool found = false;
    while (current) {
        if (current->data.getQuantity() >= minQty && current->data.getQuantity() <= maxQty) {
            current->data.display();
            found = true;
        }
        current = current->next;
    }
    if (!found) {
        setTextColorLightViolet();
cout << "| No medicines found within the specified quantity range |" << endl;
resetTextColor();
    }
    printFooter();
}

void Pharmacy::addMedicineToFile(const char* filename) {
    char name[50], genericName[50], supplier[50], batchID[20], expiryDate[15];
    float price;
    int quantity;

    cout << "Enter medicine name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Enter generic name: ";
    cin.getline(genericName, 50);
    cout << "Enter supplier: ";
    cin.getline(supplier, 50);
    cout << "Enter batch ID: ";
    cin.getline(batchID, 20);
    cout << "Enter price: ";
    cin >> price;
    cout << "Enter quantity: ";
    cin >> quantity;

    bool validDate = false;
    while (!validDate) {
        cout << "Enter expiry date (YYYY-MM-DD): ";
        cin >> expiryDate;

        // Check date format
        if (strlen(expiryDate) != 10 || 
            expiryDate[4] != '-' || 
            expiryDate[7] != '-' ||
            !isdigit(expiryDate[0]) || !isdigit(expiryDate[1]) || !isdigit(expiryDate[2]) || !isdigit(expiryDate[3]) ||
            !isdigit(expiryDate[5]) || !isdigit(expiryDate[6]) ||
            !isdigit(expiryDate[8]) || !isdigit(expiryDate[9])) {
            setTextColorLightViolet();
cout << "Invalid date format! Please use YYYY-MM-DD format.\n";
resetTextColor();
        } else {
            validDate = true;
        }
    }

    FILE* file = fopen(filename, "a");
    if (!file) {
        setTextColorLightViolet();
cout << "Error opening file for writing!" << endl;
resetTextColor();
        return;
    }
    fprintf(file, "%s %s %s %s %.2f %d %s\n", name, genericName, supplier, batchID, price, quantity, expiryDate);
    fclose(file);

    Medicine newMedicine(name, genericName, supplier, batchID, price, quantity, expiryDate);
    addMedicine(newMedicine);
    
    setTextColorLightViolet();
cout << "Medicine added successfully!" << endl;
resetTextColor();
}

void Pharmacy::updateMedicine(const char* filename) {
    cout << "Choose what to update (1: Price, 2: Quantity): ";
    int updateChoice;
    cin >> updateChoice;

    if (updateChoice != 1 && updateChoice != 2) {
        setTextColorLightViolet();
cout << "Invalid choice!" << endl;
resetTextColor();
        return;
    }

    cout << "Enter the name of the medicine to update: ";
    char medName[50];
    cin.ignore();
    cin.getline(medName, 50);
    cout << "Enter the batch ID: ";
    char batchID[20];
    cin.getline(batchID, 20);
    trim(medName);
    toLowerCase(medName);
   
    FILE* tempFile = fopen("temp_medicine_data.txt", "w");
    if (!tempFile) {
        setTextColorLightViolet();
cout << "Error opening temporary file for writing!" << endl;
resetTextColor();
        return;
    }

    bool found = false;
    Node* current = head;
    while (current) {
        char currentName[50], currentBatch[20];
        myStrcpy(currentName, current->data.getName());
        myStrcpy(currentBatch, current->data.getBatchID());
        trim(currentName);
        toLowerCase(currentName);

        if (myStrcmp(currentName, medName) == 0 && myStrcmp(currentBatch, batchID) == 0) {
            found = true;
            if (updateChoice == 1) {
                cout << "Enter the new price: ";
                float newPrice;
                cin >> newPrice;
                current->data.setPrice(newPrice);
            } else if (updateChoice == 2) {
                cout << "Enter the new quantity: ";
                int newQuantity;
                cin >> newQuantity;
                current->data.setQuantity(newQuantity);
            }
        }

        fprintf(tempFile, "%s %s %s %s %.2f %d %s\n",
                current->data.getName(),
                current->data.getGenericName(),
                current->data.getSupplier(),
                current->data.getBatchID(),
                current->data.getPrice(),
                current->data.getQuantity(),
                current->data.getExpiryDate());

        current = current->next;
    }
    fclose(tempFile);

    remove(filename);
    rename("temp_medicine_data.txt", filename);

    if (found) {
        setTextColorLightViolet();
cout << "Medicine '" << medName << "' with batch ID '" << batchID << "' updated successfully!" << endl;
resetTextColor();
    } else {
        setTextColorLightViolet();
cout << "Medicine '" << medName << "' with batch ID '" << batchID << "' not found!" << endl;
resetTextColor();
    }
}

void Pharmacy::searchBySupplier() {
    char searchTerm[50];
    cout << "Enter the supplier name to search: ";
    cin.ignore();
    cin.getline(searchTerm, 50);

    char searchLower[50];
    myStrcpy(searchLower, searchTerm);
    trim(searchLower);
    toLowerCase(searchLower);

    bool found = false;
    printHeader();

    Node* current = head;
    while (current) {
        char supplierName[50];
        myStrcpy(supplierName, current->data.getSupplier());
        toLowerCase(supplierName);
        trim(supplierName);

        if (myStrcmp(supplierName, searchLower) == 0) {
            current->data.display();
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        setTextColorLightViolet();
cout << "| No medicines found matching supplier '" << searchTerm << "' |" << endl;
resetTextColor();
    }

    printFooter();
}

Medicine* Pharmacy::findMedicine(const char* name, const char* batchID) {
    Node* current = head;
    while (current) {
        if (myStrcmp(current->data.getName(), name) == 0 &&
            myStrcmp(current->data.getBatchID(), batchID) == 0) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

void Pharmacy::updateMedicineQuantity(const char* name, const char* batchID, int quantityChange) {
    Node* current = head;
    while (current) {
        if (myStrcmp(current->data.getName(), name) == 0 &&
            myStrcmp(current->data.getBatchID(), batchID) == 0) {
            int newQuantity = current->data.getQuantity() + quantityChange;
            current->data.setQuantity(newQuantity);
            return;
        }
        current = current->next;
    }
}

void Pharmacy::deleteMedicineFromList(const char* name, const char* batchID) {
    if (!head) return;

    // If the medicine to delete is the head
    if (myStrcmp(head->data.getName(), name) == 0 &&
        myStrcmp(head->data.getBatchID(), batchID) == 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
        medicineCount--;
        return;
    }

    // Search for the medicine in the rest of the list
    Node* current = head;
    while (current->next) {
        if (myStrcmp(current->next->data.getName(), name) == 0 &&
            myStrcmp(current->next->data.getBatchID(), batchID) == 0) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            medicineCount--;
            return;
        }
        current = current->next;
    }
}

void Pharmacy::deleteMedicine(const char* filename) {
    cout << "\nCurrent Medicine List:\n";
    displayAllMedicines();

    cout << "\nEnter the name of the medicine to delete: ";
    char medName[50];
    cin.ignore();
    cin.getline(medName, 50);
    cout << "Enter the batch ID: ";
    char batchID[20];
    cin.getline(batchID, 20);

    // First, check if the medicine exists
    Medicine* med = findMedicine(medName, batchID);
    if (!med) {
        setTextColorLightViolet();
cout << "Medicine not found!" << endl;
resetTextColor();
        return;
    }

    // Delete from linked list
    deleteMedicineFromList(medName, batchID);

    // Update the file
    saveToFile(filename);

    setTextColorLightViolet();
cout << "Medicine deleted successfully!" << endl;
resetTextColor();
}

void Pharmacy::saveToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        setTextColorLightViolet();
cout << "Error opening file for writing!" << endl;
resetTextColor();
        return;
    }

    Node* current = head;
    while (current) {
        fprintf(file, "%s %s %s %s %.2f %d %s\n",
                current->data.getName(),
                current->data.getGenericName(),
                current->data.getSupplier(),
                current->data.getBatchID(),
                current->data.getPrice(),
                current->data.getQuantity(),
                current->data.getExpiryDate());
        current = current->next;
    }
    fclose(file);
}

void Pharmacy::checkAndDisplayNotifications() {
    Node* current = head;
    Medicine* medicines = new Medicine[medicineCount];
    int index = 0;
    
    while (current) {
        medicines[index++] = current->data;
        current = current->next;
    }
    
    notificationManager.clearNotifications();
    notificationManager.checkExpiryDates(medicines, medicineCount);
    notificationManager.checkLowStock(medicines, medicineCount);
    notificationManager.displayNotifications();
    
    delete[] medicines;
}

int Pharmacy::countPendingNotifications() {
    Medicine* medicines = new Medicine[medicineCount];
    int index = 0;
    
    Node* current = head;
    while (current) {
        medicines[index++] = current->data;
        current = current->next;
    }
    
    int count = notificationManager.countPendingNotifications(medicines, medicineCount);
    delete[] medicines;
    return count;
}