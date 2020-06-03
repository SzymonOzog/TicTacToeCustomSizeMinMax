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
	Field(int size);

	bool hasWon();	
	bool hasWon(int i);
	inline bool isDraw() { return std::find(vecField.begin(), vecField.end(), player::None) == vecField.end(); }
	void nullify();
	inline bool canDrawOrWin() { return std::count(vecField.begin(), vecField.end(), player::None) <= vecField.size() + 1 - 2 * nFieldSide; }

	player& operator [] (int i) { return vecField[i]; }
	inline auto begin() { return vecField.begin(); }
	inline auto end() { return vecField.end(); }
	inline size_t size() { return vecField.size(); }

private: 
	inline bool isOnFirstDiagonal(int i) { return getRow(i) == getColumn(i); }
	inline bool isOnSecondDiagonal(int i) { return nFieldSide - 1 - getRow(i) == getColumn(i); }
	inline int getColumn(int i) { return i % nFieldSide; }
	inline int getRow(int i) { return i / nFieldSide; }
	inline int coordToField(int x, int y) { return y * nFieldSide + x; }
	inline bool coordInsideField(int x, int y) { return x >= 0 && x < nFieldSide && y >= 0 && y < nFieldSide; }
	bool checkRow(int row);
	bool checkColumn(int column);
	bool checkFirstDiagonal();
	bool checkSecondDiagonal();


private:
	int nFieldSide;
	std::vector<player> vecField;
};

