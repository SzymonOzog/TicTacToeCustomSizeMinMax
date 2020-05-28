#pragma once
#define NOMINMAX //no windows.h I don`t want to use your terrible min and max macros
#include <Windows.h>
#include <string>
#include <vector>
enum class player : short
{
	AI = -1,
	None = 0,
	Human = 1
};
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
	//Screen buffer - we will be outputting this to the screen
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];

	HANDLE hConsoleOut = nullptr;
	HANDLE hConsoleIn = nullptr;

public:
	void start();
	//TODO - all of this should be private but rn I have no idea how to test private functions
	std::vector<player> vecField;
	void createScreen();
	std::pair<int, int> findBestMove(int reverseDepth = nFieldSide * nFieldSide, std::pair<int, int> bestScoreMove = { 0, -1 }, player currentPlayer = player::AI, int alpha = INT_MIN, int beta = INT_MAX);
	bool hasWon();
	bool isDraw();
	void gameOver(player p);
private:
	inline bool isViableCoord(COORD coord) { return (coord.X < nBorderSide && coord.Y < nBorderSide && screen[coord.Y * nScreenWidth + coord.X] == ' '); }
	inline int coordToScreen(COORD c) { return c.Y * nScreenWidth + c.X; }
	inline int coordToField(COORD c) { return c.Y / 2 * nFieldSide + c.X / 2; }
	inline COORD fieldToCoord(int p) { short x = p % nFieldSide; short y = p / nFieldSide; return { x * 2 + 1, y * 2 + 1 }; }
	inline int fieldToScreen(int p) { return coordToScreen(fieldToCoord(p)); }
	inline player getOpponent(player p) { return p == player::AI ? player::Human : player::AI;  }
	void createField();
	void printFinalMessage();
	void setConsoleProperties();
	void setWindowSize();
	void disableWindowResizablility();
	void disableCursorVisibility();
	void playGame();


};

