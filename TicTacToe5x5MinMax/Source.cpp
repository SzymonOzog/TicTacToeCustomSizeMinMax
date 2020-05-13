#include <Windows.h>
#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
static const int nScreenWidth = 80;
static const int nScreenHeight = 30;
static const int nFieldSide = 5;
static const int nBorderSide = 2 * nFieldSide + 1;

static const std::string rules = R"(
Welcome to the TicTacToe game where you will be competing against AI
1. You play as X
2. You have the first move
3. The AI plays as O
4. To place X just click on the field
5. The board`s size is 5x5.
To start the game press 'enter'.  
)";
                                                                                            
void setField(wchar_t* screen)
{
	//Set screen to be blank
	for (int i = 0; i < nScreenHeight * nScreenWidth; i++)
		screen[i] = ' ';
	//Create the field
	for (int i = 0; i < nBorderSide * nBorderSide; i++)
	{
		int row = i/nBorderSide;
		int column = i % nBorderSide;
		if (column % 2 == 0)
		{
			screen[row*nScreenWidth + column] = '|';
		}
		else 
		{
			if (row % 2 == 0) //Unlayable row
			{
				screen[row*nScreenWidth + column] = '-';
			}
		}
		
	}
}

int main()
{
	std::string sConsoleProps = "MODE CON COLS=" + std::to_string(nScreenWidth) + " LINES=" + std::to_string(nScreenHeight);
	system(sConsoleProps.c_str());
	//An array of values, 0 = blank space, 1 = X and 2 = O
	std::array<short, nFieldSide * nFieldSide> field; 
	field.fill(0);

	std::cout << rules;
	std::cin.get();

	//Screen buffer - we will be outputting this to the screen
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];

	//Create the game field and set the rest of the screen to be blank
	setField(screen);

	//Get the console handle
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD Input;
	DWORD Events;
	COORD coord;
	DWORD dwBytesWritten = 0;
	SetConsoleMode(hConsoleIn, ENABLE_EXTENDED_FLAGS|ENABLE_WINDOW_INPUT|ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
	SMALL_RECT r = { nScreenWidth, nScreenHeight };
	SetConsoleWindowInfo(hConsoleOut, false, &r);
	//MoveWindow(GetConsoleWindow(), 100, 100, nScreenWidth * 16, nScreenHeight * 16, false);

	bool game = true;
	while (game)
	{
		ReadConsoleInput(hConsoleIn, &Input, 1, &Events);
		if (Input.EventType == KEY_EVENT)
		{
			if (Input.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
				game = false;
		}
		if (Input.EventType == MOUSE_EVENT)
		{
			if (Input.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				coord.X = Input.Event.MouseEvent.dwMousePosition.X;
				coord.Y = Input.Event.MouseEvent.dwMousePosition.Y;
				if (coord.X < nBorderSide && coord.Y < nBorderSide && screen[coord.Y * nScreenWidth + coord.X] == ' ')
				{
					screen[coord.Y * nScreenWidth + coord.X] = 'X';
					field[coord.Y / 2 * nFieldSide + coord.X/2] = 1;
				}
			}
		}
		//null terminator for safety
		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		//output our screen to the console
		WriteConsoleOutputCharacter(hConsoleOut, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

}