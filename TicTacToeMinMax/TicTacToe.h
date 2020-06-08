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
	TicTacToe(int side);
	~TicTacToe();
	
private:
	const int screenWidth = 80;
	const int screenHeight = 30;
	const int borderSide;
	bool isGameOver = false;
	std::string finalMessage;
	wchar_t* screen = new wchar_t[screenWidth * screenHeight];
	std::shared_ptr<Field> field;
	std::unique_ptr<Console> console;
	std::unique_ptr<AI> ai;

public:
	void start();
private:
	inline bool isViableCoord(COORD coord) { return (coord.X < borderSide && coord.Y < borderSide && screen[coord.Y * screenWidth + coord.X] == ' '); }
	inline int coordToScreen(COORD c) { return c.Y * screenWidth + c.X; }
	inline int coordToField(COORD c) { return c.Y / 2 * Field::fieldSide + c.X / 2; }
	inline COORD fieldToCoord(int p) { short x = p % Field::fieldSide; short y = p / Field::fieldSide; return { x * 2 + 1, y * 2 + 1 }; }
	inline int fieldToScreen(int p) { return coordToScreen(fieldToCoord(p)); }
	void createScreen();
	void printFinalMessage();
	void playGame();
	void gameOver(player p);


};

