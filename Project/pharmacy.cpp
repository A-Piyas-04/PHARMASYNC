#include "pharmacy.h"
#include <iostream>

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
        cout << "Error opening file!" << endl;
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

        if (myStrcmp(medicineName, searchLower) == 0 || myStrcmp(genericName, searchLower) == 0) {
            current->data.display();
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "| No medicines found matching '" << searchTerm << "' |" << endl;
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
        cout << "| No medicines found within the specified quantity range |" << endl;
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
    cout << "Enter expiry date (YYYY-MM-DD): ";
    cin >> expiryDate;

    FILE* file = fopen(filename, "a");
    if (!file) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    fprintf(file, "%s %s %s %s %.2f %d %s\n", name, genericName, supplier, batchID, price, quantity, expiryDate);
    fclose(file);

    Medicine newMedicine(name, genericName, supplier, batchID, price, quantity, expiryDate);
    addMedicine(newMedicine);
    
    cout << "Medicine added successfully!" << endl;
}

void Pharmacy::updateMedicine(const char* filename) {
    cout << "Choose what to update (1: Price, 2: Quantity): ";
    int updateChoice;
    cin >> updateChoice;

    if (updateChoice != 1 && updateChoice != 2) {
        cout << "Invalid choice!" << endl;
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
        cout << "Error opening temporary file for writing!" << endl;
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
        cout << "Medicine '" << medName << "' with batch ID '" << batchID << "' updated successfully!" << endl;
    } else {
        cout << "Medicine '" << medName << "' with batch ID '" << batchID << "' not found!" << endl;
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
        cout << "| No medicines found matching supplier '" << searchTerm << "' |" << endl;
    }

    printFooter();
}