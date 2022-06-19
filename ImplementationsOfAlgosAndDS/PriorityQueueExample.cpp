#include <iostream>
using namespace std;

struct PizzaQueue
{
    int rear = -1;
    int front = -1;
    int size;
    int *age;
    string *orderedPizza;
    int *orderNumber;
};

PizzaQueue *q = NULL; // making of a global
int orderID = 0;

int isFull()
{
    if (((q->rear + 1) % q->size) == q->front)
    {
        return 1;
    }
    return 0;
}

int isEmpty()
{
    if (q->rear == -1 && q->front == -1)
    {
        return 1;
    }
    return 0;
}

void placeOrder(int age, string value, int orderNo)
{

    int pos;

    if (isFull() == 1)
    {
        // full ho tou return kr jao aur btado k aisa nhi hoskta!
        cout << "We cannot place your Order! Kindly wait for the previous orders to be completed ! " << endl;
        return;
    }

    else if (isEmpty() == 1)
    {
        // khali ho tou first element hoga jo hoga aur aik single element k liay
        // priority check nhi krni!
        q->rear = q->front = 0;
        q->orderedPizza[q->rear] = value;
        q->orderNumber[q->rear] = orderNo;
        q->age[q->rear] = age;

        cout << "Your Order is placed with ID " << q->orderNumber[q->rear] << endl;
        cout << "The Ordered item is " << q->orderedPizza[q->rear] << endl;
    }

    else
    {
        bool f1 = false; // to check if shifting happened or not .
        // This is costly operation
        pos = q->rear;
        while (pos >= 0 && q->age[pos] < age)
        {
            // right shifting
            q->orderedPizza[pos + 1 % q->size] = q->orderedPizza[pos];
            q->age[pos + 1 % q->size] = q->age[pos];
            q->orderNumber[pos + 1 % q->size] = q->orderNumber[pos];
            pos = (pos - 1);
            f1 = true;
        }

        if (f1 == false)
        {
            // ager shiting nhi hui hogi tou pehle increment hoga!
            q->rear = q->rear + 1 % q->size;
        }

        q->orderedPizza[q->rear] = value;
        q->orderNumber[q->rear] = orderNo;
        q->age[q->rear] = age;
        cout << "Your Order is placed with ID " << q->orderNumber[q->rear] << endl;
        cout << "The Ordered item is " << q->orderedPizza[q->rear] << endl;

        if (f1 == true)
        {
            // ager shifting hui hogi tou hi bad main increment hoga!
            q->rear = (q->rear + 1) % q->size;
        }
    }
}

void orderDequeue()
{
    if (isEmpty() == 1)
    {
        cout << "There is no order in the Queue " << endl;
        orderID = 0;
        return;
    }

    else if (q->rear == q->front)
    {
        cout << "The order completed is ID Number " << q->orderNumber[q->front] << endl;
        cout << "The order Completed is  " << q->orderedPizza[q->front] << endl;
        q->rear = q->front = -1;
    }
    else
    {
        cout << "The order completed is ID Number " << q->orderNumber[q->front] << endl;
        cout << "The order Completed is " << q->orderedPizza[q->front] << endl;
        q->front = (q->front + 1) % q->size;
    }
}

void display()
{
    if (isEmpty() == 1)
    {
        cout << "There is no order in the queue!" << endl;
        return;
    }
    else
    {
        //  in case of printing
        int i = q->front;
        while (i != q->rear)
        {
            if (q->orderedPizza[i] != "")
            {
                cout << "ID Number : " << q->orderNumber[i] << endl;
                cout << "Ordered Item :  " << q->orderedPizza[i] << endl;
            }
            i = (i + 1) % q->size;
        }

        cout << "ID Number : " << q->orderNumber[q->rear] << endl;
        cout << "Ordered Item :  " << q->orderedPizza[q->rear] << endl;
    }
}

void CurrentOrder()
{
    if (isEmpty() == 1)
    {
        cout << "There is no Order in the queue !" << endl;
        return;
    }

    // front element
    cout << "The Current Order ID is " << q->orderNumber[q->front] << endl;
    cout << "The Current Order is " << q->orderedPizza[q->front] << endl;
}

void latestOrder()
{
    if (isEmpty() == 1)
    {
        cout << "There is no Order in the Queue " << endl;
        return;
    }

    // rear element
    cout << "The Current Order ID is " << q->orderNumber[q->rear] << endl;
    cout << "The Latest order is " << q->orderedPizza[q->rear] << endl;
}

int main()
{
    q = new PizzaQueue; // DMA things
    int size;
    cout << "State the number of Orders \n";
    cin >> size;
    q->size = size;
    q->orderedPizza = new string[q->size];
    q->orderNumber = new int[q->size];
    q->age = new int[q->size];

    for (int i = 0; i < size; i++)
    {
        q->orderedPizza[i] = "";
        q->age[i] = 0;
    }

    int option;

    do
    {
        cout << "--------------------------------------------------\n";
        cout << "Enter options to perform corresponding actions \n";

        cout << "1 -  Place Order\n"
             << "2 -  Complete Current Order\n"
             << "3 -  Display\n"
             << "4 -  Current Order\n"
             << "5-   Latest order\n"
             << "-1 - Exit\n";
        cout << "--------------------------------------------------\n";

        cin >> option;
        switch (option)
        {
        case 1:
        {
            int age;
            cout << "Enter Age" << endl;
            cin >> age;

            int val;
            cout << "Menu : \n"
                 << "0) Chicken Fajita \n"
                 << "1) Chicken Tikka \n"
                 << "2) Cheese Lover \n"
                 << "3) Barbeque Special \n"
                 << "4) Seekh Kabab Pizza \n"
                 << "5) Super Italian \n ";

            cout << "Enter value \n";
            string pizzaList[6] = {"Chicken Fajita", "Chicken Tikka", "Cheese Lover", "Barbeque Special", "Seekh Kabab Pizza", "Super Italian"};

            cin >> val;
            if (val >= 0 && val <= 5)
            {
                // cout << "Pakistan Noor hai !"

                placeOrder(age, pizzaList[val], ++orderID);
                break;
            }
            else
            {
                continue;
            }
        }

        case 2:
        {
            orderDequeue();
            break;
        }

        case 3:
        {
            display();
            break;
        }
        case 4:
        {
            CurrentOrder();
            break;
        }
        case 5:
        {
            latestOrder();
            break;
        }
        case -1:
        {
            cout << "exiting . . . \n";
            break;
        }
        }
    } while (option != -1);

    return 0;
}
