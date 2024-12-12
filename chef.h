#ifndef RESTURANTAPPFINAL_CHEF_H
#define RESTURANTAPPFINAL_CHEF_H

#include "OrderManager.h"
using namespace std;

/**
 * The chef class represents the role of a chef in the restaurant management system.
 * It provides functionalities to process and manage orders.
 */
class chef {
public:
    /**
     * Displays the main menu for the chef, allowing them to interact with pending orders.
     */
    void processOrders();

private:
    /**
     * Displays a list of all pending orders for the chef to review.
     */
    void viewPendingOrders();

    /**
     * Allows the chef to mark a selected order as complete.
     */
    void markOrderComplete();

    /**
     * Enables the chef to prioritize orders based on their urgency.
     */
    void prioritizeOrders();
};

#endif //RESTURANTAPPFINAL_CHEF_H
