#ifndef RESTURANTAPPFINAL_MENU_H
#define RESTURANTAPPFINAL_MENU_H

#include <vector>
#include <string>
using namespace std;

/**
 * The menu class represents the menu of a restaurant, containing items and their prices.
 */
class menu {
public:
    /**
     * A static vector containing the names of menu items.
     */
    static vector<string> items;

    /**
     * A static vector containing the prices of menu items.
     */
    static vector<double> prices;

    /**
     * Displays the menu items and their corresponding prices.
     */
    void showMenu() const;

    /**
     * Retrieves the price of a given item from the menu.
     */
    double getPrice(const string& item) const;
};

#endif //RESTURANTAPPFINAL_MENU_H
