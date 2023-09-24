#pragma once
#include "Tile.h"

class List
{
private:
    class Node
    {
    public:
        Tile* value;  // Pointer to a Tile object.
        Node* next;   // Pointer to the next Node in the list.
        Node* prev;   // Pointer to the previous Node in the list.

        // Default constructor for Node.
        Node();

        // Constructor for Node that initializes it with a Tile pointer.
        Node(Tile*);
    };
    Node* head; // Pointer to the first Node in the list (head).
    Node* tail; // Pointer to the last Node in the list (tail).

public:
    // Default constructor for List.
    List();

    // Constructor for List that initializes it with a starting Tile.
    List(Tile*);

    // Add a new Tile to the front (head) of the list.
    void addToHead(Tile*);

    // Add a new Tile to the back (tail) of the list.
    void addToBack(Tile*);

    // Get the Tile at the front (head) of the list without removing it.
    Tile* top();

    // Remove and return the Tile at the front (head) of the list.
    Tile* pop();

    // Get the Tile at the back (tail) of the list without removing it.
    Tile* topBack();

    // Remove and return the Tile at the back (tail) of the list.
    Tile* popBack();
};


