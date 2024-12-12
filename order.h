#ifndef RESTURANTAPPFINAL_ORDER_H
#define RESTURANTAPPFINAL_ORDER_H

#include <vector>
#include <string>
#include "menu.h"
#include "OrderManager.h"
using namespace std;

/**
 * The order class manages individual customer orders, including placing orders,
 * saving/loading order states, and calculating the total cost.
 */
class order {
public:
    /**
     * Prompts the user to place an order, selecting items and a delivery method.
     */
    void placeOrder();

    /**
     * Saves the current state of all orders to a file for persistence.
     */
    void saveState() const;

    /**
     * Loads the state of all orders from a file, restoring them into memory.
     */
    void loadState();

    /**
     * Retrieves the user's current order.
     */
    const vector<string>& getUserOrder() const;

    /**
     * Retrieves the user's selected delivery method.
     */
    const string& getUserMethod() const;

    /**
     * Calculates the total cost of the user's order based on the menu prices.
     */
    double calculateTotal(const menu& menu) const;

private:
    /**
     * A collection of all customer orders.
     */
    vector<vector<string>> allOrders;

    /**
     * The items selected by the user for the current order.
     */
    vector<string> userOrder;

    /**
     * The delivery or dining method selected by the user for the current order.
     */
    string userMethod;
};

#endif //RESTURANTAPPFINAL_ORDER_H
