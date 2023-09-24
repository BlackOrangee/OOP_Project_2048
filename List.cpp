#include "List.h"

// Default constructor for the Node class.
List::Node::Node()
{
    value = nullptr;
    next = nullptr;
    prev = nullptr;
};

// Constructor for the Node class that initializes it with a Tile pointer.
List::Node::Node(Tile* value)
{
    this->value = value;
    next = nullptr;
    prev = nullptr;
}

// Default constructor for the List class.
List::List()
{
    head = nullptr;
    tail = nullptr;
}

// Constructor for the List class that initializes it with a starting Tile.
List::List(Tile* value)
{
    head = new Node(value);
    tail = head;
    head->next = nullptr; // Set the next pointer to nullptr
    head->prev = nullptr; // Set the prev pointer to nullptr
}

// Add a new Tile to the back (tail) of the list.
void List::addToBack(Tile* value)
{
    if (tail == nullptr)
    {
        // If the list is empty, create a new Node and set it as both the head and tail.
        tail = new Node(value);
        head = tail;
        return;
    }

    // Create a new Node and attach it to the current tail.
    tail->next = new Node(value);

    // Update the new Node's previous pointer to the current tail.
    tail->next->prev = tail;

    // Update the tail to the new Node.
    tail = tail->next;
}

// Add a new Tile to the front (head) of the list.
void List::addToHead(Tile* value)
{
    if (head == nullptr)
    {
        // If the list is empty, create a new Node and set it as both the head and tail.
        head = new Node(value);
        tail = head;
        return;
    }

    // Create a new Node and attach it to the current head.
    head->prev = new Node(value);

    // Update the new Node's next pointer to the current head.
    head->prev->next = head;

    // Update the head to the new Node.
    head = head->prev;
}

// Get the Tile at the front (head) of the list without removing it.
Tile* List::top()
{
    if (head == nullptr)
    {
        // If the list is empty, return nullptr.
        return nullptr;
    }
    // Return the Tile stored in the head Node.
    return head->value;
}

// Remove and return the Tile at the front (head) of the list.
Tile* List::pop()
{
    if (head == nullptr)
    {
        // If the list is empty, return nullptr.
        return nullptr;
    }

    // Store the Tile from the head Node.
    Tile* ret = head->value;

    // Move the head to the next Node.
    head = head->next;

    // Return the stored Tile.
    return ret;
}

// Get the Tile at the back (tail) of the list without removing it.
Tile* List::topBack()
{
    if (tail == nullptr)
    {
        // If the list is empty, return nullptr.
        return nullptr;
    }
    // Return the Tile stored in the tail Node.
    return tail->value;
}

// Remove and return the Tile at the back (tail) of the list.
Tile* List::popBack()
{
    if (tail == nullptr)
    {
        // If the list is empty, return nullptr.
        return nullptr;
    }

    // Store the Tile from the tail Node.
    Tile* ret = tail->value;

    // Move the tail to the previous Node.
    tail = tail->prev;

    // Return the stored Tile.
    return ret;
}
