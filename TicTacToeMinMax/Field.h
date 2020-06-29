#pragma once
#include <vector>
#include <algorithm>
#include <utility>

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

	bool isCoordWorthChecking(int coord);
	bool hasWon();	
	bool hasWon(int i);
	inline bool isDraw() { return std::find(vecField.begin(), vecField.end(), player::None) == vecField.end(); }
	void nullify();
	inline bool canDrawOrWin() { return getEmptyCoords() <= vecField.size() + 1 - 2 * pointsNeededToWin; }
	inline int getEmptyCoords() { return std::count(vecField.begin(), vecField.end(), player::None); }
	player& operator [] (int i) { return vecField[i]; }
	inline auto begin() { return vecField.begin(); }
	inline auto end() { return vecField.end(); }
	inline size_t size() { return vecField.size(); }

public:
	static int fieldSide;

private: 
	inline bool isCoordTaken(int row, int column) { return coordInsideField(column,row) && vecField[coordToField(column, row)] != player::None; }
	inline std::pair<int, int> getForwardDiagonalCoord(int i) { int row = getRow(i), column = getColumn(i); int diff = std::min(row, column); return { column - diff, row - diff }; }
	inline std::pair<int, int> getBackwardDiagonalCoord(int i) { int row = getRow(i), column = getColumn(i); int diff = std::min(row, (fieldSide - 1 - column)); return { column + diff, row - diff }; }
	inline bool isOnFirstDiagonal(int i) { return getRow(i) == getColumn(i); }
	inline bool isOnSecondDiagonal(int i) { return fieldSide - 1 - getRow(i) == getColumn(i); }
	inline int getColumn(int i) { return i % fieldSide; }
	inline int getRow(int i) { return i / fieldSide; }
	inline int coordToField(int x, int y) { return y * fieldSide + x; }
	inline bool coordInsideField(int x, int y) { return x >= 0 && x < fieldSide && y >= 0 && y < fieldSide; }
	bool checkRow(int row);
	bool checkColumn(int column);
	bool checkFirstDiagonal(std::pair<int, int> coord);
	bool checkSecondDiagonal(std::pair<int, int> coord);
	std::vector<std::pair<int, int>> allForwardDiagonals();
	std::vector<std::pair<int, int>> allBackwardDiagonals();

private:
	std::vector<player> vecField;
	int pointsNeededToWin;
};

