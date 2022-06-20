#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Pizza Shop Ordering Management System

// Defining Data Types

struct customer
{
    int age;
    string name;
    string pizzaName;
    int quantity;
    double bill;

    customer(){}

    customer(int age, string name, int quantity, string pizzaName, double bill)
    {
        this->age = age;
        this->name = name;
        this->pizzaName = pizzaName;
        this->quantity = quantity;
        this->bill = bill;
    }
};

struct walkingCustomer
{
    customer cusotomer;
    walkingCustomer *next = NULL;

    walkingCustomer(int age, string name, int quantity, string pizzaName, double bill)
    {
        this->cusotomer = customer(age, name, quantity, pizzaName, bill);
    }
};

struct dineInCustomer
{
    customer cusotomer;
    dineInCustomer *next = NULL;

    dineInCustomer(int age, string name, int quantity, string pizzaName, double bill)
    {
        this->cusotomer = customer(age, name, quantity, pizzaName, bill);
    }
};

struct homeDeliveryCustomer
{

    customer cusotomer;
    string address;
    struct homeDeliveryCustomer *next = NULL;
    homeDeliveryCustomer(int age, string name, int quantity, string pizzaName, double bill, string address)
    {
        this->cusotomer = customer(age, name, quantity, pizzaName, bill);
        this->address = address;
    }
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

void placeOrderWalkingCustomer(int age, string name, string pizzaName, int quantity, double bill)
{
    // making new Customer
    currentWalkingCustomer = new walkingCustomer(age, name, quantity, pizzaName, bill);

    if (myPizzaShop->nextWalkingCustomer == NULL)
    {
        // if first then insert in front
        myPizzaShop->nextWalkingCustomer = currentWalkingCustomer;
    }
    else
    {
        // finding the last Node
        walkingCustomer *temp = myPizzaShop->nextWalkingCustomer;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        if (temp->cusotomer.age < currentWalkingCustomer->cusotomer.age)
        {
            // insert at front
            walkingCustomer *firstCustomer = myPizzaShop->nextWalkingCustomer;
            myPizzaShop->nextWalkingCustomer = currentWalkingCustomer;
            currentWalkingCustomer->next = firstCustomer;
        }
        else
        {
            // insert at end
            temp->next = currentWalkingCustomer;
            currentWalkingCustomer->next = NULL;
        }
    }
}
void serveOrderWalkingCustomer()
{
    if (myPizzaShop->nextWalkingCustomer == NULL)
    {
        cout << "No Walking Customer to Serve" << endl;
    }
    else
    {
        // serving the first customer
        walkingCustomer *temp = myPizzaShop->nextWalkingCustomer;
        myPizzaShop->nextWalkingCustomer = temp->next;
        cout << "Walking Customer Served : " << temp->cusotomer.name << endl;
        delete temp; // deleting the customer
    }
}

// Now defining Order Placing and Serving of Dine-In Customer
// Based on : First Come First Served (FIFO) (QUEUE)

void placeOrderDineInCustomer(int age, string name, string pizzaName, int quantity, double bill)
{
    // making new Customer
    currentDineInCustomer = new dineInCustomer(age, name, quantity, pizzaName, bill);

    if (myPizzaShop->nextDineInCustomer == NULL)
    {
        // if first insert in front
        myPizzaShop->nextDineInCustomer = currentDineInCustomer;
    }
    else
    {
        // finding the last Node
        dineInCustomer *temp = myPizzaShop->nextDineInCustomer;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = currentDineInCustomer;
        currentDineInCustomer->next = NULL;
    }
}
void serveOrderDineInCustomer()
{
    if (myPizzaShop->nextDineInCustomer == NULL)
    {
        cout << "No Dine-In Customer to Serve" << endl;
    }
    else
    {
        // serving the first customer
        dineInCustomer *temp = myPizzaShop->nextDineInCustomer;
        myPizzaShop->nextDineInCustomer = temp->next;
        cout << "Dine-In Customer Served : " << temp->cusotomer.name << endl;
        delete temp; // deleting the customer
    }
}

// Now defining Order Placing and Serving of Home Delivery Customer
// Based on : (when all orders are ready)(LIFO)(Stack)

void placeOrderHomeDeliveryCustomer(int age, string name, string pizzaName, int quantity, double bill, string address)
{
    // making new Customer
    currentHomeDeliveryCustomer = new homeDeliveryCustomer(age, name, quantity, pizzaName, bill, address);

    if (myPizzaShop->nextHomeDeliveryCustomer == NULL)
    {
        // if first insert in front
        myPizzaShop->nextHomeDeliveryCustomer = currentHomeDeliveryCustomer;
    }
    else
    {
        // finding the last Node
        homeDeliveryCustomer *temp = myPizzaShop->nextHomeDeliveryCustomer;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = currentHomeDeliveryCustomer;
        currentHomeDeliveryCustomer->next = NULL;
    }
}

void serveOrderHomeDeliveryCustomer()
{
    if (myPizzaShop->nextHomeDeliveryCustomer == NULL)
    {
        cout << "No Home Delivery Customer to Serve" << endl;
    }
    else
    {
        // serving the last customer first
        homeDeliveryCustomer *previous = myPizzaShop->nextHomeDeliveryCustomer;
        homeDeliveryCustomer *temp = NULL;

        while (previous->next->next != NULL)
        {
            previous = previous->next;
        }

        temp = previous->next;

        previous->next = NULL;
        cout << "Home Delivery Customer Served : " << temp->cusotomer.name << endl;
        delete temp; // deleting the customer
    }
}

// It will serve all the waiting orders

void serveAllOrders()
{

    while (myPizzaShop->nextWalkingCustomer != NULL)
    {
        serveOrderWalkingCustomer();
    }
    while (myPizzaShop->nextDineInCustomer != NULL)
    {
        serveOrderDineInCustomer();
    }
    while (myPizzaShop->nextHomeDeliveryCustomer != NULL)
    {
        serveOrderHomeDeliveryCustomer();
    }
}

// In case of Serving , to keep the record of Customers Served, implementing AVL Tree
// to search the record of Customers by Name
// It can also Display all the customers Served

struct servedCustomer
{

    int age;
    string name;
    int quantity;
    string pizzaName;
    double bill;
    servedCustomer *left;
    servedCustomer *right;

    // Constructor
    servedCustomer(int age, string name, int quantity, string pizzaName, double bill)
    {
        // setting customers details

        this->age = age;
        this->name = name;
        this->quantity = quantity;
        this->pizzaName = pizzaName;
        this->bill = bill;

        // child to NULL
        this->left = NULL;
        this->right = NULL;
    }
};

servedCustomer *root = NULL; // Global pointer for the root of AVLTree

// isEmpty or not
int isEmpty(servedCustomer *root)
{
    return root == NULL;
}

// display Customers Details

void display(servedCustomer *root)
{
    cout << root->name << endl;
    cout << root->age << endl;
    cout << root->pizzaName << endl;
    cout << root->quantity << endl;
    cout << root->bill << endl;
}

// Traversal for the served Customers

void traversal(servedCustomer *root)
{
    if (root)
    {
        traversal(root->left);
        display(root); // will display all the served Customers
        traversal(root->right);
    }
}

// Height of servedCustomer tree

int height(servedCustomer *root)
{
    if (!root)
        return 0;

    return max(height(root->left), height(root->right)) + 1;
}

// Balance Factor for each ServedCustomer node

int balanceFactor(servedCustomer *root)
{
    if (!root)
        return 0;

    return height(root->left) - height(root->right);
}

// Maximum of two integers as a helper function for height
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Searching in servedCustomer tree

servedCustomer *search(servedCustomer *root, string keyName)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->name == keyName)
    {
        return root;
    }
    else if (root->name > keyName)
    {
        return search(root->right, keyName);
    }
    else if (root->name < keyName)
    {
        return search(root->left, keyName);
    }

    return root;
}

// Finding Maximum Node of servedCustomer tree

servedCustomer *maxservedCustomer(servedCustomer *root)
{
    // Maximum Node is Present in the most Right Node  of the served Customer Tree

    servedCustomer *p = root;
    servedCustomer *temp = NULL;

    while (p != NULL)
    {
        temp = p;
        p = p->right;
    }

    return temp;
}

// Balancing the ServedCustomer's Tree thorugh AVL Rotations

// LL Rotation
servedCustomer *LLRotation(servedCustomer *root)
// rotate wese right per krna hai!
{
    // saving the new root and the lost element in case of rotation
    servedCustomer *x = root->left;
    servedCustomer *temp = x->right;

    // Performing rotation
    x->right = root;
    root->left = temp;

    // updating the root
    root = x;
    // returning the root
    return x;
}

// RR Rotation
servedCustomer *RRRotation(servedCustomer *root)
{
    // rotate wese left per krna hai!

    // saving the new root and the lost element in case of rotation

    servedCustomer *x = root->right;
    servedCustomer *temp = x->left;

    // Performing rotation
    x->left = root;
    root->right = temp;

    // updating the root
    root = x;

    // returning the root
    return x;
}

// LR Rotation
servedCustomer *LRRotation(servedCustomer *root)
{
    root->left = RRRotation(root->left);
    return LLRotation(root);
}

// RL Rotation
servedCustomer *RLRotation(servedCustomer *root)
{
    root->right = LLRotation(root->right);
    return RRRotation(root);
}

//  INSERTION in servedCustomer Tree

servedCustomer *insertion(int age, string name, int quantity, string pizzaName, double bill, servedCustomer *root)
{
    servedCustomer *newNode = new servedCustomer(age, name, quantity, pizzaName, bill);

    if (root == NULL)
    {
        root = newNode;
    }

    else if (root->name > newNode->name)
    {
        root->left = insertion(age, name, quantity, pizzaName, bill, root->left);
    }
    else if (root->name < newNode->name)
    {
        root->right = insertion(age, name, quantity, pizzaName, bill, root->right);
    }

    else
    {
        cout << "No duplicates Values are Allowed " << endl;
        return root;
    }

    int bf = balanceFactor(root);

    if (bf == 2)
    {
        // LL
        if (root->left->name > newNode->name)
        {
            return LLRotation(root);
        }

        // LR
        if (root->left->name < newNode->name)
        {
            return LRRotation(root);
        }
    }
    else if (bf == -2)
    {
        // RR
        if (root->right->name < newNode->name)
        {
            return RRRotation(root);
        }

        // RL
        if (root->right->name > newNode->name)
        {
            return RLRotation(root);
        }
    }

    return root; // in case there is no need of rotation
}

servedCustomer *deleteNode(servedCustomer *root, string keyName)
{
    if (root == NULL)
    {
        return root;
    }
    else if (keyName < root->name)
    {
        root->left = deleteNode(root->left, keyName);
    }
    else if (keyName > root->name)
    {
        root->right = deleteNode(root->right, keyName);
    }
    else
    {
        // It means that we have found our node to be deleted and now its the time to delete the node

        servedCustomer *temp = NULL;
        // case 1: 0 child
        if (!root->left && !root->right)
        {
            delete root;
            root = NULL; // segmentation Fault (root dangling hogya tha aur tree lost! bht dhayan rkhna hai iska)
        }
        // case 2: 1 child
        else if (!root->left && root->right)
        {
            root = temp;
            root = root->right;
            delete temp;
        }
        else if (!root->right && root->left)
        {
            root = temp;
            root = root->left;
            delete temp;
        }
        else
        {
            temp = maxservedCustomer(root->left);
            root->name = temp->name;
            root->left = deleteNode(root->left, temp->name);
        }

        // Now start Balancing the root!

        int bf = balanceFactor(root);

        if (bf == 2)
        {
            // LL
            if (root->left->left)
            {
                return LLRotation(root);
            }

            // LR

            else
            {
                return LRRotation(root);
            }
        }
        else if (bf == -2)
        {
            // RR
            if (root->right->right)
            {
                return RRRotation(root);
            }

            // RL
            else
            {
                return RLRotation(root);
            }
        }
    }

    return root; // in case there is no need of rotation
}

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
        "chickenFajita", "cheeseLover",
        "chickenSupreme", "allveggie",
        "garlicWest", "BeefBold",
        "phantom", "mexicanDelight"};

    // setting the price

    myPizzaShop->price = new int[10]{2000, 2500, 2400, 2200, 2700, 2000, 2100, 3000, 3000, 2800};

    return 0;
}