#include "order.h"
#include "menu.h"
#include "OrderManager.h"
#include <iostream>
#include <fstream>
#include "receipt.h"

/**
 * External instance of OrderManager to manage restaurant orders.
 */
extern OrderManager ordermanager;

/**
 * Handles the process of placing an order, including item selection,
 * method selection, and order submission.
 */
void order::placeOrder() {
    menu menu;
    receipt receipt;
    while (true) {
        int itemChoice;

        /** Clear any previous order for a fresh start. */
        userOrder.clear();
        cout << "Starting a new order.\n";

        /** Ordering loop for item selection. */
        while (true) {
            cout << "Enter the number of the item you want to order (0 to finish): ";
            while (!(cin >> itemChoice) || itemChoice < 0 || itemChoice > menu::items.size()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a valid item number (0 to finish): ";
            }

            /** Exit the loop if the user chooses to finish the order. */
            if (itemChoice == 0) {
                if (!userOrder.empty()) {
                    allOrders.push_back(userOrder); // Save the order
                }
                break;
            }

            /** Add the selected item to the current order. */
            userOrder.push_back(menu::items[itemChoice - 1]);
            cout << menu::items[itemChoice - 1] << " added to your order.\n";
        }

        /** Display delivery method options and prompt the user to select one. */
        cout << "\nAvailable Methods:\n";
        cout << "1. Drive-Through\n";
        cout << "2. Onsite\n";
        cout << "3. Phone\n";
        cout << "4. Doordash\n";

        int methodChoice;
        cout << "Enter the number corresponding to your method of choice: ";
        while (!(cin >> methodChoice) || methodChoice < 1 || methodChoice > 4) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a valid method number: ";
        }

        /** Assign the selected method to the order. */
        switch (methodChoice) {
            case 1: userMethod = "Drive-Through"; break;
            case 2: userMethod = "Onsite"; break;
            case 3: userMethod = "Phone"; break;
            case 4: userMethod = "Doordash"; break;
        }

        cout << "You selected " << userMethod << " as your order method.\n";

        /** Assign priority based on the selected method and add the order to the manager. */
        int priority;
        if (userMethod == "Drive-Through") priority = 4;
        else if (userMethod == "Onsite") priority = 3;
        else if (userMethod == "Phone") priority = 2;
        else priority = 1;

        ordermanager.addOrder(userOrder, userMethod, priority);

        /** Display the summary of the current order. */
        cout << "\nYour order summary:\n";
        for (const auto& item : userOrder) {
            cout << "- " << item << endl;
        }
        cout << "Method: " << userMethod << endl;

        receipt.showReceipt(*this, menu);

        /** Prompt the user to decide whether to start a new order. */
        char choice;
        cout << "\nWould you like to start a new order? (y/n): ";
        while (!(cin >> choice) || (choice != 'y' && choice != 'n')) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter 'y' for yes or 'n' for no: ";
        }

        if (choice == 'y') {
            menu.showMenu();
        }

        if (choice == 'n') {
            cout << "Thank you for your orders! Exiting...\n";
            break;
        }
    }
}

/**
 * Saves the current state of orders using the OrderManager.
 */
void order::saveState() const {
    ordermanager.saveState();
}

/**
 * Loads the state of orders using the OrderManager.
 */
void order::loadState() {
    ordermanager.loadState();
}

/**
 * Calculates the total cost of the current order based on the menu prices.
 */
double order::calculateTotal(const menu& menu) const {
    double total = 0.0;
    for (const string& item : userOrder) {
        total += menu.getPrice(item);
    }
    return total;
}

/**
 * Retrieves the user's current order as a vector of items.
 */
const vector<string>& order::getUserOrder() const {
    return userOrder;
}

/**
 * Retrieves the delivery or dining method selected by the user.
 */
const string& order::getUserMethod() const {
    return userMethod;
}
