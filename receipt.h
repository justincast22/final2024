#ifndef RESTURANTAPPFINAL_RECEIPT_H
#define RESTURANTAPPFINAL_RECEIPT_H

#include "order.h"
#include "menu.h"

/**
 * The receipt class provides functionality to display a detailed receipt
 * for a given order, including itemized details and the total cost.
 */
class receipt {
public:
    /**
     * Displays the receipt for a specified order, including item details and prices.
     */
    void showReceipt(const order& order, const menu& menu) const;
};

#endif //RESTURANTAPPFINAL_RECEIPT_H
