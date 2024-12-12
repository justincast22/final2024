#include "role.h"
#include "menu.h"
#include "order.h"
#include "chef.h"
#include <iostream>

using namespace std;

/**
 * Handles user role selection and provides role-specific functionality.
 * Users can choose to act as either a customer or a chef.
 */
void role::askRole() {
    /** Create instances of menu, order, and chef for role-specific operations. */
    menu restaurantMenu;
    order customerOrder;
    chef restaurantChef;

    int roleInput;

    /** Prompt the user to select their role. */
    cout << "Are you a customer (1) or a chef (2)? ";

    /** Input validation loop to ensure correct role selection. */
    while (true) {
        if (cin >> roleInput && (roleInput == 1 || roleInput == 2)) {
            break;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter 1 for Customer or 2 for Chef: ";
    }

    /** Handle the role-specific logic. */
    if (roleInput == 1) {
        /** Customer role: Display the menu, take the order, and save it. */
        restaurantMenu.showMenu();
        customerOrder.placeOrder();
        customerOrder.saveState();
    } else {
        /** Chef role: Load existing orders and process them. */
        customerOrder.loadState();
        restaurantChef.processOrders();
    }
}
