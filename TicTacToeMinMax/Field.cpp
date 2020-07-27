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
	for (int i = 0; i < fieldSide; i++)
	{
		if (rowChecker->checkForWin(i * fieldSide))
			return true;
		if (columnChecker->checkForWin(i))
			return true;
	}
	for (auto coord : allForwardDiagonals())
	{
		if (forwardDiagonalChecker->checkForWin(coordToField(coord.first, coord.second)))
			return true;
	}
	for (auto coord : allBackwardDiagonals())
	{
		if (backwardDiagonalChecker->checkForWin(coordToField(coord.first, coord.second)))
			return true;
	}
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

std::vector<std::pair<int, int>> Field::allForwardDiagonals()
{
	std::vector<std::pair<int, int>> forwardDiagonals;
	int row = 0, column = 0;
	while (fieldSide - row >= pointsNeededToWin)
		forwardDiagonals.push_back({ column, row++ });
	row = 0;
	while (fieldSide - column >= pointsNeededToWin)
		forwardDiagonals.push_back({ column++, row });
	return forwardDiagonals;
}

std::vector<std::pair<int, int>> Field::allBackwardDiagonals()
{
	std::vector<std::pair<int, int>> backwardDiagonals = allForwardDiagonals();
	for (auto& coord : backwardDiagonals)
		coord.first = fieldSide - 1 - coord.first;
	return backwardDiagonals;
}