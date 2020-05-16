#define NOMINMAX //no windows.h I don`t want to use your terrible min and max macros
#include <Windows.h>
#include <algorithm>
#include <iostream>
#include <array>
#include <cstdlib>
#include <numeric>
#include <utility>
#include "TicTacToe.h"

void TicTacToe::setField(wchar_t* screen)
{
	//Set screen to be blank
	for (int i = 0; i < nScreenHeight * nScreenWidth; i++)
		screen[i] = ' ';
	//Create the field
	for (int i = 0; i < nBorderSide * nBorderSide; i++)
	{
		int row = i / nBorderSide;
		int column = i % nBorderSide;
		if (column % 2 == 0)
		{
			screen[row * nScreenWidth + column] = '|';
		}
		else
		{
			if (row % 2 == 0) //Unlayable row
			{
				screen[row * nScreenWidth + column] = '-';
			}
		}
	}
}


void TicTacToe::start()
{
	std::string sConsoleProps = "MODE CON COLS=" + std::to_string(nScreenWidth) + " LINES=" + std::to_string(nScreenHeight);
	system(sConsoleProps.c_str());

	std::array<player, nFieldSide* nFieldSide> field;
	field.fill(player::None);

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
	SetConsoleMode(hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

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
					field[coord.Y / 2 * nFieldSide + coord.X / 2] = player::Human;
				}
			}
		}
		//null terminator for safety
		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		//output our screen to the console
		WriteConsoleOutputCharacter(hConsoleOut, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}
}
