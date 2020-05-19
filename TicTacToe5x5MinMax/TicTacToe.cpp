
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <numeric>
#include <utility>
#include "TicTacToe.h"

TicTacToe::TicTacToe(int fieldSide) : nBorderSide(2 * fieldSide + 1)
{
	nFieldSide = fieldSide;
	
	//set the size of our window
	std::string sConsoleProps = "MODE CON COLS=" + std::to_string(nScreenWidth) + " LINES=" + std::to_string(nScreenHeight);
	system(sConsoleProps.c_str());

	//disable the ability to resize the window
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	//disable cursor visibility
	GetConsoleCursorInfo(hConsoleOut, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsoleOut, &cursorInfo);

	//Set the field to be empty
	field.reserve(nFieldSide * nFieldSide);
	for (int i = 0; i < nFieldSide * nFieldSide; i++)
		field.emplace_back(player::None);

	//Create the game field and set the rest of the screen to be blank
	setScreen(screen);
}

TicTacToe::~TicTacToe()
{
	delete(screen);
}

void TicTacToe::setScreen(wchar_t* screen)
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

bool TicTacToe::hasWon(const std::vector<player> &field)
{
	int sum, winningCase;
	//if there are less taken fields than moves needed to win
	if (std::count(field.begin(), field.end(), player::None) > field.size() - nFieldSide)
		return false;
	for (int i = 0; i < nFieldSide; i++)
	{
		sum = 0;
		winningCase = 0;
		//check horizontally
		while (abs(sum) == winningCase && winningCase < nFieldSide)
			sum += static_cast<int>(field[winningCase++ + i*nFieldSide]);
		if (abs(sum) == nFieldSide)
			return true;
		//check veritically 
		sum = 0;
		winningCase = 0;
		while (abs(sum) == winningCase && winningCase < nFieldSide)
			sum += static_cast<int>(field[nFieldSide*winningCase++ + i]);
		if (abs(sum) == nFieldSide)
			return true;
	}
	//check first diagonal
	sum = 0;
	for (int x = 0, y=0; y < nFieldSide && x< nFieldSide; x++, y++)
		sum += static_cast<int>(field[y*nFieldSide+x]);
	if (abs(sum) == nFieldSide)
		return true;
	//check second diagonal
	sum = 0;
	for (int x = nFieldSide - 1, y = 0; y < nFieldSide && x >=0; x--, y++)
		sum += static_cast<int>(field[y * nFieldSide + x]);
	if (abs(sum) == nFieldSide)
		return true;
	return false;
}

std::pair<int, int> TicTacToe::findBestMove(std::vector<player> &field, int movesTaken, std::pair<int, int> shortestWin)
{
	if (movesTaken >= shortestWin.first)
		return shortestWin;
	else if (hasWon(field))
		return { movesTaken, -1 };
	for (int i = 0; i < field.size(); i++)
	{
		//check for AI and player Win, if the player can win faster - block him
		if (field[i] == player::None)
		{
			field[i] = player::AI;
			shortestWin = std::min(shortestWin, { findBestMove(field, movesTaken + 1, shortestWin).first, i });
			field[i] = player::Human;
			shortestWin = std::min(shortestWin, { findBestMove(field, movesTaken + 1, shortestWin).first, i });
			field[i] = player::None;
		}
	}
	return shortestWin;
}
void TicTacToe::start()
{

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
				coord = Input.Event.MouseEvent.dwMousePosition;
				if (isViableCoord(coord))
				{
					screen[coordToScreen(coord)] = 'X';
					field[coordToField(coord)] = player::Human;
					//if somebody won at this point - it was the player
					if (hasWon(field))
					{
						gameOver(player::Human);
						break;
					}
					int aiMove = findBestMove(field).second;
					if (aiMove == -1)
					{
						gameOver(player::None);
						break;
					}
					screen[fieldToScreen(aiMove)] = 'O';
					field[aiMove] = player::AI;
					if (hasWon(field))
					{
						gameOver(player::AI);
						break;
					}
				}
			}
		}
		//null terminator for safety
		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		//output our screen to the console
		WriteConsoleOutputCharacter(hConsoleOut, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}
	SetConsoleCursorPosition(hConsoleOut, { 0, static_cast<short>(nBorderSide + 1) });
	std::cout << finalMessage << std::endl;
}

void TicTacToe::gameOver(player p)
{
	game = false;
	switch (p)
	{
	case player::None:
		finalMessage = "TIE! Congratulations, you couldn`t win anyway";
		break;
	case player::AI:
		finalMessage = "YOU LOST!";
		break;
	case player::Human:
		finalMessage = "WOW, YOU WON! Guess my program is bad, post an issue on my GitHub or contact me";
		break;
	}
}
