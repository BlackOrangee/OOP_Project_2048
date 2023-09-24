#include "Game.h"
#include <conio.h>

Game::Game()
{
	// Default constructor for the Game class.
	// Initializes the game state, setting it as not over, and uses a default board size of 4x4.
	board = nullptr;
	gameOver = false;
	boardSize = 4;
}

Game::Game(int boardSize)
{
	// Parameterized constructor for the Game class.
	// Initializes the game state, setting it as not over, and allows specifying the board size.
	board = nullptr;
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
	cout << "\t\t\t\t===================================" << endl;
	cout << "\t\t\t\t             Game Menu             " << endl;
	cout << "\t\t\t\t===================================" << endl;
	cout << "\t\t\t\t1 - Play" << endl;
	cout << "\t\t\t\t2 - Settings" << endl;
	cout << "\t\t\t\t3 - Exit" << endl;
	cout << "\t\t\t\t===================================" << endl;
	cout << "\t\t\t\tEnter your choice: ";

	bool exit = true;

	do
	{
		int userInput;
		if (!_kbhit())
		{
			continue;
		}
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
		
	} while (exit);
}


void Game::Settings()
{
	// Clear the screen and display the settings menu
	system("cls");

	cout << "\n\n\n";
	cout << "\t\t\t\t===================================" << endl;
	cout << "\t\t\t\t           Game Settings           " << endl;
	cout << "\t\t\t\t===================================" << endl;
	cout << "\t\t\t\tBoard size:" << endl;
	cout << "\t\t\t\t1 - 4x4" << endl;
	cout << "\t\t\t\t2 - 6x6" << endl;
	cout << "\t\t\t\t3 - 8x8" << endl;
	cout << "\t\t\t\t4 - Custom" << endl;
	cout << "\t\t\t\t5 - Back" << endl;
	cout << "\t\t\t\t===================================" << endl;
	cout << "\t\t\t\tEnter your choice: ";

	bool exit = true;

	do
	{
		int userInput;
		if (!_kbhit())
		{
			continue;
		}
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
		if (!board->hasMoves() || board->isGameOver())
		{
			// Check if the game is over (win or lose conditions)
			displayGameOver();
		}

		if (!handleInput())
		{
			continue;
		}

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

bool Game::handleInput()
{
	// Check if a key has been pressed
	if (!_kbhit())
	{
		// If no key was pressed or the key pressed had no specific action, return false
		return false;
	}

	int userInput = _getch();

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
		// Exit the game when the back tick key (`) is pressed
		gameOver = true;
		return false;

	default:
		return false;
	}
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
	SetConsoleTextAttribute(hConsole, WORD(textColor | (bgColor << 4)));

	// Define the ASCII art for the logo as an array of wide characters
	vector<const wchar_t*> arr;

	// Fill the array with the logo ASCII art
	// (each element in the array represents a line of the logo)

	arr.push_back(L"\n\n\n\t\t\t█████████████████████████████████████████████████████████████");
	arr.push_back(L"\n\t\t\t█░░░░░░░░░░░░░░█░░░░░░░░░░░░░░█░░░░░░██░░░░░░█░░░░░░░░░░░░░░█");
	arr.push_back(L"\n\t\t\t█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█");
	arr.push_back(L"\n\t\t\t█░░░░░░░░░░▄▀░░█░░▄▀░░░░░░▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀░░░░░░▄▀░░█");
	arr.push_back(L"\n\t\t\t█████████░░▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀░░██░░▄▀░░█");
	arr.push_back(L"\n\t\t\t█░░░░░░░░░░▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀░░░░░░▄▀░░█░░▄▀░░░░░░▄▀░░█");
	arr.push_back(L"\n\t\t\t█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█");
	arr.push_back(L"\n\t\t\t█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀░░██░░▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█");
	arr.push_back(L"\n\t\t\t█░░▄▀░░░░░░░░░░█░░▄▀░░██░░▄▀░░█░░░░░░░░░░▄▀░░█░░▄▀░░░░░░▄▀░░█");
	arr.push_back(L"\n\t\t\t█░░▄▀░░█████████░░▄▀░░██░░▄▀░░█████████░░▄▀░░█░░▄▀░░██░░▄▀░░█");
	arr.push_back(L"\n\t\t\t█░░▄▀░░░░░░░░░░█░░▄▀░░░░░░▄▀░░█████████░░▄▀░░█░░▄▀░░░░░░▄▀░░█");
	arr.push_back(L"\n\t\t\t█░░▄▀▄▀▄▀▄▀▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█████████░░▄▀░░█░░▄▀▄▀▄▀▄▀▄▀░░█");
	arr.push_back(L"\n\t\t\t█░░░░░░░░░░░░░░█░░░░░░░░░░░░░░█████████░░░░░░█░░░░░░░░░░░░░░█");
	arr.push_back(L"\n\t\t\t█████████████████████████████████████████████████████████████\n\t\t\t");

	// Loop through the array and write each line to the console
	for (const wchar_t* a : arr)
	{
		WriteConsoleW(hConsole, a, wcslen(a), nullptr, nullptr);
	}

	// Perform a color transition animation
	for (int i = steps; i > 0; i--) {

		if (_kbhit()) {
			break;
		}
		textColor -= i;
		bgColor -= i;

		// Set the new text attributes (color) for the console
		SetConsoleTextAttribute(hConsole, WORD(textColor | (bgColor >> 4)));

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
	vector<const wchar_t*> arr;

	// Fill the array with the instruction ASCII art
	// (each element in the array represents a line of the instructions)

	arr.push_back(L"\n\n\n\t\t\t\t\t         ______ ");
	arr.push_back(L"\n\t\t\t\t\t        | W    |");
	arr.push_back(L"\n\t\t\t\t\t        |___ __|");
	arr.push_back(L"\n\t\t\t\t\t  ______   ______   ______");
	arr.push_back(L"\n\t\t\t\t\t | A    | | S    | | D    |");
	arr.push_back(L"\n\t\t\t\t\t |__ ___| |__ ___| |__ ___|\n\n\n");
	arr.push_back(L"\n\t\t\t\t\t Use keyboard to control\t\n\n\n");
	arr.push_back(L"\n\t\t\t\t\t   Press F to continue\t");

	// Display a brief instruction on using the keyboard for control

	Sleep(100);
	system("cls");

	// Loop through the array and write each line to the console
	for (int i = 0; i < arr.size(); i++)
	{
		if (i == 7)
		{
			Sleep(1000);
		}
		WriteConsoleW(hConsole, arr[i], wcslen(arr[i]), nullptr, nullptr);
	}

	// Pause briefly to display the instructions

	int userInput = 0;

	do
	{
		if (!_kbhit())
		{
			continue;
		}
		
		userInput = _getch();
		
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
	vector<const wchar_t*> WIN;

	// Fill the array with ASCII art for the win message
	WIN.push_back(L"\n\n");
	WIN.push_back(L"\n\t\t\t   ██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗██╗███╗   ██╗\n");
	WIN.push_back(L"\n\t\t\t   ██║   ██║██╔═══██╗╚██╗ ██╔╝    ██║    ██║██║████╗  ██║\n");
	WIN.push_back(L"\n\t\t\t   ██║   ██║██║   ██║ ╚████╔╝     ██║ █╗ ██║██║██╔██╗ ██║\n");
	WIN.push_back(L"\n\t\t\t   ██║   ██║██║   ██║  ╚██╔╝      ██║███╗██║██║██║╚██╗██║\n");
	WIN.push_back(L"\n\t\t\t   ╚██████╔╝╚██████╔╝   ██║       ╚███╔███╔╝██║██║ ╚████║\n");
	WIN.push_back(L"\n\t\t\t    ╚═════╝  ╚═════╝    ╚═╝        ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝\n");

	// Define ASCII art for the lose message
	vector<const wchar_t*> LOS;

	// Fill the array with ASCII art for the lose message
	LOS.push_back(L"\n\n");
	LOS.push_back(L"\n\t\t\t   ██████╗ ██╗   ██╗███╗   ██╗ ██████╗ ██████╗  ██████╗ \n");
	LOS.push_back(L"\n\t\t\t  ██╔═══██╗██║   ██║████╗  ██║██╔════╝ ██╔══██╗██╔═══██╗\n");
	LOS.push_back(L"\n\t\t\t  ██║   ██║██║   ██║██╔██╗ ██║██║  ███╗██████╔╝██║   ██║\n");
	LOS.push_back(L"\n\t\t\t  ██║   ██║██║   ██║██║╚██╗██║██║   ██║██╔══██╗██║   ██║\n");
	LOS.push_back(L"\n\t\t\t  ╚██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝██████╔╝╚██████╔╝\n");
	LOS.push_back(L"\n\t\t\t   ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═════╝  ╚═════╝ \n");

	// Display a brief instruction on using the keyboard for control
	Sleep(100);
	system("cls");

	// Loop through the array and write each line to the console
	for (int i = 0; i < WIN.size(); i++)
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
