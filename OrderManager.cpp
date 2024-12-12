#include "OrderManager.h"
#include "menu.h"
#include <fstream>
#include <iostream>
#include <algorithm>

/** Adds a new order to the queue and sorts by priority. */
void OrderManager::addOrder(const vector<string>& items, const string& method, int priority) {
    int computedPriority = (method == "Drive-Through") ? 4 :
                           (method == "Onsite") ? 3 :
                           (method == "Phone") ? 2 : 1;
    orders.emplace_back(items, method, computedPriority);
    sortOrdersByPriority();
    cout << "Order added successfully!\n";
}

/** Displays all pending orders, including their status. */
void OrderManager::viewPendingOrders() const {
    if (orders.empty()) {
        cout << "No pending orders.\n";
        return;
    }

    menu restaurantMenu;
    cout << "\nPending Orders (Sorted by Priority):\n";

    for (size_t i = 0; i < orders.size(); ++i) {
        const auto& order = orders[i];
        double total = 0.0;

        for (const auto& item : order.items) total += restaurantMenu.getPrice(item);
        if (order.method == "Doordash") total += total * 0.05;

        cout << i + 1 << ". Method: " << order.method
             << ", Total Price: $" << total
             << ", Items: ";
        for (const auto& item : order.items) cout << item << " ";

        if (order.isCooking) cout << " (Cooking)";
        else if (order.isCompleted) cout << " (Completed)";
        else if (order.isReadyForPickup) cout << " (Ready for Pickup)";
        cout << endl;
    }
}

/** Cancels an order if eligible. */
void OrderManager::cancelOrder() {
    if (orders.empty()) {
        cout << "No orders to cancel.\n";
        return;
    }

    viewPendingOrders();

    int cancelIndex;
    cout << "Enter the number of the order you want to cancel: ";
    while (!(cin >> cancelIndex) || cancelIndex < 1 || cancelIndex > static_cast<int>(orders.size())) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a valid order number: ";
    }

    cancelIndex -= 1;
    if (orders[cancelIndex].isCooking || orders[cancelIndex].isCompleted) {
        cout << "Cannot cancel this order.\n";
        return;
    }

    orders.erase(orders.begin() + cancelIndex);
    cout << "Order canceled successfully.\n";
    sortOrdersByPriority();
}

/** Marks an order as complete if it is cooking. */
void OrderManager::markOrderComplete() {
    if (orders.empty()) {
        cout << "No orders to mark as complete.\n";
        return;
    }

    viewPendingOrders();

    int completeIndex;
    cout << "Enter the number of the order to mark as complete: ";
    while (!(cin >> completeIndex) || completeIndex < 1 || completeIndex > static_cast<int>(orders.size())) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a valid order number: ";
    }

    auto& order = orders[completeIndex - 1];
    if (!order.isCooking) {
        cout << "This order is not currently being cooked.\n";
        return;
    }

    order.isCooking = false;
    order.isCompleted = true;
    cout << "Order marked as complete.\n";
}

/** Sorts orders based on priority. */
void OrderManager::prioritizeOrders() {
    sortOrdersByPriority();
    cout << "Orders prioritized successfully.\n";
}

/** Retrieves the next order for cooking. */
void OrderManager::getNextOrder() {
    if (orders.empty()) {
        cout << "No pending orders.\n";
        return;
    }

    auto& nextOrder = orders.front();
    if (!nextOrder.isCooking) {
        nextOrder.isCooking = true;
        cout << "Next order to cook: ";
        for (const auto& item : nextOrder.items) cout << item << " ";
        cout << endl;
    } else {
        cout << "Current order is already being cooked.\n";
    }
}

/** Marks an order as picked up. */
void OrderManager::markPickedUp() {
    if (orders.empty()) {
        cout << "No orders to pick up.\n";
        return;
    }
    orders.erase(orders.begin());
    cout << "Order marked as picked up.\n";
}

/** Saves orders to a file. */
void OrderManager::saveState() const {
    ofstream outFile("orders_state.txt");
    if (!outFile) {
        cerr << "Error saving orders.\n";
        return;
    }
    for (const auto& order : orders) {
        for (size_t i = 0; i < order.items.size(); ++i) {
            outFile << order.items[i];
            if (i != order.items.size() - 1) outFile << ",";
        }
        outFile << "|" << order.method << "\n";
    }
    cout << "State saved successfully.\n";
}

/** Loads orders from a file. */
void OrderManager::loadState() {
    ifstream inFile("orders_state.txt");
    if (!inFile) {
        cerr << "Error loading orders.\n";
        return;
    }

    orders.clear();
    string line;
    while (getline(inFile, line)) {
        size_t separatorPos = line.find('|');
        if (separatorPos == string::npos) continue;

        string itemsPart = line.substr(0, separatorPos);
        string method = line.substr(separatorPos + 1);

        vector<string> items;
        size_t pos = 0;
        while ((pos = itemsPart.find(',')) != string::npos) {
            items.push_back(itemsPart.substr(0, pos));
            itemsPart.erase(0, pos + 1);
        }
        if (!itemsPart.empty()) items.push_back(itemsPart);

        int priority = (method == "Drive-Through") ? 4 :
                       (method == "Onsite") ? 3 :
                       (method == "Phone") ? 2 : 1;
        orders.emplace_back(items, method, priority);
    }

    sortOrdersByPriority();
    cout << "State loaded successfully.\n";
}

/** Sorts the orders by priority. */
void OrderManager::sortOrdersByPriority() {
    sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) {
        return a.priority > b.priority;
    });
}

/** Marks an order as served and removes it from the queue. */
void OrderManager::markServed() {
    if (orders.empty()) {
        cout << "No orders to serve.\n";
        return;
    }

    cout << "\nOrders Ready to Be Served:\n";
    bool foundReadyToServe = false;

    for (size_t i = 0; i < orders.size(); ++i) {
        if (orders[i].isCompleted) {
            foundReadyToServe = true;
            cout << i + 1 << ". Method: " << orders[i].method << ", Items: ";
            for (const auto& item : orders[i].items) cout << item << " ";
            cout << endl;
        }
    }

    if (!foundReadyToServe) {
        cout << "No completed orders are ready to be served.\n";
        return;
    }

    int serveIndex;
    cout << "Enter the number of the order to mark as served: ";
    while (!(cin >> serveIndex) || serveIndex < 1 || serveIndex > static_cast<int>(orders.size())) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a valid order number: ";
    }

    auto& order = orders[serveIndex - 1];
    if (!order.isCompleted) {
        cout << "This order is not marked as completed.\n";
        return;
    }

    orders.erase(orders.begin() + (serveIndex - 1));
    cout << "Order " << serveIndex << " has been served and removed from the queue.\n";
}

/** Marks an order as picked up and removes it from the queue. */
void OrderManager::markOrderForPickup() {
    if (orders.empty()) {
        cout << "No orders to pick up.\n";
        return;
    }

    cout << "\nOrders Ready for Pickup:\n";
    bool foundReadyForPickup = false;

    for (size_t i = 0; i < orders.size(); ++i) {
        if (orders[i].isReadyForPickup) {
            foundReadyForPickup = true;
            cout << i + 1 << ". Method: " << orders[i].method << ", Items: ";
            for (const auto& item : orders[i].items) cout << item << " ";
            cout << endl;
        }
    }

    if (!foundReadyForPickup) {
        cout << "No orders are currently ready for pickup.\n";
        return;
    }

    int pickupIndex;
    cout << "Enter the number of the order to mark as picked up: ";
    while (!(cin >> pickupIndex) || pickupIndex < 1 || pickupIndex > static_cast<int>(orders.size())) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a valid order number: ";
    }

    auto& order = orders[pickupIndex - 1];
    if (!order.isReadyForPickup) {
        cout << "This order is not marked as ready for pickup.\n";
        return;
    }

    orders.erase(orders.begin() + (pickupIndex - 1));
    cout << "Order " << pickupIndex << " has been picked up and removed from the queue.\n";
}
