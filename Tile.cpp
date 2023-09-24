#include "Tile.h"

// Constructor to initialize a Tile with a given value, row, and column.
Tile::Tile(int value, int row, int col)
{
    this->value = value;
    this->row = row;
    this->col = col;
}

// Getter method to retrieve the value of the tile.
int Tile::getValue()
{
    Tile const* a = this;
    if (a == nullptr)
    {
        return -1;
    }
    return value;
}

// Setter method to set the value of the tile.
void Tile::setValue(int Value)
{
    this->value = Value;
}

// Getter method to retrieve the row position of the tile on the game board.
int Tile::getRow()
{
    return row;
}

// Getter method to retrieve the column position of the tile on the game board.
int Tile::getCol()
{
    return col;
}

