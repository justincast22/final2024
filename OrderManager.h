#ifndef RESTURANTAPPFINAL_ORDERMANAGER_H
#define RESTURANTAPPFINAL_ORDERMANAGER_H

#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include "OrderManager.h"

using namespace std;

/**
 * The OrderManager class is responsible for managing all orders in the system.
 * It handles order addition, prioritization, state changes, and persistence.
 */
class OrderManager {
public:
    /**
     * Represents a single order in the system, including its items, method, priority, and status flags.
     */
    struct Order {
        vector<string> items;         /** Items included in the order. */
        string method;                /** Method of delivery or dining (e.g., Drive-Through, Phone). */
        int priority;                 /** Priority of the order based on the method. */
        bool isCooking = false;       /** Flag indicating if the order is currently being cooked. */
        bool isReadyForPickup = false;/** Flag indicating if the order is ready for pickup. */
        bool isCompleted = false;     /** Flag indicating if the order is completed. */
        bool isPickedUp = true;       /** Flag indicating if the order has been picked up. */
        int skipCount = 0;            /** Count of times the order has been skipped in prioritization. */

        /**
         * Constructs an Order object with specified items, method, and priority.
         */
        Order(vector<string> i, string m, int p) : items(i), method(m), priority(p) {}
    };

    /**
     * Adds a new order to the system.
     */
    void addOrder(const vector<string>& items, const string& method, int priority);

    /**
     * Displays all pending orders, sorted by priority.
     */
    void viewPendingOrders() const;

    /**
     * Marks the current order as complete.
     */
    void markOrderComplete();

    /**
     * Prioritizes orders based on their assigned priority.
     */
    void prioritizeOrders();

    /**
     * Retrieves the next order for cooking.
     */
    void getNextOrder();

    /**
     * Marks the current order as picked up.
     */
    void markPickedUp();

    /**
     * Cancels an order from the system.
     */
    void cancelOrder();

    /**
     * Saves the current state of all orders to a file.
     */
    void saveState() const;

    /**
     * Loads the state of orders from a file.
     */
    void loadState();

    /**
     * Marks an order as ready for pickup.
     */
    void markOrderForPickup();

    /**
     * Marks an order as picked up by the customer.
     */
    void markOrderPickedUp();

    /**
     * Marks an order as served to the customer.
     */
    void markServed();

private:
    vector<Order> orders; /** Vector to manage all orders in the system. */
    int maxSkips = 3;     /** Maximum number of skips allowed for prioritization. */

    /**
     * Sorts orders by priority in descending order.
     */
    void sortOrdersByPriority();
};

#endif //RESTURANTAPPFINAL_ORDERMANAGER_H
