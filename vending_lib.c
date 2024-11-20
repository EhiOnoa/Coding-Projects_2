#include "vending_lib.h"
#include <stdio.h>

// Descriptions of the products
const char *prodDesc[NUM_PRODUCTS] = 
{
    "Hershey's Milk Chocolate Bar 1.55oz",
    "Lays Classic Potato Chips 1.5oz",
    "Hubba Bubba Original Bubble Gum",
    "Pepsi Soda 20oz Bottle"};

// Declare a function to fill up the array of products
void stockMachine(struct Product products[NUM_PRODUCTS]) 
{
    float prices[NUM_PRODUCTS] = {2.30, 1.50, 1.00, 1.99};
    int quantities[NUM_PRODUCTS] = {15, 10, 20, 7};

    for (int i = 0; i < NUM_PRODUCTS; i++) 
    {
        products[i].type = i;
        products[i].price = prices[i];
        products[i].quantity = quantities[i];
    }
}

// Display available products
void displayProducts(const struct Product products[NUM_PRODUCTS]) 
{
    printf("Code | Product Description                 |"
        " Available Quantity | Unit Price\n");
    printf("-----|-------------------------------------|"
        "--------------------|------------\n");

    for (int i = 0; i < NUM_PRODUCTS; i++) 
    {
        printf("%4d | %-35s | %18d | %10.2f\n", i, prodDesc[i], 
            products[i].quantity, products[i].price);
    }
}

// Declare a fucntion product code from the user
int getProduct() 
{
    int code;
    printf("Enter the code of the product you want to purchase: ");
    scanf("%d", &code);

    // Clear input buffer
    while (getchar() != '\n');

    return code;
}

// Declare a function to get the quantity of a product from the user
int getQuantity(int productCode, const struct Product products[NUM_PRODUCTS]) 
{
    printf("Enter the quantity for %s: ", prodDesc[productCode]);

    int quantity;
    scanf("%d", &quantity);

    // Clear input buffer
    while (getchar() != '\n');

    if (quantity <= 0) 
    {
        printf("Invalid quantity. Please enter a number greater than zero.\n");
        return ABORT;
    }

    if (quantity > products[productCode].quantity) 
    {
        printf("Insufficient quantity available. "
            "Please enter a smaller quantity.\n");
        return ABORT;
    }

    return quantity;
}

// Function to select an item and update the array of products
struct CartItem selectItem(enum ProductType productType, 
    struct Product products[NUM_PRODUCTS], int quantity) 
{
    struct CartItem item;
    item.product.type = productType;
    item.product.price = products[productType].price;
    item.product.quantity = quantity;
    item.quantity = quantity;

    // Update the array of products
    products[productType].quantity -= quantity;

    return item;
}

// Function to add an item to the shopping cart
bool addToCart(struct CartItem item, struct ShoppingCart *cart) 
{
    if (cart->itemCount >= MAX_NUM_PRODUCTS) 
    {
        printf("Shopping cart is full. Cannot add more items.\n");
        return false;
    }

    // Update the shopping cart
    cart->items[cart->itemCount] = item;
    cart->itemCount++;
    cart->totalCost += item.product.price * item.quantity;

    return true;
}

// Function to cancel the purchase and return items to the shelf
void cancelPurchase(struct ShoppingCart *cart, 
    struct Product products[NUM_PRODUCTS]) 
{
    for (int i = 0; i < cart->itemCount; i++) 
    {
        products[cart->items[i].product.type].quantity += 
        cart->items[i].quantity;
    }

    // Reset the shopping cart
    cart->itemCount = 0;
    cart->totalCost = 0.0;

    printf("Purchase canceled. Items returned to the shelf.\n");
}

// Function to generate the bill
void generateBill(const struct ShoppingCart *cart, 
    const struct Product products[NUM_PRODUCTS]) 
{
    printf("Product                                 |"
        " Unit Price | Product total\n");
    printf("----------------------------------------|"
        "------------|--------------\n");

    for (int i = 0; i < cart->itemCount; i++) 
    {
        printf("%2d x %-35s | %2d x %6.2f | %6.2f\n",
               cart->items[i].quantity,
               prodDesc[cart->items[i].product.type],
               cart->items[i].quantity,
               cart->items[i].product.price,
               cart->items[i].product.price * cart->items[i].quantity);
    }

    printf("Order Total: %.2f\n", cart->totalCost);
}

const char* creditCardToStr(enum CreditCard card) 
{
    switch (card) 
    {
        case MASTERCARD:
            return "MasterCard";
        case VISA:
            return "Visa";
        case DISCOVER:
            return "Discover";
        case AMERICAN_EXPRESS:
            return "American Express";
        default:
            return "Unknown Card";
    }
}

const char* contactlessToStr(enum Contactless method) 
{
    switch (method) 
    {
        case GOOGLE_WALLET:
            return "Google Wallet";
        case APPLE_PAY:
            return "Apple Pay";
        default:
            return "Unknown Method";
    }
}


// Function to handle the payment
bool pay(struct ShoppingCart *cart, float totalCost) 
{
    enum Payment paymentMethod;
    printf("Select payment method:\n");
    printf("1. Cash\n");
    printf("2. Credit Card\n");
    printf("3. Contactless\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Clear input buffer
    while (getchar() != '\n');

    switch (choice) 
    {
        case 1:
            paymentMethod = CASH;
            break;

        case 2:
            // Handle credit card payment
            {
                enum CreditCard creditCardBrand;
                printf("Enter credit card brand (1 for MasterCard, 2 for Visa,"
                       "3 for Discover, 4 for American Express): ");
                scanf("%d", (int*)&creditCardBrand);

                switch (creditCardBrand) 
                {
                    case MASTERCARD:
                    case VISA:
                    case DISCOVER:
                    case AMERICAN_EXPRESS: 
                    {
                        // Credit card payment logic
                        float serviceFee = 0.02 * cart->totalCost;
                        float finalAmount = cart->totalCost + serviceFee;

                        printf("Paid by: Credit Card (%s)\n", 
                            creditCardToStr(creditCardBrand));
                        printf("Service Fee: $%.2f\n", serviceFee);
                        printf("Paid amount: $%.2f\n", finalAmount);
                        printf("Change: $0.00\n");
                        return true;
                    }
                    default:
                        printf("Invalid credit card brand. Payment failed.\n");
                        return false;
                }
            }

        case 3:
            // Handle contactless payment
            {
                int contactlessChoice;
                printf("Enter contactless payment method (1 for Google Wallet,"
                       "2 for Apple Pay): ");
                scanf("%d", (int*)&contactlessChoice);

                switch (contactlessChoice) 
                {
                    case GOOGLE_WALLET:
                    case APPLE_PAY: 
                    {
                        // Contactless payment logic
                        float serviceFee = 0.01 * cart->totalCost;
                        float finalAmount = cart->totalCost + serviceFee;

                        printf("Paid by: Contactless Payment (%s)\n",
                               contactlessToStr(contactlessChoice));
                        printf("Service Fee: $%.2f\n", serviceFee);
                        printf("Paid amount: $%.2f\n", finalAmount);
                        printf("Change: $0.00\n");
                        return true;
                    }

                    default:
                        printf("Invalid contactless payment method."
                            " Payment failed.\n");
                        return false;
                }
            }

        // Process payment based on the selected method
        switch (paymentMethod) 
        {
            case CASH: 
            {
                float cashAmount;
                printf("Enter the amount in cash: $");
                scanf("%f", &cashAmount);

                if (cashAmount >= totalCost) 
                {
                    float change = cashAmount - totalCost;
                    printf("Payment successful. Change: $%.2f\n", change);
                    return true;
                } 

                else 
                {
                    printf("Insufficient cash. Payment failed.\n");
                    return false;
                }
            }

            case CREDIT_CARD: 
            {
                // Handle credit card payment
                int creditCard;
                printf("Enter credit card type (0 for MasterCard, 1 for Visa, "
                       "2 for Discover, 3 for American Express): ");
                scanf("%d", &creditCard);

                float serviceFee = 0.02 * totalCost;
                float finalAmount = totalCost + serviceFee;

                printf("Payment successful. Service Fee: $%.2f\n", serviceFee);
                printf("Paid amount: $%.2f\n", finalAmount);
                return true;
            }

            case CONTACTLESS: 
            {
                // Handle contactless payment
                int contactlessChoice;
                printf("Enter contactless payment method (0 for Google Wallet, "
                       "1 for Apple Pay): ");
                scanf("%d", &contactlessChoice);

                float contactlessServiceFee = 0.01 * totalCost;
                float contactlessFinalAmount = totalCost + 
                contactlessServiceFee;

                printf("Payment successful. Service Fee: $%.2f\n", 
                    contactlessServiceFee);
                printf("Paid amount: $%.2f\n", contactlessFinalAmount);
                return true;
            }

            default:
                printf("Invalid payment method. Payment failed.\n");
                return false;
        }

        // Reset the shopping cart after successful payment
        cart->itemCount = 0;
        cart->totalCost = 0.0;

        printf("Payment successful. Thank you!\n");
        return true;
    }
}
enum Menu getUserChoice(void) 
{
    int choice;
    printf("Enter your choice (1 for CONTINUE, 2 for CANCEL, "
        "3 for CHECKOUT): ");
    scanf("%d", &choice);

    switch (choice) 
    {
        case 1:
            return CONTINUE;
        case 2:
            return CANCEL;
        case 3:
            return CHECKOUT;
        default:
            return CONTINUE; 
    }
}
