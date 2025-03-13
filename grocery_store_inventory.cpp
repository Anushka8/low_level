/******************************************************************************
 * Title: Grocery Store Inventory List
 * Author: Anushka Churi
 * Date: March 13, 2025
 * Description: The program simualted a grocery store invenotry. The user can
 *              add, remove and delete items from the inventory.
 * Topics: dynamic memory, manual deallocation, linked list
 *****************************************************************************/

#include <iostream>

using namespace std;

class GroceryItem
{
public:
    string name;
    float price;
    int quantity;
    GroceryItem *next;

    // constructor that initializes name, price and quantity and  points next to null
    GroceryItem(string n, float p, int q) : name(n), price(p), quantity(q), next(nullptr) {}
};

class Inventory
{
private:
    GroceryItem *head;

public:
    Inventory() : head(nullptr) {}

    void addItem(string name, float price, int quantity)
    {
        // create a new item
        GroceryItem *newItem = new GroceryItem(name, price, quantity);
        // set next to prev (current head)
        newItem->next = head;
        // set new item to head
        head = newItem;
        cout << "Added: " << name << "(Quantity: " << quantity << ", Price: $" << price << endl;
    }

    void removeItem(string name)
    {
        // store current head in a temp variable and create a prev
        GroceryItem *temp = head;
        GroceryItem *prev = nullptr;

        // move pointer till it points to the desired name
        while (temp != nullptr && temp->name != name)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr)
        {
            cout << "Item not found!\n";
            return;
        }

        // check if prev points to null, else remove the name
        if (prev == nullptr)
        {
            head = temp->next;
        }
        else
        {
            prev->next = temp->next;
        }

        cout << "Removed: " << name << endl;
        delete temp;
    }

    void displayItems()
    {
        GroceryItem *temp = head;

        while (temp)
        {
            cout << temp->name << "(Quantity: " << temp->quantity << ", Price: $" << temp->price << endl;
            temp = temp->next;
        }
    }

    ~Inventory()
    {
        while (head)
        {
            GroceryItem *temp = head;
            head = head->next;
            delete temp;
        }
        cout << "Inventory memory cleaned up";
    }
};

int main()
{
    Inventory store;

    store.addItem("Apples", 1.5, 50);
    store.addItem("Bananas", 0.8, 100);
    store.addItem("Milk", 3.2, 30);

    store.displayItems();

    store.removeItem("Bananas");
    store.displayItems();

    return 0;
}