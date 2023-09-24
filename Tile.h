#pragma once
#include <iostream>
using namespace std;

class Tile
{
private:
    int value;  // The value associated with the tile.
    int row;    // The row position of the tile on a game board.
    int col;    // The column position of the tile on a game board.

public:
    // Constructor to initialize a Tile with a given value, row, and column.
    Tile(int value, int row, int col);

    // Getter method to retrieve the value of the tile.
    int getValue();

    // Setter method to set the value of the tile.
    void setValue(int value);

    // Getter method to retrieve the row position of the tile on the game board.
    int getRow();

    // Getter method to retrieve the column position of the tile on the game board.
    int getCol();
};


