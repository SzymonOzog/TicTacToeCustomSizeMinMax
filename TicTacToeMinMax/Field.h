#pragma once
#include <vector>
#include <algorithm>
enum class player : short
{
	AI = -1,
	None = 0,
	Human = 1
};
class Field
{
public:
	Field() = delete;
	Field(int side);

	bool hasWon();	
	bool hasWon(int i);
	inline bool isDraw() { return std::find(vecField.begin(), vecField.end(), player::None) == vecField.end(); }
	void nullify();
	inline bool canDrawOrWin() { return std::count(vecField.begin(), vecField.end(), player::None) <= vecField.size() + 1 - 2 * fieldSide; }

	player& operator [] (int i) { return vecField[i]; }
	inline auto begin() { return vecField.begin(); }
	inline auto end() { return vecField.end(); }
	inline size_t size() { return vecField.size(); }

private: 
	inline bool isOnFirstDiagonal(int i) { return getRow(i) == getColumn(i); }
	inline bool isOnSecondDiagonal(int i) { return fieldSide - 1 - getRow(i) == getColumn(i); }
	inline int getColumn(int i) { return i % fieldSide; }
	inline int getRow(int i) { return i / fieldSide; }
	inline int coordToField(int x, int y) { return y * fieldSide + x; }
	inline bool coordInsideField(int x, int y) { return x >= 0 && x < fieldSide && y >= 0 && y < fieldSide; }
	bool checkRow(int row);
	bool checkColumn(int column);
	bool checkFirstDiagonal();
	bool checkSecondDiagonal();


private:
	int fieldSide;
	std::vector<player> vecField;
};

