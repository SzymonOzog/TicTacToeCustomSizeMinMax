#include "Field.h"
#include "WinChecker.h"
#include <cmath>
Field::Field(int side)
{
	pointsNeededToWin = side < 4 ? side : 4;
	fieldSide = side;
	rowChecker = new RowChecker(this);
	columnChecker = new ColumnChecker(this);
	forwardDiagonalChecker = new ForwardDiagonalChecker(this);
	backwardDiagonalChecker = new BackwardDiagonalChecker(this);
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
	if (rowChecker->checkAllLines())
		return true;
	if (columnChecker->checkAllLines())
		return true;
	if (forwardDiagonalChecker->checkAllLines())
		return true;
	if (backwardDiagonalChecker->checkAllLines())
		return true;
	return false;
}

bool Field::hasWon(int i)
{
	if (rowChecker->checkForWin(i))
		return true;
	if (columnChecker->checkForWin(i))
		return true;
	if (forwardDiagonalChecker->checkForWin(i))
		return true;
	if (backwardDiagonalChecker->checkForWin(i))
		return true;
	return false;
}

void Field::nullify()
{
	for (auto& p : vecField)
		p = player::None;
}
