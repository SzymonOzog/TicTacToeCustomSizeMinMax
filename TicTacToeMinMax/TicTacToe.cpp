
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <numeric>
#include <utility>
#include "TicTacToe.h"

int Field::fieldSide;

TicTacToe::TicTacToe(int side) : borderSide(2 * side + 1)
{
	createScreen();

	field = std::make_shared<Field>(side);
	console = std::make_unique<Console>(screenWidth, screenHeight);
	ai = std::make_unique<AI>(field);
}


void TicTacToe::createScreen()
{
	//Set screen to be blank
	for (int i = 0; i < screenHeight * screenWidth; i++)
		screen[i] = ' ';
	//Create the field
	for (int i = 0; i < borderSide * borderSide; i++)
	{
		COORD c{ i % borderSide, i / borderSide };
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
	while (!isGameOver)
	{
		console->listen();
		if (console->isKeyEvent())
		{
			if (console->isEscEvent())
				isGameOver = true;
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
					int aiMove = ai->findBestMove();
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
		screen[screenWidth * screenHeight - 1] = '\0';
		console->outputScreen(screen);
	}
}

void TicTacToe::gameOver(player p)
{
	isGameOver = true;
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

void TicTacToe::printFinalMessage()
{
	console->setCursorPosition(0, borderSide + 1);
	std::cout << finalMessage << std::endl;
}
