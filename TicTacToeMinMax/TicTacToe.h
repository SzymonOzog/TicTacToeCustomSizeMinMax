#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Field.h"
#include "AI.h"
#include "Console.h"
class TicTacToe
{
public: 
	TicTacToe() = delete;
	TicTacToe(int fieldSide);
	~TicTacToe();
	
private:
	static const int nScreenWidth = 80;
	static const int nScreenHeight = 30;
	static int nFieldSide;
	const int nBorderSide;
	bool bGame = true;
	std::string sFinalMessage;
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	std::shared_ptr<Field> field;
	std::unique_ptr<Console> console;
	std::unique_ptr<AI> ai;

public:
	void start();
private:
	inline bool isViableCoord(COORD coord) { return (coord.X < nBorderSide && coord.Y < nBorderSide && screen[coord.Y * nScreenWidth + coord.X] == ' '); }
	inline int coordToScreen(COORD c) { return c.Y * nScreenWidth + c.X; }
	inline int coordToField(COORD c) { return c.Y / 2 * nFieldSide + c.X / 2; }
	inline COORD fieldToCoord(int p) { short x = p % nFieldSide; short y = p / nFieldSide; return { x * 2 + 1, y * 2 + 1 }; }
	inline int fieldToScreen(int p) { return coordToScreen(fieldToCoord(p)); }
	void createScreen();
	void printFinalMessage();
	void playGame();
	void gameOver(player p);


};

