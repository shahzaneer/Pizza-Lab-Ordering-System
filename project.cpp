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

    walkingCustomer(int age, string name, int quantity, string pizzaName, double bill)
    {
        cusotomer.age = age;
        cusotomer.name = name;
        cusotomer.order.quantity = quantity;
        cusotomer.order.pizzaName = pizzaName;
        cusotomer.order.bill = bill;
    }
};

struct dineInCustomer
{
    customer cusotomer;
    dineInCustomer *next = NULL;

    dineInCustomer(int age, string name, int quantity, string pizzaName, double bill)
    {
        cusotomer.age = age;
        cusotomer.name = name;
        cusotomer.order.quantity = quantity;
        cusotomer.order.pizzaName = pizzaName;
        cusotomer.order.bill = bill;
    }
};


struct homeDeliveryCustomer{
    customer cusotomer;
    string address;
    struct homeDeliveryCustomer *next = NULL;

    homeDeliveryCustomer(int age, string name, int quantity, string pizzaName, double bill, string address)
    {
        cusotomer.age = age;
        cusotomer.name = name;
        cusotomer.order.quantity = quantity;
        cusotomer.order.pizzaName = pizzaName;
        cusotomer.order.bill = bill;
        this->address = address;
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

void placeOrderWalkingCustomer(int age , string name , string pizzaName , int quantity , double bill){
    // making new Customer
    currentWalkingCustomer = new walkingCustomer(age, name, quantity, pizzaName, bill);

    if(myPizzaShop->nextWalkingCustomer == NULL){
        // if first then insert in front
        myPizzaShop->nextWalkingCustomer = currentWalkingCustomer;
    }
    else{
        // finding the last Node
        walkingCustomer *temp = myPizzaShop->nextWalkingCustomer;
        while(temp->next != NULL){
            temp = temp->next;
        }

        if(temp->cusotomer.age < currentWalkingCustomer->cusotomer.age){
            // insert at front
            walkingCustomer *firstCustomer = myPizzaShop->nextWalkingCustomer;
            myPizzaShop->nextWalkingCustomer = currentWalkingCustomer;
            currentWalkingCustomer->next = firstCustomer;
        }
        else{
            // insert at end
            temp->next = currentWalkingCustomer;
            currentWalkingCustomer->next = NULL;
        }

    }
}
void serveOrderWalkingCustomer(){
    if(myPizzaShop->nextWalkingCustomer == NULL){
        cout << "No Walking Customer to Serve" << endl;
    }
    else{
        // serving the first customer
        walkingCustomer *temp = myPizzaShop->nextWalkingCustomer;
        myPizzaShop->nextWalkingCustomer = temp->next;
        cout << "Walking Customer Served : " << temp->cusotomer.name << endl;
        delete temp; // deleting the customer
    }
}

// Now defining Order Placing and Serving of Dine-In Customer
// Based on : First Come First Served (FIFO) (QUEUE)

void placeOrderDineInCustomer(int age, string name, string pizzaName, int quantity, double bill){
    // making new Customer
    currentDineInCustomer = new dineInCustomer(age, name, quantity, pizzaName, bill);

    if(myPizzaShop->nextDineInCustomer == NULL){
        //if first insert in front
        myPizzaShop->nextDineInCustomer = currentDineInCustomer;
    }
    else{
        // finding the last Node
        dineInCustomer *temp = myPizzaShop->nextDineInCustomer;
        while(temp->next != NULL){
            temp = temp->next;
        }

        temp->next = currentDineInCustomer;
        currentDineInCustomer->next = NULL;
    }

}
void serveOrderDineInCustomer(){
    if(myPizzaShop->nextDineInCustomer == NULL){
        cout << "No Dine-In Customer to Serve" << endl;
    }
    else{
        // serving the first customer
        dineInCustomer *temp = myPizzaShop->nextDineInCustomer;
        myPizzaShop->nextDineInCustomer = temp->next;
        cout << "Dine-In Customer Served : " << temp->cusotomer.name << endl;
        delete temp; // deleting the customer
    }
}

// Now defining Order Placing and Serving of Home Delivery Customer
// Based on : (when all orders are ready)(LIFO)(Stack)

void placeOrderHomeDeliveryCustomer(int age ,string name ,string pizzaName , int quantity, double bill , string address){
    // making new Customer
    currentHomeDeliveryCustomer = new homeDeliveryCustomer(age, name, quantity, pizzaName, bill, address);

    if(myPizzaShop->nextHomeDeliveryCustomer == NULL){
        // if first insert in front
        myPizzaShop->nextHomeDeliveryCustomer = currentHomeDeliveryCustomer;
    }
    else{
        // finding the last Node
        homeDeliveryCustomer *temp = myPizzaShop->nextHomeDeliveryCustomer;
        while(temp->next != NULL){
            temp = temp->next;
        }

        temp->next = currentHomeDeliveryCustomer;
        currentHomeDeliveryCustomer->next = NULL;
    }

}

void serveOrderHomeDeliveryCustomer(){
    if(myPizzaShop->nextHomeDeliveryCustomer == NULL){
        cout << "No Home Delivery Customer to Serve" << endl;
    }
    else{
        // serving the last customer first
        homeDeliveryCustomer *previous = myPizzaShop->nextHomeDeliveryCustomer;
        homeDeliveryCustomer *temp = NULL;

        while(previous->next->next != NULL){
            previous = previous->currentHomeDeliveryCustomer;
        }

        temp = previous->next;

        previous->next = NULL;
        cout << "Home Delivery Customer Served : " << temp->cusotomer.name << endl;
        delete temp; // deleting the customer

    }
}


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