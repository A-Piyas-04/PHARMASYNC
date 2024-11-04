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
    void setPrice(float newPrice) { price = newPrice; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }

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

void searchMedicine() {
    // Ask for user input
    char searchTerm[50];
    cout << "Enter the name or generic name of the medicine to search: ";
    cin.ignore(); // To handle any leftover newline character in the buffer
    cin.getline(searchTerm, 50); // Read the input

    // Process the input: convert to lowercase and trim
    char searchLower[50];
    myStrcpy(searchLower, searchTerm);
    trim(searchLower);
    toLowerCase(searchLower);

    bool found = false;
    printHeader();

    // Traverse the linked list and search
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


 void updateMedicine(const char* filename) {
    cout << "Choose what to update (1: Price, 2: Quantity): ";
    int updateChoice;
    cin >> updateChoice;

    if (updateChoice != 1 && updateChoice != 2) {
        cout << "Invalid choice!" << endl;
        return;
    }

    cout << "Enter the name of the medicine to update: ";
    char medName[50];
    cin.ignore(); // Clear the buffer
    cin.getline(medName, 50);
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
        char currentName[50];
        myStrcpy(currentName, current->data.getName());
        trim(currentName);
        toLowerCase(currentName);

        if (myStrcmp(currentName, medName) == 0) {
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

        // Write the updated or unchanged medicine to the temp file
        fprintf(tempFile, "%s %s %s %.2f %d %s\n",
                current->data.getName(),
                current->data.getGenericName(),
                current->data.getSupplier(),
                current->data.getPrice(),
                current->data.getQuantity(),
                current->data.getExpiryDate());

        current = current->next;
    }
    fclose(tempFile);

    // Replace the original file with the updated temp file
    remove(filename);
    rename("temp_medicine_data.txt", filename);

    if (found) {
        cout << "Medicine '" << medName << "' updated successfully!" << endl;

        // clearMedicines(); // Clear and reload the data to reflect updates
        // loadData(filename);
        // searchMedicine(medName); // Display only the updated medicine
    } else {
        cout << "Medicine '" << medName << "' not found!" << endl;
    }
}




};

int main() {
    Pharmacy pharmacy;
    pharmacy.loadData("medicine_data.txt");

    int mainChoice;

    while (true) {
        // Display the title and main menu
        cout << "\n==============================\n";
        cout << "   Welcome to PHARMASYNC\n";
        cout << "==============================\n\n";
        cout << "1. View Medicine\n";
        cout << "2. Stock Manipulation\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        if (mainChoice == 1) {
            // View Medicine Menu
            int viewChoice;
            cout << "\n--- View Medicine ---\n";
            cout << "1. View All Medicines\n";
            cout << "2. Search Medicine\n";
            cout << "3. Sort Medicines\n";
            cout << "4. Filter By Quantity\n";
            cout << "5. Go Back\n";
            cout << "Enter your choice: ";
            cin >> viewChoice;

            if(viewChoice == 1){  
                 pharmacy.displayAllMedicines();
            }else if (viewChoice == 2) {
                pharmacy.searchMedicine();
            } else if (viewChoice == 3) {

    
                cout << "\nSort Options:" << endl;
                cout << "1. By Name" << endl;
                cout << "2. By Generic Name" << endl;
                cout << "3. By Expiry Date" << endl;
                cout << "4. By Quantity" << endl;
                cout << "Enter the number corresponding to your sort choice: ";
                
                int sortOption;
                cin >> sortOption;
                
                cout << "Choose sort order (1 for Ascending, 0 for Descending): ";
                bool ascending;
                cin >> ascending;
                
                // Call the sortMedicines function
                pharmacy.sortMedicines(sortOption, ascending);
                
                // Display sorted medicines
                cout << "\nSorted Medicines:" << endl;
                pharmacy.displayAllMedicines();



            } else if (viewChoice == 4) {
                cout << "\nEnter the lower bound of quantity: ";
                int lowerBound;
                cin >> lowerBound;

                cout << "Enter the upper bound of quantity: ";
                int upperBound;
                cin >> upperBound;

                cout << "\nMedicines with quantity between " << lowerBound << " and " << upperBound << ":\n";
                pharmacy.filterByQuantity(lowerBound, upperBound);

            } else if (viewChoice == 5) {
                continue; // Go back to the main menu
            } else {
                cout << "Invalid choice. Please try again.\n";
            }

        } else if (mainChoice == 2) {
            // Stock Manipulation Menu
            while (true) {
                cout << "\n--- Stock Manipulation ---\n";
                cout << "1. Add a medicine\n";
                cout << "2. Update a medicine\n";
                cout << "3. Delete a medicine\n";
                cout << "4. Go Back\n";
                cout << "Enter your choice: ";
                int stockChoice;
                cin >> stockChoice;

                if (stockChoice == 1) {
                    cout << "Adding a new medicine:\n";
                    pharmacy.addMedicineToFile("medicine_data.txt");
                    cout << "\nUpdated Medicines:\n";
                    pharmacy.displayAllMedicines();
                } else if (stockChoice == 2) {
                    cout << "Update a medicine:\n";
                    pharmacy.updateMedicine("medicine_data.txt");
                } else if (stockChoice == 3) {
                    cout << "Enter the name of the medicine to delete: ";
                    char medName[50];
                    cin.ignore(); 
                    cin.getline(medName, 50);
                    pharmacy.deleteMedicine(medName);
                    cout << "\nUpdated Medicines:\n";
                    pharmacy.displayAllMedicines();
                } else if (stockChoice == 4) {
                    break; // Go back to the main menu
                } else {
                    cout << "Invalid choice. Please try again.\n";
                }
            }

        } else if (mainChoice == 3) {
            cout << "Exiting PHARMASYNC. Goodbye!\n";
            break; // Exit the program
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}