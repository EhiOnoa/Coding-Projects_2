#include "vending_lib.h"
#include <stdio.h>

int main() 
{
    // Part I - Setup
    struct Product products[NUM_PRODUCTS];
    struct ShoppingCart cart;
    cart.itemCount = 0;
    cart.totalCost = 0.0;

    // Fill the vending machine with products
    stockMachine(products);

    // Print the title
    printf("Welcome to the Vending Machine!\n");

    // Part II - The vending machine
    enum Menu userChoice;  // Declare userChoice here

    while (true) 
    {
        // Display the products
        displayProducts(products);

        // Get user's product choice
        int productCode = getProduct();

        // Handle the user abort
        if (productCode == ABORT) 
        {
            printf("Program aborted. Exiting...\n");
            break;
        }

        // Get the quantity from the user
        int quantity = getQuantity(productCode, products);

        // Add items to the cart
        struct CartItem selectedItem = selectItem((enum ProductType)productCode,
         products, quantity);
        //Create an if staement for when the cart is full
        if (!addToCart(selectedItem, &cart)) 
        {
            printf("Shopping cart is full. Cannot add more items.\n");
            break;
        }

        // Ask user to continue shopping, cancel, or proceed to payment
        userChoice = getUserChoice();

        switch (userChoice) 
        {
            case CONTINUE:
                // create a function that Continue's shopping
                continue;
            case CANCEL:
                // create a function that Cancels purchase
                cancelPurchase(&cart, products);
                printf("Purchase canceled. Exiting...\n");
                break;
            case CHECKOUT:
                generateBill(&cart, products);

                // Ask for confirmation
                printf("Do you want to proceed with the purchase? (1 for Yes, 2"
                " for No): ");
                int confirmation;
                scanf("%d", &confirmation);

                if (confirmation == 1) 
                {
                    // Process the payment
                    if (pay(&cart, cart.totalCost)) 
                    {
                        printf("Purchase successful! You can retrieve your"
                        " items.\n");
                    } 

                    else 
                    {
                        printf("Purchase canceled. Exiting...\n");
                    }
                } 
                
                else 
                {
                    // Cancel the purchase
                    cancelPurchase(&cart, products);
                    printf("Purchase canceled. Exiting...\n");
                }

                break;
        }
    }

    return 0;
}
