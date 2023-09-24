#include "Game.h"
#include <conio.h>

Game::Game()
{
	// Default constructor for the Game class.
	// Initializes the game state, setting it as not over, and uses a default board size of 4x4.
	gameOver = false;
	boardSize = 4;
}

Game::Game(int boardSize)
{
	// Parameterized constructor for the Game class.
	// Initializes the game state, setting it as not over, and allows specifying the board size.
	this->boardSize = boardSize;
	gameOver = false;
}

void Game::start()
{
	// Starts the game by displaying the game logo, instructions, and main menu.
	displayLogo();         // Display the game's logo or title.
	displayInstructions(); // Display instructions on how to play.
	menu();                // Display the main menu and wait for user input.
}

void Game::menu()
{
	// Clears the console screen and displays the main menu with options to play or access settings.

	system("cls"); // Clears the console screen.

	cout << "\n\n\n";
	cout << "===================================" << endl;
	cout << "             Game Menu             " << endl;
	cout << "===================================" << endl;
	cout << "1 - Play" << endl;
	cout << "2 - Settings" << endl;
	cout << "3 - Exit" << endl;
	cout << "===================================" << endl;
	cout << "Enter your choice: ";


	bool exit = true;

	do
	{
		char userInput;
		if (_kbhit())
		{
			userInput = _getch(); // Gets the key pressed by the user.

			switch (userInput)
			{
			case '1': // If the user presses '1', start the game.
				play();
				exit = false;
				break;
			case '2': // If the user presses '2', invoke the Settings() function and then set exit to false.
				Settings();
				exit = false;
				break;
			case '3':
				gameOver = true; // Exit the game
				exit = false;
				break;
			default:
				// cout << "\nInvalid input. Please enter a valid option: ";
				break;
			}
		}
	} while (exit);

	return; // Return from the menu function.
}


void Game::Settings()
{
	// Clear the screen and display the settings menu
	system("cls");

	cout << "\n\n\n";
	cout << "===================================" << endl;
	cout << "           Game Settings           " << endl;
	cout << "===================================" << endl;
	cout << "Board size:" << endl;
	cout << "1 - 4x4" << endl;
	cout << "2 - 6x6" << endl;
	cout << "3 - 8x8" << endl;
	cout << "4 - Custom" << endl;
	cout << "5 - Back" << endl;
	cout << "===================================" << endl;
	cout << "Enter your choice: ";

	bool exit = true;

	do
	{
		char userInput;
		if (_kbhit())
		{
			userInput = _getch();

			switch (userInput)
			{
			case '1': // Set the board size to 4x4 and exit the menu
				boardSize = 4;
				exit = false;
				break;

			case '2':// Set the board size to 6x6 and exit the menu
				boardSize = 6;
				exit = false;
				break;

			case '3':// Set the board size to 8x8 and exit the menu
				boardSize = 8;
				exit = false;
				break;

			case '4':
				cout << "\nEnter size: ";
				cin >> boardSize;
				// Check if the custom size is valid (4 or more)
				if (boardSize < 4)
				{
					cout << "Invalid size. Please enter a size of 4 or more." << endl;
				}
				else
				{
					// Custom size is valid, exit the menu
					exit = false;
				}
				break;

			case '5':// Exit the menu
				menu();
				break;

			default:// Invalid input, ask the user to enter a valid option
				cout << "\nInvalid input. Please enter a valid option: ";
				break;
			}
		}
	} while (exit);
}

void Game::play()
{
	// Initialize the game board with the chosen size and add an initial tile
	board = new GameBoard(boardSize);
	board->addTile();

	// Display the game board after each move
	board->displayBoard();

	// Continue the game loop until the game is over
	while (!gameOver)
	{
		// Check for user input and perform game actions
		if (board->hasMoves() && !board->isGameOver())
		{
			if (handleInput())
			{
				// Display the game board after each move
				board->displayBoard();

				// Add a new tile to the board
				board->addTile();

				// Pause briefly to display game changes
				Sleep(50);

				// Display the game board again after the new tile is added
				board->displayBoard();
			}
		}
		else
		{
			// Check if the game is over (win or lose conditions)
			displayGameOver();
		}
	}
}

bool Game::handleInput()
{
	char userInput;

	// Check if a key has been pressed
	if (_kbhit()) {
		userInput = _getch();

		// Determine the action based on the pressed key
		switch (userInput) {
		case 'a':
			// Move the tiles left and return whether the move is valid
			return board->moveLeft();

		case 'd':
			// Move the tiles right and return whether the move is valid
			return board->moveRight();

		case 'w':
			// Move the tiles up and return whether the move is valid
			return board->moveUp();

		case 's':
			// Move the tiles down and return whether the move is valid
			return board->moveDown();

		case '`':
			// Exit the game when the backtick key (`) is pressed
			gameOver = true;
			return false;

		default:
			break;
		}
	}

	// If no key was pressed or the key pressed had no specific action, return false
	return false;
}


void Game::displayLogo()
{
	// Get a handle to the console window for setting text attributes
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int textColor = 11;  // Initial text color
	int bgColor = 0;    // Initial background color
	int steps = 500;    // Number of color transition steps
	int delay = 50;     // Delay between color transitions in milliseconds

	// Set the console output to support UTF-8 characters
	SetConsoleOutputCP(CP_UTF8);

	// Define the console font size
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
	fontInfo.dwFontSize.X = 30;
	fontInfo.dwFontSize.Y = 30;
	SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

	// Set the initial text attributes (color)
	SetConsoleTextAttribute(hConsole, textColor | (bgColor << 4));

	// Define the ASCII art for the logo as an array of wide characters
	const wchar_t* arr[14];

	// Fill the array with the logo ASCII art
	// (each element in the array represents a line of the logo)

	arr[0] = L"\n\n\n\t\t\t█████████████████████████████████████████████████████████████";
	arr[1] = L"\n\t\t\t█░░░░░░░░░░░░░░█░░░░░░░░░░░░░░█░░░░░░██░░░░░░█░░░░░░░░░░░░░░█";
	arr[2] = L"\n\t\t\t█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█";
	arr[3] = L"\n\t\t\t█░░░░░░░░░░▄▀░░█░░▄▀░░░░░░▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀░░░░░░▄▀░░█";
	arr[4] = L"\n\t\t\t█████████░░▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀░░██░░▄▀░░█";
	arr[5] = L"\n\t\t\t█░░░░░░░░░░▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀░░░░░░▄▀░░█░░▄▀░░░░░░▄▀░░█";
	arr[6] = L"\n\t\t\t█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█";
	arr[7] = L"\n\t\t\t█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█";
	arr[8] = L"\n\t\t\t█░░▄▀░░░░░░░░░░█░░▄▀░░██░░▄▀░░█░░░░░░░░░░▄▀░░█░░▄▀░░░░░░▄▀░░█";
	arr[9] = L"\n\t\t\t█░░▄▀░░█████████░░▄▀░░██░░▄▀░░█████████░░▄▀░░█░░▄▀░░██░░▄▀░░█";
	arr[10] = L"\n\t\t\t█░░▄▀░░░░░░░░░░█░░▄▀░░░░░░▄▀░░█████████░░▄▀░░█░░▄▀░░░░░░▄▀░░█";
	arr[11] = L"\n\t\t\t█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█████████░░▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█";
	arr[12] = L"\n\t\t\t█░░░░░░░░░░░░░░█░░░░░░░░░░░░░░█████████░░░░░░█░░░░░░░░░░░░░░█";
	arr[13] = L"\n\t\t\t█████████████████████████████████████████████████████████████\n\t\t\t";

	// Loop through the array and write each line to the console
	for (int i = 0; i < 14; i++)
	{
		WriteConsoleW(hConsole, arr[i], wcslen(arr[i]), nullptr, nullptr);
	}

	// Perform a color transition animation
	for (int i = steps; i > 0; i--) {

		if (_kbhit()) {
			break;
		}
		textColor -= i;
		bgColor -= i;

		// Set the new text attributes (color) for the console
		SetConsoleTextAttribute(hConsole, textColor | (bgColor << 4));

		// Clear the console screen
		system("cls");

		// Redraw the logo with the new colors
		for (int j = 0; j < 14; j++)
		{
			WriteConsoleW(hConsole, arr[j], wcslen(arr[j]), nullptr, nullptr);
		}

		// Pause briefly to display the animation
		Sleep(delay);
	}

	// Restore the console text attributes to the default
	SetConsoleTextAttribute(hConsole, 7);
}


void Game::displayInstructions()
{
	// Get a handle to the console window for setting text attributes
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set the console output to support UTF-8 characters
	SetConsoleOutputCP(CP_UTF8);

	// Define the console font size
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
	fontInfo.dwFontSize.X = 30;
	fontInfo.dwFontSize.Y = 30;
	SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

	// Set the text attributes (color)
	SetConsoleTextAttribute(hConsole, 11 | (0 << 4));

	// Define the ASCII art for the instructions as an array of wide characters
	const wchar_t* arr[8];

	// Fill the array with the instruction ASCII art
	// (each element in the array represents a line of the instructions)

	arr[0] = L"\n\n\n\t\t\t\t\t         ______ ";
	arr[1] = L"\n\t\t\t\t\t        | W    |";
	arr[2] = L"\n\t\t\t\t\t        |___ __|";
	arr[3] = L"\n\t\t\t\t\t  ______   ______   ______";
	arr[4] = L"\n\t\t\t\t\t | A    | | S    | | D    |";
	arr[5] = L"\n\t\t\t\t\t |__ ___| |__ ___| |__ ___|\n\n\n";
	arr[6] = L"\n\t\t\t\t\t Use keyboard to controll\t\n\n\n";
	arr[7] = L"\n\t\t\t\t\t   Press F to continue\t";


	// Display a brief instruction on using the keyboard for control
	Sleep(100);
	system("cls");

	// Loop through the array and write each line to the console
	for (int i = 0; i < 8; i++)
	{
		if (i == 7)
		{
			Sleep(500);
		}
		WriteConsoleW(hConsole, arr[i], wcslen(arr[i]), nullptr, nullptr);
	}

	// Pause briefly to display the instructions

	char userInput;

	do
	{
		if (_kbhit())
		{
			userInput = _getch();

		}
	} while (userInput != 'f');
}

// Method to display the game-over or win message on the console.
void Game::displayGameOver()
{
	// Determine whether the player has won or lost
	bool win = board->isGameOver();

	// Get a handle to the console window for setting text attributes
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set the console output to support UTF-8 characters
	SetConsoleOutputCP(CP_UTF8);

	// Define the console font size
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
	fontInfo.dwFontSize.X = 30;
	fontInfo.dwFontSize.Y = 30;
	SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

	// Set the text attributes (color)
	SetConsoleTextAttribute(hConsole, 11 | (0 << 4));

	// Define ASCII art for the win and lose messages as arrays of wide characters
	const wchar_t* WIN[7];

	// Fill the array with ASCII art for the win message
	WIN[0] = L"\n\n";
	WIN[1] = L"\n\t\t\t   ██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗██╗███╗   ██╗\n";
	WIN[2] = L"\n\t\t\t   ██║   ██║██╔═══██╗╚██╗ ██╔╝    ██║    ██║██║████╗  ██║\n";
	WIN[3] = L"\n\t\t\t   ██║   ██║██║   ██║ ╚████╔╝     ██║ █╗ ██║██║██╔██╗ ██║\n";
	WIN[4] = L"\n\t\t\t   ██║   ██║██║   ██║  ╚██╔╝      ██║███╗██║██║██║╚██╗██║\n";
	WIN[5] = L"\n\t\t\t   ╚██████╔╝╚██████╔╝   ██║       ╚███╔███╔╝██║██║ ╚████║\n";
	WIN[6] = L"\n\t\t\t    ╚═════╝  ╚═════╝    ╚═╝        ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝\n";

	// Define ASCII art for the lose message
	const wchar_t* LOS[7];

	// Fill the array with ASCII art for the lose message
	LOS[0] = L"\n\n";
	LOS[1] = L"\n\t\t\t   ██████╗ ██╗   ██╗███╗   ██╗ ██████╗ ██████╗  ██████╗ \n";
	LOS[2] = L"\n\t\t\t  ██╔═══██╗██║   ██║████╗  ██║██╔════╝ ██╔══██╗██╔═══██╗\n";
	LOS[3] = L"\n\t\t\t  ██║   ██║██║   ██║██╔██╗ ██║██║  ███╗██████╔╝██║   ██║\n";
	LOS[4] = L"\n\t\t\t  ██║   ██║██║   ██║██║╚██╗██║██║   ██║██╔══██╗██║   ██║\n";
	LOS[5] = L"\n\t\t\t  ╚██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝██████╔╝╚██████╔╝\n";
	LOS[6] = L"\n\t\t\t   ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═════╝  ╚═════╝ \n";

	// Display a brief instruction on using the keyboard for control
	Sleep(100);
	system("cls");

	// Loop through the array and write each line to the console
	for (int i = 0; i < 7; i++)
	{
		if (win)
		{
			// Display the win message
			WriteConsoleW(hConsole, WIN[i], wcslen(WIN[i]), nullptr, nullptr);
		}
		else
		{
			// Display the lose message
			WriteConsoleW(hConsole, LOS[i], wcslen(LOS[i]), nullptr, nullptr);
		}
	}
	gameOver = true;
}
