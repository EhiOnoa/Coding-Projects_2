#ifndef VENDING_LIB_H
#define VENDING_LIB_H

#include <stdbool.h>

// Constants
//#define NUM_PRODUCTS 4
#define ABORT -1
#define MAX_NUM_PRODUCTS 100

// Enums
enum ProductType 
{
    CHOCOLATE_BAR,
    CHIPS,
    CHEWING_GUM,
    PEPSI,
    NUM_PRODUCTS
};

enum Menu getUserChoice(void);

enum Menu 
{
    CANCEL,
    CHECKOUT,
    CONTINUE
};

enum Payment 
{
    CASH,
    CREDIT_CARD,
    CONTACTLESS
};

enum CreditCard 
{
    MASTERCARD,
    VISA,
    DISCOVER,
    AMERICAN_EXPRESS,
    NUM_CREDIT_CARDS
};

enum Contactless 
{
    GOOGLE_WALLET,
    APPLE_PAY,
    NUM_CONTACTLESS_METHODS
};

// Structs
struct Product 
{
    enum ProductType type;
    float price;
    int quantity;
};

struct CartItem 
{
    struct Product product;
    int quantity;
};

struct ShoppingCart 
{
    struct CartItem items[MAX_NUM_PRODUCTS];
    int itemCount;
    float totalCost;
};

//Declarations
void stockMachine(struct Product products[NUM_PRODUCTS]);
void displayProducts(const struct Product products[NUM_PRODUCTS]);
int getProduct();
int getQuantity(int productCode, const struct Product products[NUM_PRODUCTS]);
struct CartItem selectItem(enum ProductType productType, struct Product products[NUM_PRODUCTS], int quantity);
bool addToCart(struct CartItem item, struct ShoppingCart *cart);
void cancelPurchase(struct ShoppingCart *cart, struct Product products[NUM_PRODUCTS]);
void generateBill(const struct ShoppingCart *cart, const struct Product products[NUM_PRODUCTS]);
bool pay(struct ShoppingCart *cart, float totalCost);
const char* creditCardToStr(enum CreditCard card);
const char* contactlessToStr(enum Contactless method);
bool pay(struct ShoppingCart *cart, float totalCost);

#endif // VENDING_LIB_H