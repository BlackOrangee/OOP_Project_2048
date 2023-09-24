#include "GameBoard.h"

// Constructor to initialize a new GameBoard with the given size.
GameBoard::GameBoard(int size)
{
	this->size = size;  // Initialize the size of the game board.

	// Allocate memory for the 2D array of Tile pointers to represent the game board.
	tiles = new Tile * *[size];

	// Loop through rows and columns to initialize each Tile on the board.
	for (int i = 0; i < size; i++)
	{
		tiles[i] = new Tile * [size];  // Allocate memory for each row.

		for (int j = 0; j < size; j++)
		{
			// Create a new Tile with a value of 0 (empty) at the specified row and column.
			tiles[i][j] = new Tile(0, i, j);
		}
	}
}

// Method to add a new Tile to a random empty position on the board.
void GameBoard::addTile()
{
	// Check if there's at least one empty position on the board
	bool canSpawn = false;

	// Create a vector to store references to empty tiles
	vector<Tile*> emptyTiles;

	// Iterate through the board to find empty tiles and store their references
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			// If a tile is empty (has a value of 0), mark that we can spawn a new tile
			if (tiles[i][j]->getValue() == 0)
			{
				canSpawn = true;
				// Store a reference to this empty tile in the vector
				emptyTiles.push_back(tiles[i][j]);
			}
		}
	}

	// If there are no empty positions, exit the method
	if (!canSpawn)
	{
		return;
	}

	// Seed the random number generator with the current time
	random_device rd;  // Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	uniform_int_distribution<> dis(0, emptyTiles.size() - 1);

	// Generate a random index within the range of available empty tiles
	int randomIndex = dis(gen);

	// Determine the value of the new tile (90% chance of 2, 10% chance of 4)
	uniform_int_distribution<> dis2(0, 100);
	int tileValue = (dis2(gen) >= 90) ? 4 : 2;

	// Set the value of the randomly chosen empty tile to the determined value
	tiles[emptyTiles[randomIndex]->getRow()][emptyTiles[randomIndex]->getCol()]->setValue(tileValue);
}


// Methods to move tiles in different directions, return true if any move was made.
bool GameBoard::moveLeft()
{
	// Iterate through each row of the game board
	for (int i = 0; i < size; i++)
	{
		// Collect the tiles in the current row into a list
		List* list = collectRow(i);

		// Create an empty list to store modified tiles
		auto* list2 = new List();

		do
		{
			// Check if the top tile in the list has a value of 0 (empty)
			if (list->top()->getValue() == 0)
			{
				// Pop the empty tile from the list
				list->pop();
			}
			else
			{
				// Push non-empty tiles to the second list
				list2->addToBack(list->pop());
			}

		} while (list->top() != nullptr);

		// Set the first list to the second list (containing modified tiles)
		list = list2;

		// Iterate through each column in the row
		for (int j = 0; j < size; j++)
		{
			Tile* tile1;

			// Pop a tile from the list (if any are left)
			tile1 = list->pop();

			if (tile1 == nullptr)
			{
				break;
			}

			// Check if the current tile has the same value as the next tile
			if (tile1->getValue() == list->top()->getValue())
			{
				// Merge the two tiles by doubling the value
				tiles[i][j]->setValue(list->pop()->getValue() * 2);
			}
			else if (tile1->getValue() != list->top()->getValue())
			{
				// Move the current tile without merging
				tiles[i][j]->setValue(tile1->getValue());
			}
			else
			{
				// The tiles cannot be merged, set the current tile to 0
				tiles[i][j]->setValue(0);
			}
		}
		delete list;
	}
	
	// Return true to indicate a successful move
	return true;
}

bool GameBoard::moveRight()
{
	// Loop through each row from right to left
	for (int i = size - 1; i >= 0; i--)
	{
		// Collect the tiles in the current row
		List* list = collectRow(i);

		// Create a new list to store merged or shifted tiles
		auto* list2 = new List();

		// Iterate through the collected tiles
		do
		{
			// If the top tile has a value of 0, pop it (skip empty tiles)
			if (list->top()->getValue() == 0)
			{
				list->pop();
			}
			else // Otherwise, add it to the new list for merging or shifting
			{
				list2->addToBack(list->pop());
			}
		} while (list->top() != nullptr);

		// Replace the original list with the new list
		list = list2;

		// Iterate through the row from right to left
		for (int j = size - 1; j >= 0; j--)
		{
			Tile* tile1;

			// Pop a tile from the new list
			tile1 = list->popBack();

			// If there are no more tiles, break the loop
			if (tile1 == nullptr)
			{
				break;
			}

			// If the current tile has the same value as the tile next to it (on the right)
			if (tile1->getValue() == list->topBack()->getValue())
			{
				// Double the value of the current tile (merge the tiles)
				tiles[i][j]->setValue(list->popBack()->getValue() * 2);
			}
			// If the current tile has a different value than the tile next to it
			else if (tile1->getValue() != list->topBack()->getValue())
			{
				// Set the current tile's value to its own value (no merge)
				tiles[i][j]->setValue(tile1->getValue());
			}
			else // If none of the above conditions match (shouldn't happen), set the current tile's value to 0
			{
				tiles[i][j]->setValue(0);
			}
		}
		delete list;
	}
	// Return true to indicate a successful move
	return true;
}


bool GameBoard::moveUp()
{
	// Iterate through each column from top to bottom
	for (int j = 0; j < size; j++)
	{
		// Collect the tiles in the current column
		List* list = collectCol(j);

		// Create a new list to store merged or shifted tiles
		auto* list2 = new List();

		// Iterate through the collected tiles
		do
		{
			// If the top tile has a value of 0, pop it (skip empty tiles)
			if (list->top()->getValue() == 0)
			{
				list->pop();
			}
			// Otherwise, add it to the new list for merging or shifting
			else
			{
				list2->addToBack(list->pop());
			}
		} while (list->top() != nullptr);

		// Replace the original list with the new list
		list = list2;

		// Iterate through the column from top to bottom
		for (int i = 0; i < size; i++)
		{
			Tile* tile1;

			// Pop a tile from the new list
			tile1 = list->pop();

			// If there are no more tiles, break the loop
			if (tile1 == nullptr)
			{
				break;
			}

			// If the current tile has the same value as the tile below it (in the column)
			if (tile1->getValue() == list->top()->getValue())
			{
				// Double the value of the current tile (merge the tiles)
				tiles[i][j]->setValue(list->pop()->getValue() * 2);
			}
			// If the current tile has a different value than the tile below it
			else if (tile1->getValue() != list->top()->getValue())
			{
				// Set the current tile's value to its own value (no merge)
				tiles[i][j]->setValue(tile1->getValue());
			}
			// If none of the above conditions match (shouldn't happen), set the current tile's value to 0
			else
			{
				tiles[i][j]->setValue(0);
			}
		}
		delete list;
	}
	// Return true to indicate a successful move
	return true;
}


bool GameBoard::moveDown()
{
	// Iterate through each column from bottom to top
	for (int j = size - 1; j >= 0; j--)
	{
		// Collect the tiles in the current column
		List* list = collectCol(j);

		// Create a new list to store merged or shifted tiles
		auto* list2 = new List();

		// Iterate through the collected tiles
		do
		{
			// If the top tile has a value of 0, pop it (skip empty tiles)
			if (list->top()->getValue() == 0)
			{
				list->pop();
			}
			// Otherwise, add it to the new list for merging or shifting
			else
			{
				list2->addToBack(list->pop());
			}
		} while (list->top() != nullptr);

		// Replace the original list with the new list
		list = list2;

		// Iterate through the column from bottom to top
		for (int i = size - 1; i >= 0; i--)
		{
			Tile* tile1;

			// Pop a tile from the new list
			tile1 = list->popBack();

			// If there are no more tiles, break the loop
			if (tile1 == nullptr)
			{
				break;
			}

			// If the current tile has the same value as the tile above it (in the column)
			if (tile1->getValue() == list->topBack()->getValue())
			{
				// Double the value of the current tile (merge the tiles)
				tiles[i][j]->setValue(list->popBack()->getValue() * 2);
			}
			// If the current tile has a different value than the tile above it
			else if (tile1->getValue() != list->topBack()->getValue())
			{
				// Set the current tile's value to its own value (no merge)
				tiles[i][j]->setValue(tile1->getValue());
			}
			// If none of the above conditions match (shouldn't happen), set the current tile's value to 0
			else
			{
				tiles[i][j]->setValue(0);
			}
		}
		delete list;
	}
	// Return true to indicate a successful move
	return true;
}


// Check if there are any legal moves left on the game board.
// return true if there is at least one valid move, otherwise false.
bool GameBoard::hasMoves()
{
	// Iterate through each row and column of the game board
	for (int i = 0; i < size; i++)
	{
		// Check for valid moves in both rows and columns
		if (hasValidMoveInRow(i) || hasValidMoveInColumn(i))
		{
			// Return true as soon as a valid move is found
			return true;
		}
	}

	// If no valid moves are found after iterating through all rows and columns, return false
	return false;
}

// Check if there is at least one valid move in a specific row.
bool GameBoard::hasValidMoveInRow(int rowIndex)
{
	int temp = tiles[rowIndex][0]->getValue();

	// Iterate through the tiles in the current row
	for (int j = 1; j < size; j++)
	{
		// Check if the current tile is empty (has a value of 0)
		// OR if it has the same value as the previous tile in the row
		if (tiles[rowIndex][j]->getValue() == 0 || tiles[rowIndex][j]->getValue() == temp)
		{
			// Return true as soon as a valid move is found in the row
			return true;
		}

		// Update the temporary variable with the current tile's value for the next iteration
		temp = tiles[rowIndex][j]->getValue();
	}

	// If no valid move is found in the row, return false
	return false;
}

// Check if there is at least one valid move in a specific column.
bool GameBoard::hasValidMoveInColumn(int columnIndex)
{
	int temp = tiles[0][columnIndex]->getValue();

	// Iterate through the tiles in the current column
	for (int i = 1; i < size; i++)
	{
		// Check if the current tile is empty (has a value of 0)
		// OR if it has the same value as the previous tile in the column
		if (tiles[i][columnIndex]->getValue() == 0 || tiles[i][columnIndex]->getValue() == temp)
		{
			// Return true as soon as a valid move is found in the column
			return true;
		}

		// Update the temporary variable with the current tile's value for the next iteration
		temp = tiles[i][columnIndex]->getValue();
	}

	// If no valid move is found in the column, return false
	return false;
}


bool GameBoard::isGameOver()
{
	// Iterate through each tile on the game board
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			// Check if the value of the current tile is equal to 2048
			if (tiles[i][j]->getValue() == 2048)
			{
				// If a tile with the value 2048 is found, return true,
				// indicating that the game is over (player has won)
				return true;
			}
		}
	}

	// If no tile with the value 2048 is found after checking all tiles,
	// return false, indicating that the game is not over (player has not won)
	return false;
}

int GameBoard::displayTilesSupporter(int tileValue, int& bgColor, int& textColor)
{
	// This function is used to set the background (bgColor) and text (textColor) colors
	// for displaying different tile values on the game board. It takes the current tile's
	// value as input and modifies the bgColor and textColor parameters accordingly.

	// Using a switch statement to match the tileValue and set appropriate colors.
	switch (tileValue)
	{
	case 0:
		// For tiles with a value of 0, set both background and text color to the same shade of gray.
		bgColor = 5; // Gray background
		textColor = 5; // Gray text
		break;
	case 2:
	case 4:
		// For tiles with a value of 2 and 4 set a light gray background with black text.
		bgColor = 7; // Light gray background
		textColor = 0; // Black text
		break;
	case 8:
		// Continue this pattern for other tile values, setting appropriate colors.
		bgColor = 14; // Yellow background
		textColor = 0; // Black text
		break;
	case 16:
		bgColor = 12; // Blue background
		textColor = 0; // Black text
		break;
	case 32:
		bgColor = 4; // Red background
		textColor = 0; // Black text
		break;
	case 64:
		bgColor = 14; // Yellow background
		textColor = 1; // White text
		break;
	case 128:
		bgColor = 6; // Light cyan background
		textColor = 0; // Black text
		break;
	case 256:
		bgColor = 11; // Light magenta background
		textColor = 1; // White text
		break;
	case 512:
		bgColor = 3; // Dark cyan background
		textColor = 0; // Black text
		break;
	case 1024:
		bgColor = 10; // Light green background
		textColor = 0; // Black text
		break;
	case 2048:
		bgColor = 2; // Green background
		textColor = 0; // Black text
		break;
	default:
		break;
	}

	// The function returns the original tileValue, which is used for display purposes.
	return tileValue;
}

void GameBoard::displayBoard()
{
	// Sleep to control the display speed.
	Sleep(150);

	// Clear the console screen.
	system("cls");

	// Loop through each row of the game board.
	for (int row = 0; row < size; ++row)
	{
		if (row == 0)
		{
			cout << "\n"; // Add a newline before the first row.
		}

		for (int col = 0; col < size; ++col)
		{
			if (col == 0)
			{
				cout << "  "; // Add spacing before the first column.
			}

			int bgColor;
			int textColor;

			// Get the tile value and associated colors using the displayTilesSupporter function.
			int tileValue = displayTilesSupporter(tiles[row][col]->getValue(), bgColor, textColor);

			// Get a handle to the console to manipulate text attributes.
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			// Define a font size based on the game board size.
			CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
			GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

			if (size == 4)
			{
				// For a 4x4 board, use a larger font size.
				fontInfo.dwFontSize.X = 160;
				fontInfo.dwFontSize.Y = 160;
			}
			else
			{
				// For other board sizes, use a smaller font size.
				fontInfo.dwFontSize.X = 25;
				fontInfo.dwFontSize.Y = 25;
			}

			// Apply the selected font size to the console.
			SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

			// Set the text attributes to display the tile with the chosen colors.
			SetConsoleTextAttribute(hConsole, WORD(textColor | (bgColor << 4)));

			// Display the tile's value with appropriate spacing.
			if (tileValue < 10)
			{
				cout << " " << tileValue << "  ";
			}
			else if (tileValue < 100)
			{
				cout << " " << tileValue << " ";
			}
			else if (tileValue < 1000)
			{
				cout << " " << tileValue;
			}
			else
			{
				cout << tileValue;
			}

			// Reset the console's text attributes to default (white text on black background).
			SetConsoleTextAttribute(hConsole, 7);
		}
		cout << endl; // Move to the next row with a newline.
	}
}

List* GameBoard::collectRow(int i)
{
	// Create a new List to collect the tiles from the specified row.
	auto* list = new List(new Tile(tiles[i][0]->getValue(), tiles[i][0]->getRow(), tiles[i][0]->getCol()));

	// Set the value of the first tile in the row to 0 (indicating an empty tile).
	tiles[i][0]->setValue(0);

	// Loop through the remaining tiles in the row.
	for (int j = 1; j < size; j++)
	{
		// Add a new Tile to the List with the value, row, and column of the current tile.
		list->addToBack(new Tile(tiles[i][j]->getValue(), tiles[i][j]->getRow(), tiles[i][j]->getCol()));

		// Set the value of the current tile to 0 (indicating an empty tile).
		tiles[i][j]->setValue(0);
	}

	// Return the List containing the collected tiles from the row.
	return list;
}


List* GameBoard::collectCol(int j)
{
	// Create a new List to collect the tiles from the specified col.
	auto* list = new List(new Tile(tiles[0][j]->getValue(), tiles[0][j]->getRow(), tiles[0][j]->getCol()));

	// Set the value of the first tile in the row to 0 (indicating an empty tile).
	tiles[0][j]->setValue(0);

	// Loop through the remaining tiles in the row.
	for (int i = 1; i < size; i++)
	{
		// Add a new Tile to the List with the value, row, and column of the current tile.
		list->addToBack(new Tile(tiles[i][j]->getValue(), tiles[i][j]->getRow(), tiles[i][j]->getCol()));

		// Set the value of the current tile to 0 (indicating an empty tile).
		tiles[i][j]->setValue(0);
	}

	// Return the List containing the collected tiles from the row.
	return list;
}