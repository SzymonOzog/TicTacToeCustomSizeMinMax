#include "Field.h"
#include "WinChecker.h"
#include <cmath>
Field::Field(int side)
{
	pointsNeededToWin = side < 4 ? side : 4;
	fieldSide = side;
	winCheckers.push_back(new RowChecker(this));
	winCheckers.push_back(new ColumnChecker(this));
	winCheckers.push_back(new ForwardDiagonalChecker(this));
	winCheckers.push_back(new BackwardDiagonalChecker(this));
	int size = side * side;
	vecField.reserve(size);
	while (size--)
		vecField.emplace_back(player::None);
}

bool Field::isCoordWorthChecking(int coord)
{
	int row = getRow(coord);
	int column = getColumn(coord);
	for (int y = row - 2; y <= row + 2; y++)
		for (int x = column - 2; x <= column + 2; x++)
			if (isCoordTaken(y, x))
				return true;
	return false;
}

bool Field::hasWon()
{
	for (auto winChecker : winCheckers)
		if (winChecker->checkAllLines())
			return true;
	return false;
}

bool Field::hasWon(int i)
{
	for (auto winChecker : winCheckers)
		if (winChecker->checkForWin(i))
			return true;
	return false;
}

void Field::nullify()
{
	for (auto& p : vecField)
		p = player::None;
}
