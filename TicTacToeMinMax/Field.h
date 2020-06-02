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
	inline bool canDrawOrWin() { return std::count(vecField.begin(), vecField.end(), player::None) <= vecField.size() + 1 - 2 * nFieldSide; }
	inline auto begin() { return vecField.begin(); }
	inline auto end() { return vecField.end(); }
	inline size_t size() { return vecField.size(); }
private:
	void updateState(int i);
	field checkColumn(int i);
	field checkRow(int i);
	field checkFirstDiagonal();
	field checkSecondDiagonal();
	inline bool hasWon() { return std::find(vecStates.begin(), vecStates.end(), field::Won) != vecStates.end(); }
	inline bool isDraw() { return std::count(vecStates.begin(), vecStates.end(), field::Draw) == vecStates.size(); }
	inline int getColumn(int i) { return i % nFieldSide; }
	inline int getRow(int i) { return i / nFieldSide; }
	inline bool isOnFirstDiagonal(int i) { return getRow(i) == getColumn(i); } 
	inline bool isOnSecondDiagonal(int i) {	return nFieldSide - 1 - getRow(i) == getColumn(i);}
private:
	int nFieldSide;
	std::vector<player> vecField;
	std::vector<field> vecStates; 	
	field fieldState = field::None;
};

