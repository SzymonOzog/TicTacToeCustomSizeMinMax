
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <numeric>
#include <utility>
#include "TicTacToe.h"

int AI::nFieldSide;

TicTacToe::TicTacToe(int fieldSide) : nBorderSide(2 * fieldSide + 1)
{
	nFieldSide = fieldSide;
	createScreen();

	field = std::make_shared<Field>(fieldSide * fieldSide);
	console = std::make_unique<Console>(nScreenWidth, nScreenHeight);
	ai = std::make_unique<AI>(field);
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
	delete[] screen;
}

void TicTacToe::start()
{
	playGame();
	printFinalMessage();
}


void TicTacToe::playGame()
{

	COORD coord = { 0,0 };
	while (bGame)
	{
		console->listen();
		if (console->isKeyEvent())
		{
			if (console->isEscEvent())
				bGame = false;
		}
		if (console->isMouseEvent())
		{
			if (console->isLMBEvent())
			{
				coord = console->getMousePosition();
				if (isViableCoord(coord))
				{
					screen[coordToScreen(coord)] = 'X';
					(*field)[coordToField(coord)] = player::Human;
					if (field->hasWon())
					{
						gameOver(player::Human);
						break;
					}
					int aiMove = ai->findBestMove().second;
					if (aiMove == -1)
					{
						gameOver(player::None);
						break;
					}
					screen[fieldToScreen(aiMove)] = 'O';
					(*field)[aiMove] = player::AI;
					if (field->hasWon())
					{
						gameOver(player::AI);
						break;
					}
				}
			}
		}
		//null terminator for safety
		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		console->outputScreen(screen);
	}
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
	console->setCursorPosition(0, nBorderSide + 1);
	std::cout << sFinalMessage << std::endl;
}
