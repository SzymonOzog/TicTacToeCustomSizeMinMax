#pragma once
#include <vector>
#include <algorithm>
#include <utility>
class RowChecker;
class ColumnChecker;
class ForwardDiagonalChecker;
class BackwardDiagonalChecker;
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

	friend class WinCheckerTemplate;

	bool isCoordWorthChecking(int coord);
	bool hasWon();	
	bool hasWon(int i);
	inline bool isDraw() { return std::find(vecField.begin(), vecField.end(), player::None) == vecField.end(); }
	void nullify();
	inline bool canDrawOrWin() { return getEmptyCoords() <= vecField.size() + 1 - 2 * pointsNeededToWin; }
	inline int getEmptyCoords() { return std::count(vecField.begin(), vecField.end(), player::None); }
	inline int getColumn(int i) { return i % fieldSide; }
	inline int getRow(int i) { return i / fieldSide; }
	inline int getPointsNeededToWin() { return pointsNeededToWin; }
	inline int coordToField(int x, int y) { return y * fieldSide + x; }
	inline auto begin() { return vecField.begin(); }
	inline auto end() { return vecField.end(); }
	inline size_t size() { return vecField.size(); }
	player& operator [] (int i) { return vecField[i]; }

public:
	static int fieldSide;

protected:
	inline player playerAt(int column, int row) { return vecField[coordToField(column, row)]; }
	inline bool coordInsideField(int x, int y) { return x >= 0 && x < fieldSide&& y >= 0 && y < fieldSide; }

private: 
	inline bool isCoordTaken(int row, int column) { return coordInsideField(column,row) && vecField[coordToField(column, row)] != player::None; }

private:
	std::vector<player> vecField;
	int pointsNeededToWin;
	RowChecker* rowChecker = nullptr;
	ColumnChecker* columnChecker = nullptr;
	ForwardDiagonalChecker* forwardDiagonalChecker = nullptr;
	BackwardDiagonalChecker* backwardDiagonalChecker = nullptr;
};

