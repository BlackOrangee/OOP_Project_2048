#pragma once
#include <iostream>
#include "Tile.h"
#include "List.h"
#include "windows.h "
#include <vector>
#include <random>

using namespace std;

class GameBoard
{
private:
    int size;        // The size of the game board (size x size)
    Tile*** tiles;   // A 2D array of Tile pointers to represent the game board.

public:
    // Constructor to initialize a new GameBoard with the given size.
    GameBoard(int size);

    // Method to add a new Tile to a random empty position on the board.
    void addTile();

    // Methods to move tiles in different directions, return true if any move was made.
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();

    // Check if there are any legal moves left on the board.
    bool hasMoves();
    bool hasValidMoveInRow(int);
    bool hasValidMoveInColumn(int);

    // Check if the game is over (no legal moves left).
    bool isGameOver();

    int displayTilesSupporter(int, int&, int&);

    // Display the current state of the game board.
    void displayBoard();

    // Collect the tiles from a specified row into a List.
    List* collectRow(int);

    // Collect the tiles from a specified column into a List.
    List* collectCol(int);
};

