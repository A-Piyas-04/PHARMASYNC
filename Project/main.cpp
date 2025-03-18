#include "pharmacy.h"
#include "cart.h"
#include "transaction.h"
#include <iostream>

using namespace std;

int main() {
    Pharmacy pharmacy;
    pharmacy.loadData("medicine_data.txt");
    Cart cart;

    int mainChoice;

    while (true) {
        // Display the title and main menu
        cout << "\n\n";
        cout << "\n==============================\n";
        setTextColorCyan();
cout << "   Welcome to PHARMASYNC\n";
resetTextColor();
        cout << "==============================\n\n";
        cout << "1. Medicine query\n";
        cout << "2. Manage Stock\n";
        cout << "3. Sell Medicine\n";
        cout << "4. View Notifications (" << pharmacy.countPendingNotifications() << ")\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        if (mainChoice == 1) {
            // View Medicine Menu
            int viewChoice;
            
            setTextColorCyan();
            cout << "\n--- View Medicine ---\n";
            resetTextColor();
            cout << "1. View All Medicines\n";
            cout << "2. Search Medicine\n";
            cout << "3. Sort Medicines\n";
            cout << "4. Filter Medicines\n";
            cout << "5. Go Back\n";
            cout << "Enter your choice: ";
            cin >> viewChoice;

            if (viewChoice == 1) {
                pharmacy.displayAllMedicines();
            } else if (viewChoice == 2) {
                pharmacy.searchMedicine();
            } else if (viewChoice == 3) {
                cout << "\nSort Options:\n";
                cout << "1. By Name\n";
                cout << "2. By Generic Name\n";
                cout << "3. By Expiry Date\n";
                cout << "4. By Quantity\n";
                cout << "Enter the number corresponding to your sort choice: ";

                int sortOption;
                cin >> sortOption;

                cout << "Choose sort order (1 for Ascending, 0 for Descending): ";
                bool ascending;
                cin >> ascending;

                pharmacy.sortMedicines(sortOption, ascending);
                cout << "\nSorted Medicines:\n";
                pharmacy.displayAllMedicines();

            } else if (viewChoice == 4) {
                int filterChoice;
                
                setTextColorCyan();
                cout << "\n--- Filter Options ---\n";
                resetTextColor();
                cout << "1. Filter by Quantity\n";
                cout << "2. Filter by Supplier\n";
                cout << "Enter your choice: ";
                cin >> filterChoice;

                if (filterChoice == 1) {
                    cout << "\nEnter the lower bound of quantity: ";
                    int lowerBound;
                    cin >> lowerBound;

                    cout << "Enter the upper bound of quantity: ";
                    int upperBound;
                    cin >> upperBound;

                    cout << "\nMedicines with quantity between " << lowerBound << " and " << upperBound << ":\n";
                    pharmacy.filterByQuantity(lowerBound, upperBound);

                } else if (filterChoice == 2) {
                    pharmacy.searchBySupplier();
                } else {
                    setTextColorLightViolet();
cout << "Invalid filter choice. Please try again.\n";
resetTextColor();
                }
            } else if (viewChoice == 5) {
                continue;
            } else {
                setTextColorLightViolet();
cout << "Invalid choice. Please try again.\n";
resetTextColor();
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
                    
                    setTextColorCyan();
                    cout << "Adding a new medicine:\n";
                    resetTextColor();
                    pharmacy.addMedicineToFile("medicine_data.txt");
                    cout << "\nUpdated Medicines:\n";
                    pharmacy.displayAllMedicines();
                } else if (stockChoice == 2) {
                 
                    setTextColorCyan();
                    cout << "Update a medicine:\n";
                    resetTextColor();
                    pharmacy.updateMedicine("medicine_data.txt");
                } else if (stockChoice == 3) {
                    
                    setTextColorCyan();
                    cout << "Delete a medicine:\n";
                    resetTextColor();
                    pharmacy.deleteMedicine("medicine_data.txt");
                } else if (stockChoice == 4) {
                    break;
                } else {
                    setTextColorLightViolet();
cout << "Invalid choice. Please try again.\n";
resetTextColor();
                }
            }

        } else if (mainChoice == 3) {
            // Sell Medicine Menu
            while (true) {
                cout << "\n--- Sell Medicine ---\n";
                cout << "1. Add Medicine to Cart\n";
                cout << "2. View Cart\n";
                cout << "3. Checkout\n";
                cout << "4. Empty Cart\n";
                cout << "5. View Selling History\n";
                cout << "6. Go Back\n";
                cout << "Enter your choice: ";
                int sellChoice;
                cin >> sellChoice;

                if (sellChoice == 1) {
                    pharmacy.displayAllMedicines();
                    cout << "\nEnter the name of the medicine to add to cart: ";
                    char medName[50];
                    cin.ignore();
                    cin.getline(medName, 50);
                    cout << "Enter the batch ID: ";
                    char batchID[20];
                    cin.getline(batchID, 20);
                    cout << "Enter quantity: ";
                    int quantity;
                    cin >> quantity;

                    // Find the medicine and add to cart
                    Medicine* med = pharmacy.findMedicine(medName, batchID);
                    if (med != nullptr) {
                        cart.addItem(*med, quantity);
                        if (quantity <= med->getQuantity()) {
                            setTextColorLightViolet();
cout << "Medicine added to cart successfully!\n";
resetTextColor();
                        }
                    } else {
                        setTextColorLightViolet();
cout << "Medicine not found!\n";
resetTextColor();
                    }
                } else if (sellChoice == 2) {
                    cart.displayCart();
                } else if (sellChoice == 3) {
                    if (cart.getTotal() > 0) {
                        cart.printReceipt();
                        // Get current date
                        char currentDate[11];
                        time_t now = time(0);
                        strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", localtime(&now));
                        // Record transaction
                        Transaction::recordTransaction(cart, currentDate);
                        // Update stock
                        for (const CartItem& item : cart.getItems()) {
                            pharmacy.updateMedicineQuantity(item.medicine.getName(), 
                                                          item.medicine.getBatchID(), 
                                                          -item.quantity);
                        }
                        pharmacy.saveToFile("medicine_data.txt");
                        cart.clear();
                        cout << "\nThank you for your purchase!\n";
                    } else {
                        setTextColorLightViolet();
cout << "Cart is empty!\n";
resetTextColor();
                    }
                } else if (sellChoice == 4) {
                    if (cart.getTotal() > 0) {
                        cart.clear();
                        setTextColorLightViolet();
cout << "Cart has been emptied successfully!\n";
resetTextColor();
                    } else {
                        setTextColorLightViolet();
cout << "Cart is already empty!\n";
resetTextColor();
                    }
                } else if (sellChoice == 5) {
                    Transaction::displayTransactionHistory();
                    cout << "\nPress Enter to continue...";
                    cin.ignore();
                    cin.get();
                } else if (sellChoice == 6) {
                    break;
                } else if (sellChoice > 6) {
                    setTextColorLightViolet();
cout << "Invalid choice. Please try again.\n";
resetTextColor();
                }
            }
        } else if (mainChoice == 4) {
            pharmacy.checkAndDisplayNotifications();
            cin.ignore(); // Clear any remaining newline characters
        } else if (mainChoice == 5) {
            cout << "Thank you for using PHARMASYNC\n";
            break;
        } else {
            setTextColorLightViolet();
cout << "Invalid choice. Please try again.\n";
resetTextColor();
        }
    }

    return 0;
}