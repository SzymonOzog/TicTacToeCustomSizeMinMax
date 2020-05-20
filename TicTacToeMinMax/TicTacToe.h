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
	bool game = true;
	std::string finalMessage;
	//Screen buffer - we will be outputting this to the screen
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];

	HANDLE hConsoleOut = nullptr;
	HANDLE hConsoleIn = nullptr;
	DWORD Events = 0;
	COORD coord = { 0,0 };
	DWORD dwBytesWritten = 0;
	INPUT_RECORD Input;
	CONSOLE_CURSOR_INFO cursorInfo;
public:
	void start();
	//TODO - all of this should be private but rn I have no idea how to test private functions
	std::vector<player> field;
	void setScreen();
	bool hasWon();
	std::pair<int, int> findBestMove(int movesTaken = 0, std::pair<int, int> shortestWin = { nFieldSide, -1 });
	void gameOver(player p);
private:
	inline bool isViableCoord(COORD coord) { return (coord.X < nBorderSide && coord.Y < nBorderSide && screen[coord.Y * nScreenWidth + coord.X] == ' '); }
	inline int coordToScreen(COORD c) { return c.Y * nScreenWidth + c.X; }
	inline int coordToField(COORD c) { return c.Y / 2 * nFieldSide + c.X / 2; }
	inline COORD fieldToCoord(int p) { short x = p % nFieldSide; short y = p / nFieldSide; return { x * 2 + 1, y * 2 + 1 }; }
	inline int fieldToScreen(int p) { return coordToScreen(fieldToCoord(p)); }
};

