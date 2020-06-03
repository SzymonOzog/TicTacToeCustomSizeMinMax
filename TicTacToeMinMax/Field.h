#pragma once
#include <vector>
#include <algorithm>
enum class player : short
{
	AI = -1,
	None = 0,
	Human = 1
};
enum class field : short
{
	None = 0,
	Draw,
	Won
};
class Field
{
public:
	Field() = delete;
	Field(int size);
	
	void nullify();
	void set(int i, player p);

	inline const player& at(int i) { return vecField[i]; }
	inline const field& getState() { return fieldState; }
	inline bool canDrawOrWin() { return fieldsTaken >= 2 * nFieldSide - 1; }
	inline auto begin() { return vecField.begin(); }
	inline auto end() { return vecField.end(); }
	inline size_t size() { return vecField.size(); }
private:
	void updateState(int i);
	bool checkColumn(int column);
	bool checkRow(int row);
	bool checkFirstDiagonal();
	bool checkSecondDiagonal();
	inline bool isDraw() { return std::find(vecField.begin(), vecField.end(), player::None) == vecField.end(); }
	inline bool isOnFirstDiagonal(int i) { return getRow(i) == getColumn(i); } 
	inline bool isOnSecondDiagonal(int i) {	return nFieldSide - 1 - getRow(i) == getColumn(i);}
	inline int getColumn(int i) { return i % nFieldSide; }
	inline int getRow(int i) { return i / nFieldSide; }
	inline int coordToField(int x, int y) { return y * nFieldSide + x; }
	inline bool coordInsideField(int x, int y) { return x >= 0 && x < nFieldSide && y >= 0 && y < nFieldSide; }
private:
	int nFieldSide;
	int fieldsTaken = 0;
	std::vector<player> vecField;
	field fieldState = field::None;
};

