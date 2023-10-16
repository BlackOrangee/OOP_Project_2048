#pragma once
#include "GameBoard.h"
#include <string>
#include <conio.h>  // Include for _getch() function.

class Game
{
private:
    GameBoard* board;   // Pointer to a GameBoard object for the game.
    bool gameOver;      // Flag indicating whether the game is over.
    int boardSize;      // Size of the game board.

public:
    // Default constructor.
    Game();

    // Parameterized constructor that allows setting the board size.
    Game(int boardSize);

    // Starts the game.
    void start();

    // Main game loop where the game play happens.
    void play();

    // Displays the main menu.
    void menu();

    // Displays and handles game settings.
    void Settings();

    // Handles user input during the game.
    bool handleInput();

    // Displays the game logo or title.
    void displayLogo();

    // Displays instructions on how to play the game.
    void displayInstructions();

    // Displays the game over message when the game ends.
    void displayGameOver();
};

