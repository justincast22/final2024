#include "receipt.h"
#include "order.h"
#include "menu.h"
#include <iostream>

using namespace std;

/**
 * Displays the receipt for a specified order, showing itemized details and the total cost.
 * If the order method is DoorDash, a 5% upcharge is applied to the total.
 */
void receipt::showReceipt(const order& order, const menu& menu) const {
    /** Display the summary of items in the order. */
    cout << "Your order summary:\n";
    for (const string& item : order.getUserOrder()) {
        cout << "- " << item << " - $" << menu.getPrice(item) << endl;
    }

    /** Calculate the total cost of the order. */
    double total = order.calculateTotal(menu);

    /** Apply a 5% upcharge for DoorDash orders. */
    if (order.getUserMethod() == "Doordash") {
        total += total * 0.05; // Add 5% upcharge
        cout << "Note: A 5% DoorDash upcharge has been applied.\n";
    }

    /** Display the selected delivery/dining method and the total price. */
    cout << "Method: " << order.getUserMethod() << endl;
    cout << "Total Price: $" << total << endl;
}
