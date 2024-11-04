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

void intToStr(int num, char* str, int width) {
    int i = 0, temp = num;
    char tempStr[50];
    
    do {
        tempStr[i++] = (temp % 10) + '0';
        temp /= 10;
    } while (temp > 0);
    
    int j = 0;
    while (i > 0) {
        str[j++] = tempStr[--i];
    }
    
    while (j < width) {
        str[j++] = ' ';
    }
    str[j] = '\0';
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
    const char* getSupplier() { return supplier; }
    const char* getExpiryDate() { return expiryDate; }
    float getPrice() { return price; }
    int getQuantity() { return quantity; }

    void display() {
        char namePad[50], genericNamePad[50], supplierPad[50], priceStr[10], quantityStr[10];
        padString(name, 15);
        padString(genericName, 15);
        padString(supplier, 20);
        intToStr(price, priceStr, 8);
        intToStr(quantity, quantityStr, 9);
        padString(expiryDate, 12);
        cout << "| " << name << "| " << genericName << "| " << supplier << "| " << priceStr << "| " << quantityStr << "| " << expiryDate << "|" << endl;
    }



int compareExpiryDate(const string& otherExpiryDate) const {

    if (expiryDate == otherExpiryDate) {
        return 0;
    }
    return (expiryDate > otherExpiryDate) ? 1 : -1;
}

    
};

struct Node {
    Medicine data;
    Node* next;
    Node(Medicine med) : data(med), next(nullptr) {}
};

class Pharmacy {
private:
    Node* head;
    int medicineCount;

public:
    Pharmacy() : head(nullptr), medicineCount(0) {}

    ~Pharmacy() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
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
            Medicine med(name, genericName, supplier, price, quantity, expiryDate);
            addMedicine(med);
        }
        fclose(file);
    }

    void addMedicine(const Medicine& med) {
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

    void printHeader() {
        cout << "+----------------+----------------+---------------------+----------+----------+-------------+" << endl;
        cout << "| Name           | Generic Name   | Supplier            | Price    | Quantity | Expiry Date |" << endl;
        cout << "+----------------+----------------+---------------------+----------+----------+-------------+" << endl;
    }

    void printFooter() {
        cout << "+----------------+----------------+---------------------+----------+----------+-------------+" << endl;
    }



    void displayAllMedicines() {
    printHeader();
    Node* current = head;
    while (current) {
        current->data.display();
        current = current->next;
    }
    printFooter();
}

    void searchMedicine(const char* searchTerm) {
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
    

void swap(Node* a, Node* b) {
    Medicine temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void sortMedicines(int sortBy, bool ascending) {
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


void filterByQuantity(int minQty, int maxQty) {
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

void addMedicineToFile(const char* filename) {
        // Prompt for medicine details
        char name[50], genericName[50], supplier[50], expiryDate[15];
        float price;
        int quantity;

        cout << "Enter medicine name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter generic name: ";
        cin.getline(genericName, 50);
        cout << "Enter supplier: ";
        cin.getline(supplier, 50);
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter quantity: ";
        cin >> quantity;
        cout << "Enter expiry date (YYYY-MM-DD): ";
        cin >> expiryDate;

        // Append the new medicine information to the file
        FILE* file = fopen(filename, "a");
        if (!file) {
            cout << "Error opening file for writing!" << endl;
            return;
        }
        fprintf(file, "%s %s %s %.2f %d %s\n", name, genericName, supplier, price, quantity, expiryDate);
        fclose(file);

        // Add the new medicine to the in-memory list as well
        Medicine newMedicine(name, genericName, supplier, price, quantity, expiryDate);
        addMedicine(newMedicine);
        
        cout << "Medicine added successfully!" << endl;
    }


void clearMedicines() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr; // Reset head to nullptr
    medicineCount = 0; // Reset medicine count
}

void deleteMedicine(const char* medicineName) {
    
    Node* current = head;

   
    FILE* tempFile = fopen("temp_medicine_data.txt", "w");
    if (!tempFile) {
        cout << "Error opening temporary file for writing!" << endl;
        return;
    }


    char normalizedInput[50];
    myStrcpy(normalizedInput, medicineName);
    trim(normalizedInput);
    toLowerCase(normalizedInput);
   
    bool found = false;

 
    while (current) {
       
        char currentName[50];
        myStrcpy(currentName, current->data.getName());
        trim(currentName);
        toLowerCase(currentName);

        
        if (myStrcmp(currentName, normalizedInput) != 0) {
            
            fprintf(tempFile, "%s %s %s %.2f %d %s\n",
                current->data.getName(),
                current->data.getGenericName(),
                current->data.getSupplier(),
                current->data.getPrice(),
                current->data.getQuantity(),
                current->data.getExpiryDate());
        } else {
            found = true; 
        }
        current = current->next;
     }

    fclose(tempFile);

    remove("medicine_data.txt");
    rename("temp_medicine_data.txt", "medicine_data.txt");

     if (found) {
         cout << "Medicine '" << medicineName << "' deleted successfully!" << endl;

         
         clearMedicines();

         
         loadData("medicine_data.txt");
     } else {
         cout << "Medicine '" << medicineName << "' not found!" << endl;
     }
 }



};

int main() {
    Pharmacy pharmacy;
    pharmacy.loadData("medicine_data.txt");

    cout << "\nAll Medicines:\n";
    pharmacy.displayAllMedicines();


    cout << "\nSearch Results for 'Paracetamol':\n";
    pharmacy.searchMedicine("Paracetamol");

    cout << "\nSearch Results for 'Amoxicillin':\n";
    pharmacy.searchMedicine("Amoxicillin");

    cout << "\nSearch Results for 'Exium':\n";
    pharmacy.searchMedicine("Exium");


    cout << "\nMedicines sorted by Name (Ascending):\n";
    pharmacy.sortMedicines(1, true);
    pharmacy.displayAllMedicines();

    cout << "\nMedicines sorted by Expiry Date (Ascending):\n";
    pharmacy.sortMedicines(3, true);
    pharmacy.displayAllMedicines();

    cout << "\nMedicines sorted by Quantity (Descending):\n";
    pharmacy.sortMedicines(4, false);
    pharmacy.displayAllMedicines();

    cout << "\nMedicines with quantity between 50 and 150:\n";
    pharmacy.filterByQuantity(50, 150);



    

    while(1){
    cout << "\n**\n**\n**\n";
    cout << "1. Add a medicine" << endl;
    cout << "2. Delete a medicine" << endl;
    cout << "3. Exit" << endl;
    cout << "Choose: ";
    
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Adding a new medicine:" << endl;

        pharmacy.addMedicineToFile("medicine_data.txt");

        cout << "Updated Medicines:" << endl;
        pharmacy.displayAllMedicines();


    }
     else if (choice == 2) {
        cout << "Enter the name of the medicine to delete: ";
        char medName[50];
        cin.ignore(); // Clear the buffer
        cin.getline(medName, 50);

        pharmacy.deleteMedicine(medName);
        cout << "\nUpdated Medicines:\n";
        pharmacy.displayAllMedicines();

    } 
    else {
        break;
    }
   
  }

    system("pause");
    
    return 0;
}