#include <iostream>
#include "role.h"
#include "OrderManager.h"

/**
 * Create an instance of OrderManager to manage restaurant orders.
 */
OrderManager ordermanager;

/**
 * Create an instance of the role class to handle user roles.
 * This will determine the access level and functionalities available to the user.
 */
role userRole;

using namespace std;

/**
 * The main function serves as the entry point for the Restaurant Management System.
 * It welcomes the user, prompts for their role, and initializes the system.
 */
int main() {
    /** Display a welcome message to the user. */
    cout << "Welcome to the Restaurant Management System!\n";

    /** Prompt the user to input their role and handle role-specific actions. */
    userRole.askRole();

    return 0;
}
