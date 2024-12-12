#include "menu.h"
#include <iostream>

/**
 * Static vector containing the names of menu items.
 */
vector<string> menu::items = {"Burger", "Fries", "Wings", "Soda"};

/**
 * Static vector containing the prices of menu items.
 */
vector<double> menu::prices = {5.99, 2.99, 7.99, 1.99};

/**
 * Displays the available menu items and their corresponding prices.
 */
void menu::showMenu() const {
    cout << "Available Menu Items:\n";
    for (size_t i = 0; i < items.size(); ++i) {
        cout << i + 1 << ". " << items[i] << " - $" << prices[i] << endl;
    }
}

/**
 * Retrieves the price of a specified item from the menu.
 */
double menu::getPrice(const string& item) const {
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i] == item) {
            return prices[i];
        }
    }
    return 0.0;
}
