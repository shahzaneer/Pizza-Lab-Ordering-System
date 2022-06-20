#include <iostream>
#include <stdlib.h>
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

// Globally declaring the variables for the total of all the orders
double total, walking, dineIn, homeDelivery;

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

void displayAllServedOrders(servedCustomer *root)
{
    if (root)
    {
        displayAllServedOrders(root->left);
        display(root); // will display all the served Customers
        displayAllServedOrders(root->right);
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
    cout << "Your Order has been Placed MR/MRS " << name << " and your order is " << pizzaName << " with " << quantity << " quantity and total bill is " << bill << endl;
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

        // Now before deleting the node we need to update the servedCustomer Tree
        root = insertion(temp->cusotomer.age, temp->cusotomer.name, temp->cusotomer.quantity, temp->cusotomer.pizzaName, temp->cusotomer.bill, root);

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
    cout << "Your Order has been Placed MR/MRS " << name << " and your order is " << pizzaName << " with " << quantity << " quantity and total bill is " << bill << endl;
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

        // Now before deleting the node we need to update the servedCustomer Tree
        root = insertion(temp->cusotomer.age, temp->cusotomer.name, temp->cusotomer.quantity, temp->cusotomer.pizzaName, temp->cusotomer.bill, root);

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
    cout << "Your Order has been Placed MR/MRS " << name << " and your order is " << pizzaName << " with " << quantity << " quantity and total bill is " << bill << endl;
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

        // Now before deleting the node we need to update the servedCustomer Tree
        root = insertion(temp->cusotomer.age, temp->cusotomer.name, temp->cusotomer.quantity, temp->cusotomer.pizzaName, temp->cusotomer.bill, root);

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

void displayAllOrdersWalkingCustomers(){
    if(myPizzaShop->nextWalkingCustomer == NULL){
        cout << "There is no Order for Walking Customer till yet" << endl;
    }
    else{
        walkingCustomer *traversal = myPizzaShop->nextWalkingCustomer;
        while(traversal != NULL){

            cout << "-----------------------------------------------------" << endl;
            cout << "Walking Customer : " << traversal->cusotomer.name << endl;
            cout << "Age : " << traversal->cusotomer.age << endl;
            cout << "Pizza Name : " << traversal->cusotomer.pizzaName << endl;
            cout << "Quantity : " << traversal->cusotomer.quantity << endl;
            cout << "Bill : " << traversal->cusotomer.bill <<" RS/_"<< endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }
}

void displayAllOrdersHomeDeliveryCustomers(){
    if (myPizzaShop->nextHomeDeliveryCustomer == NULL)
    {
        cout << "There is no Order for Home Delivery Customer till yet" << endl;
    }
    else
    {
        homeDeliveryCustomer *traversal = myPizzaShop->nextHomeDeliveryCustomer;
        while (traversal != NULL)
        {
            cout << "-----------------------------------------------------" << endl;
            cout << "Walking Customer : " << traversal->cusotomer.name << endl;
            cout << "Age : " << traversal->cusotomer.age << endl;
            cout << "Pizza Name : " << traversal->cusotomer.pizzaName << endl;
            cout << "Quantity : " << traversal->cusotomer.quantity << endl;
            cout << "Bill : " << traversal->cusotomer.bill << " RS/_" << endl;
            cout << "Address : " << traversal->address << endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }
}

void displayAllOrdersDineInCustomers(){
    if (myPizzaShop->nextDineInCustomer == NULL)
    {
        cout << "There is no Order for Dine-In Customer till yet" << endl;
    }
    else
    {
        dineInCustomer *traversal = myPizzaShop->nextDineInCustomer;
        while (traversal != NULL)
        {
            cout << "-----------------------------------------------------" << endl;
            cout << "Walking Customer : " << traversal->cusotomer.name << endl;
            cout << "Age : " << traversal->cusotomer.age << endl;
            cout << "Pizza Name : " << traversal->cusotomer.pizzaName << endl;
            cout << "Quantity : " << traversal->cusotomer.quantity << endl;
            cout << "Bill : " << traversal->cusotomer.bill << " RS/_" << endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }
}

void displayAllOrders(){

    cout << "The Walk-IN Customers Are :" << endl;
    displayAllOrdersWalkingCustomers();

    cout << "The Dine-IN Customers Are :" << endl;
    displayAllOrdersDineInCustomers();

    cout << "The Home Delivery Customers Are :" << endl;
    displayAllOrdersHomeDeliveryCustomers();

}

void earnings(){
    walkingCustomer *p = myPizzaShop->nextWalkingCustomer;
    while(p != NULL){
        walking += p->cusotomer.bill;
        p = p->next;
    }
    dineInCustomer *q = myPizzaShop->nextDineInCustomer;
    while(q != NULL){
        dineIn += q->cusotomer.bill;
        q = q -> next;
    }
    homeDeliveryCustomer *r = myPizzaShop->nextHomeDeliveryCustomer;
    while(r != NULL){
        homeDelivery += r->cusotomer.bill;
        r = r->next;
    }
    total = walking + dineIn + homeDelivery;

    cout << "The total Earning by Walk-In customers are : "<< walking << " RS/_" << endl;
    cout << "The total Earning by Dine-In customers are : "<< dineIn << " RS/_" << endl;
    cout << "The total Earning by Home Delivery customers are : "<< homeDelivery << " RS/_" << endl;
    cout << "The Total Earnings Are : " << total << " RS/_" << endl;
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
    myPizzaShop->menu = new string[11]{"",
        "chickenTikka", "arabicRanch",
        "chickenFajita", "cheeseLover",
        "chickenSupreme", "allveggie",
        "garlicWest", "BeefBold",
        "phantom", "mexicanDelight"};

    // setting the price

    myPizzaShop->price = new int[11]{0,2000, 2500, 2400, 2200, 2700, 2000, 2100, 3000, 3000, 2800};

    int option = -99;

    // now starting the main program
    do{

        cout << "-------------------------------------------------------------------------" << endl;
        cout << "---------------------------------"<<myPizzaShop->shopName <<"------------------------------" << endl;
        cout << "-------------------------------------------------------------------------" << endl;
        cout << "-------------------------------------------------------------------------" << endl;

        cout << "Located at " << myPizzaShop->address << endl;
        cout << "Our Menu is as follows: " << endl;
        for (int i = 1; i<=10; i++)
        {
            cout << i << ". " << myPizzaShop->menu[i] << " - " << myPizzaShop->price[i] << endl;
        }

        cout << "-------------------------------------------------------------------------" << endl;
        cout << "---------------------------------Operations------------------------------" << endl;
        cout << "-------------------------------------------------------------------------" << endl;
        cout << "-------------------------------------------------------------------------" << endl;

        // Order placing
        cout << "1. Place order for Walk-in Customer" << endl;
        cout << "2. Place order for Home Delivery Customer" << endl;
        cout << "3. Place order for Dine-In Customer" << endl;

        // order serving
        cout << "4. Serve order for Walk-in Customer" << endl;
        cout << "5. Serve order for Home Delivery Customer" << endl;
        cout << "6. Serve order for Dine-In Customer" << endl;
        cout << "7. Serve All Orders " << endl;

        // Displaying orders
        cout << "8. Display all orders of Walk in Customers" << endl;
        cout << "9. Display all orders of Home Delivery Customers" << endl;
        cout << "10. Display all orders of Dine-In Customers" << endl;
        cout << "11. Display all orders of all Customers" << endl;

        // Served orders
        cout << "12. Display all served Orders" << endl;
        cout << "13. Search Served Orders " << endl;
        cout << "14. Display total earnings of Shop" << endl;
        cout << "0.  EXIT " << endl;

        cout << "Enter your choice: ";

        cin >> option;

        // for taking input of Customer Details
        int age, quantity, pizzaIndex;
        double bill;
        string address;
        string name;

        switch (option)
        {
            case 1:
                // placing order for walk-in customer
                cout << "Enter the name of the customer: ";
                cin >> name;
                cout << "Enter the age of the customer: ";
                cin >> age;
                cout << "Enter the quantity of the pizza: ";
                cin >> quantity;
                cout << "Enter the option for the pizza: ";
                cin >> pizzaIndex;

                bill = quantity * myPizzaShop->price[pizzaIndex];
                placeOrderWalkingCustomer(age,name,myPizzaShop->menu[pizzaIndex],quantity,bill);
                break;

            case 2:

                // placing order for Home Delivery customer
                cout << "Enter the name of the customer: ";
                cin >> name;
                cout << "Enter the age of the customer: ";
                cin >> age;
                cout << "Enter the quantity of the pizza: ";
                cin >> quantity;
                cout << "Enter the option for the pizza: ";
                cin >> pizzaIndex;
                cout << "Enter the address of the customer: ";
                cin >> address;

                bill = quantity * myPizzaShop->price[pizzaIndex];
                placeOrderHomeDeliveryCustomer(age,name,myPizzaShop->menu[pizzaIndex],quantity,bill ,address);
                break;

            case 3:
                // placing order for Dine-in customer

                cout << "Enter the name of the customer: ";
                cin >> name;
                cout << "Enter the age of the customer: ";
                cin >> age;
                cout << "Enter the quantity of the pizza: ";
                cin >> quantity;
                cout << "Enter the option for the pizza: ";
                cin >> pizzaIndex;

                bill = quantity * myPizzaShop->price[pizzaIndex];
                placeOrderDineInCustomer(age,name,myPizzaShop->menu[pizzaIndex],quantity,bill);
                break;

            case 4:
                // serving order for walk-in customer
                serveOrderWalkingCustomer();
                break;

            case 5:
                // serving order for Home Delivery customer
                serveOrderHomeDeliveryCustomer();

                break;

            case 6:
                // serving order for Dine-in customer
                serveOrderDineInCustomer();
                break;

            case 7:
                // serving all orders
                serveAllOrders();
                break;

            case 8:
                // displaying all orders of walk-in customers
                displayAllOrdersWalkingCustomers();
                break;

            case 9:
                // displaying all orders of Home Delivery customers
                displayAllOrdersHomeDeliveryCustomers();
                break;

            case 10:
                // displaying all orders of Dine-in customers
                displayAllOrdersDineInCustomers();
                break;

            case 11:
                // displaying all orders of all customers
                displayAllOrders();
                break;

            case 12:
                // displaying all served orders
                displayAllServedOrders(root);
                break;
            case 13:
                // searching served orders
                cout << "Enter the name of the customer you want to search: "<<endl;
                cin >> name;
                servedCustomer *searchedCustomer =  search(root, name);
                if(searchedCustomer == NULL)
                    cout << "No such Customer was Served " << endl;
                else 
                    display(searchedCustomer);
                break;

        }

    } while (option != 0);

    cout << "Pizza Order Management System -- Terminated"<<endl;
    cout << "Thank you for Using our Services " << endl;

    return 0;
}