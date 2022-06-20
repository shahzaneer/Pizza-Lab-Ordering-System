#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Pizza Shop Ordering Management System

// Defining Data Types

struct order
{
    int quantity;
    string pizzaName;
    double bill;
};

struct customer
{
    int age;
    string name;
    order order;
};

struct walkingCustomer
{
    customer cusotomer;
    walkingCustomer *next = NULL;
};

struct dineInCustomer
{
    customer cusotomer;
    dineInCustomer *next = NULL;
};

struct homeDeliveryCustomer
{
    customer cusotomer;
    string address;
    struct homeDeliveryCustomer *next = NULL;
};

struct PizzaShop
{

    string shopName;
    string *menu;
    int *price;
    string address;
    walkingCustomer *nextWalkingCustomer = NULL;
    dineInCustomer *nextDineInCustomer = NULL;
    homeDeliveryCustomer *nextHomeDeliveryCustomer = NULL;
};

// Globally declaring the pizza Shop's pointer
PizzaShop *myPizzaShop = NULL;

// Globally Declaring the Current Customer's Pointers for all three Types
walkingCustomer *currentWalkingCustomer = NULL;
dineInCustomer *currentDineInCustomer = NULL;
homeDeliveryCustomer *currentHomeDeliveryCustomer = NULL;

// Now defining Order Placing and Serving of Walking Customer
// Based on : Older person will be served first (PRIORITY QUEUE)
void placeOrderWalkingCustomer();
void serveOrderWalkingCustomer();

// Now defining Order Placing and Serving of Dine-In Customer
// Based on : First Come First Served (FIFO) (QUEUE)
void placeOrderDineInCustomer();
void serveOrderDineInCustomer();

// Now defining Order Placing and Serving of Home Delivery Customer
// Based on : (when all orders are ready)(LIFO)(Stack)

void placeOrderHomeDeliveryCustomer();
void serveOrderHomeDeliveryCustomer();


// In case of Serving , to keep the record of Customers Served, implementing AVL Tree
// to search the record of Customers by Name
// It can also Display all the customers Served
int main()
{
    // making pizza shop
    myPizzaShop = new PizzaShop;

    // setting the name
    myPizzaShop->shopName = "The Pizza Delight";

    // setting the address
    myPizzaShop->address = "Liberty Chowk, Lahore";

    // Setting the menu
    myPizzaShop->menu = new string[10]{
        "chickenTikka", "arabicRanch",
        "chickenFajita","cheeseLover",
        "chickenSupreme","allveggie",
        "garlicWest","BeefBold",
        "phantom","mexicanDelight"
    };

    // setting the price

    myPizzaShop->price = new int[10] {2000, 2500, 2400, 2200, 2700, 2000, 2100, 3000, 3000, 2800};


    return 0;
}