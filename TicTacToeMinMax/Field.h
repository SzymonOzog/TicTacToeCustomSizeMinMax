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
	bool isDraw();
	void nullify();
	inline bool canDrawOrWin() { return std::count(vecField.begin(), vecField.end(), player::None) <= vecField.size() + 1 - 2 * nFieldSide; }

	player& operator [] (int i) { return vecField[i]; }
	inline auto begin() { return vecField.begin(); }
	inline auto end() { return vecField.end(); }
	inline size_t size() { return vecField.size(); }

private:
	int nFieldSide;
	std::vector<player> vecField;
};

