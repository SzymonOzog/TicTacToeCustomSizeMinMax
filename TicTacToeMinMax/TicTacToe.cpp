
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <numeric>
#include <utility>
#include "TicTacToe.h"

TicTacToe::TicTacToe(int fieldSide) : nBorderSide(2 * fieldSide + 1)
{
	nFieldSide = fieldSide;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	createScreen();
	createField();
}
void TicTacToe::createField()
{
	vecField.reserve(nFieldSide * nFieldSide);
	for (int i = 0; i < nFieldSide * nFieldSide; i++)
		vecField.emplace_back(player::None);
}

void TicTacToe::createScreen()
{
	//Set screen to be blank
	for (int i = 0; i < nScreenHeight * nScreenWidth; i++)
		screen[i] = ' ';
	//Create the field
	for (int i = 0; i < nBorderSide * nBorderSide; i++)
	{
		COORD c{ i % nBorderSide, i / nBorderSide };
		if (c.X % 2 == 0)
		{
			screen[coordToScreen(c)] = '|';
		}
		else
		{
			if (c.Y % 2 == 0) //Unlayable row
			{
				screen[coordToScreen(c)] = '-';
			}
		}
	}
}
TicTacToe::~TicTacToe()
{
	//delete[] screen;
}

void TicTacToe::start()
{
	setConsoleProperties();
	playGame();
	printFinalMessage();
}

void TicTacToe::setConsoleProperties()
{
	setWindowSize();
	disableWindowResizablility();
	disableCursorVisibility();
	SetConsoleMode(hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
}

void TicTacToe::setWindowSize()
{
	std::string sConsoleProps = "MODE CON COLS=" + std::to_string(nScreenWidth) + " LINES=" + std::to_string(nScreenHeight);
	system(sConsoleProps.c_str());
}

void TicTacToe::disableWindowResizablility()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void TicTacToe::disableCursorVisibility()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsoleOut, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsoleOut, &cursorInfo);
}

void TicTacToe::playGame()
{
	DWORD dwEvents = 0;
	COORD coord = { 0,0 };
	DWORD dwBytesWritten = 0;
	INPUT_RECORD Input;

	while (bGame)
	{
		ReadConsoleInput(hConsoleIn, &Input, 1, &dwEvents);
		if (Input.EventType == KEY_EVENT)
		{
			if (Input.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
				bGame = false;
		}
		if (Input.EventType == MOUSE_EVENT)
		{
			if (Input.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				coord = Input.Event.MouseEvent.dwMousePosition;
				if (isViableCoord(coord))
				{
					screen[coordToScreen(coord)] = 'X';
					vecField[coordToField(coord)] = player::Human;
					//if somebody won at this point - it was the player
					if (hasWon())
					{
						gameOver(player::Human);
						break;
					}
					int aiMove = findBestMove().second;
					if (aiMove == -1)
					{
						gameOver(player::None);
						break;
					}
					screen[fieldToScreen(aiMove)] = 'O';
					vecField[aiMove] = player::AI;
					if (hasWon())
					{
						gameOver(player::AI);
						break;
					}
				}
			}
		}
		//null terminator for safety
		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsoleOut, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}
}

std::pair<int, int> TicTacToe::findBestMove(int reverseDepth, std::pair<int, int> bestScoreMove, player currentPlayer, int alpha, int beta)
{
	if (hasWon())
		return { reverseDepth * static_cast<int>(currentPlayer), -1 };
	else if (std::find(vecField.begin(), vecField.end(), player::None) == vecField.end())//FIELD FULL - TIE
		return { 0, -1 };
	bestScoreMove.first = (currentPlayer == player::AI ? INT_MIN : INT_MAX);
	for (int i = 0; i < vecField.size(); i++)
	{
		if (vecField[i] == player::None)
		{
			vecField[i] = currentPlayer;
			int score = findBestMove(reverseDepth - 1, bestScoreMove, getOpponent(currentPlayer), alpha, beta).first;
			if (currentPlayer == player::AI)
			{
				alpha = std::max(alpha, score);
				if (bestScoreMove.first < score)
					bestScoreMove = { score, i };
			}
			else
			{
				beta = std::min(beta, score);
				if (bestScoreMove.first > score)
					bestScoreMove = { score, i };
			}
			vecField[i] = player::None;
			if (beta <= alpha)
				break;
		}
	}
	return bestScoreMove;
}

bool TicTacToe::hasWon()
{
	int sum, winningCase;
	//if there are less taken fields than twice the moves needed to win (AI and human plays alternatley)
	if (std::count(vecField.begin(), vecField.end(), player::None) > vecField.size() - 2*nFieldSide)
		return false;
	for (int i = 0; i < nFieldSide; i++)
	{
		sum = 0;
		winningCase = 0;
		//check horizontally
		while (abs(sum) == winningCase && winningCase < nFieldSide)
			sum += static_cast<int>(vecField[winningCase++ + i*nFieldSide]);
		if (abs(sum) == nFieldSide)
			return true;
		//check veritically 
		sum = 0;
		winningCase = 0;
		while (abs(sum) == winningCase && winningCase < nFieldSide)
			sum += static_cast<int>(vecField[nFieldSide*winningCase++ + i]);
		if (abs(sum) == nFieldSide)
			return true;
	}
	//check first diagonal
	sum = 0;
	for (int x = 0, y=0; y < nFieldSide && x< nFieldSide; x++, y++)
		sum += static_cast<int>(vecField[y*nFieldSide+x]);
	if (abs(sum) == nFieldSide)
		return true;
	//check second diagonal
	sum = 0;
	for (int x = nFieldSide - 1, y = 0; y < nFieldSide && x >=0; x--, y++)
		sum += static_cast<int>(vecField[y * nFieldSide + x]);
	if (abs(sum) == nFieldSide)
		return true;
	return false;
}

void TicTacToe::gameOver(player p)
{
	bGame = false;
	switch (p)
	{
	case player::None:
		sFinalMessage = "TIE! Congratulations, you couldn`t win anyway";
		break;
	case player::AI:
		sFinalMessage = "YOU LOST!";
		break;
	case player::Human:
		sFinalMessage = "WOW, YOU WON! Guess my program is bad, post an issue on my GitHub or contact me";
		break;
	}
}

void TicTacToe::printFinalMessage()
{
	SetConsoleCursorPosition(hConsoleOut, { 0, static_cast<short>(nBorderSide + 1) });
	std::cout << sFinalMessage << std::endl;
}
