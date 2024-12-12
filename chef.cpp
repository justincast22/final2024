#include "chef.h"
#include <iostream>

using namespace std;

/**
 * External instance of OrderManager to manage restaurant orders.
 */
extern OrderManager ordermanager;

/**
 * Displays the main menu for the chef, allowing them to manage orders.
 * The chef can view, process, and update the status of orders.
 */
void chef::processOrders() {
    int choice;
    do {
        /** Display the Chef Menu options. */
        cout << "\nChef Menu:" << endl;
        cout << "1. View Pending Orders" << endl;
        cout << "2. Get Next Order to Cook" << endl;
        cout << "3. Mark Current Order as Complete" << endl;
        cout << "4. Cancel Order" << endl;
        cout << "5. Mark Pickup Orders" << endl;
        cout << "6. Mark Order as Picked Up" << endl;
        cout << "7. Mark Order as Served" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        /** Handle user input and call the appropriate function based on the selected choice. */
        switch (choice) {
            case 1:
                viewPendingOrders();
                break;
            case 2:
                ordermanager.getNextOrder();
                break;
            case 3:
                markOrderComplete();
                break;
            case 4:
                ordermanager.cancelOrder();
                break;
            case 5:
                ordermanager.markPickedUp();
                break;
            case 6:
                ordermanager.markOrderForPickup();
                break;
            case 7:
                ordermanager.markServed();
                break;
            case 8:
                /** Exit the Chef Menu. */
                cout << "Exiting Chef Menu.\n";
                break;
            default:
                /** Handle invalid input by prompting the user to try again. */
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);
}

/**
 * Displays a list of all pending orders for the chef to review.
 */
void chef::viewPendingOrders() {
    ordermanager.viewPendingOrders();
}

/**
 * Allows the chef to mark a selected order as complete.
 */
void chef::markOrderComplete() {
    ordermanager.markOrderComplete();
}

/**
 * Enables the chef to prioritize orders based on their urgency.
 */
void chef::prioritizeOrders() {
    ordermanager.prioritizeOrders();
}
