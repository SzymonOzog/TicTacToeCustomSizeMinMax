#pragma once
#include <string>
enum class player : short
{
	AI = -1,
	None = 0,
	Human = 1
};
class TicTacToe
{
public: 
	TicTacToe() = default;
	~TicTacToe() = default;
	
private:
	static const int nScreenWidth = 80;
	static const int nScreenHeight = 30;
	static const int nFieldSide = 5;
	static const int nBorderSide = 2 * nFieldSide + 1;
	const std::string rules = R"(
Welcome to the TicTacToe game where you will be competing against AI
1. You play as X
2. You have the first move
3. The AI plays as O
4. To place X just click on the field
5. The board`s size is 5x5.
To start the game press 'enter'.  
)";
public:
	void setField(wchar_t* screen);
	void start();
};

