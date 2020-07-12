#include "Field.h"
#include "WinChecker.h"
#include <cmath>
Field::Field(int side)
{
	pointsNeededToWin = side < 4 ? side : 4;
	fieldSide = side;
	rowChecker = new RowChecker(this);
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
		rowChecker->updateCoord(0, i);
		if (rowChecker->checkForWin())
			return true;
		if (checkColumn(i))
			return true;
	}
	for(auto coord : allForwardDiagonals())
		if (checkFirstDiagonal(coord))
			return true;
	for (auto coord : allBackwardDiagonals())
		if (checkSecondDiagonal(coord))
			return true;
	return false;
}

bool Field::hasWon(int i)
{

	if (checkRow(getRow(i)))
		return true;
	if (checkColumn(getColumn(i)))
		return true;
	std::pair<int, int> coord = getForwardDiagonalCoord(i);
	if (checkFirstDiagonal(coord))
		return true;
	coord = getBackwardDiagonalCoord(i);
	if (checkSecondDiagonal(coord))
		return true;
	return false;
}

void Field::nullify()
{
	for (auto& p : vecField)
		p = player::None;
}

bool Field::checkRow(int row)
{
	int column = 0;
	int points = 0;
	player currentPlayer = vecField[coordToField(column, row)];
	while (fieldSide - column + abs(points) >= pointsNeededToWin && coordInsideField(column, row))
	{
		if (vecField[coordToField(column, row)] == currentPlayer)
			points += static_cast<int>(vecField[coordToField(column, row)]);
		else
			points = static_cast<int>(vecField[coordToField(column, row)]);
		if (abs(points) == pointsNeededToWin)
			return true;
		currentPlayer = vecField[coordToField(column++, row)];
	}
	return false;
}

bool Field::checkColumn(int column)
{
	int row = 0;
	int points = 0;
	player currentPlayer = vecField[coordToField(column, row)];
	while (fieldSide - row + abs(points) >= pointsNeededToWin && coordInsideField(column, row))
	{
		if (vecField[coordToField(column, row)] == currentPlayer)
			points += static_cast<int>(vecField[coordToField(column, row)]);
		else
			points = static_cast<int>(vecField[coordToField(column, row)]);
		if (abs(points) == pointsNeededToWin)
			return true;
		currentPlayer = vecField[coordToField(column, row++)];
	}
	return false;
}

bool Field::checkFirstDiagonal(std::pair<int, int> coord)
{
	int column = coord.first, row = coord.second;
	int points = 0;
	player currentPlayer = vecField[coordToField(column, row)];
	while (fieldSide - row + abs(points) >= pointsNeededToWin && coordInsideField(column, row))
	{
		if (vecField[coordToField(column, row)] == currentPlayer)
			points += static_cast<int>(vecField[coordToField(column, row)]);
		else
			points = static_cast<int>(vecField[coordToField(column, row)]);
		if (abs(points) == pointsNeededToWin)
			return true;
		currentPlayer = vecField[coordToField(column++, row++)];
	}
	return false;
}

bool Field::checkSecondDiagonal(std::pair<int, int> coord)
{
	int column = coord.first, row = coord.second;
	int points = 0;
	player currentPlayer = vecField[coordToField(column, row)];
	while (fieldSide - row + abs(points) >= pointsNeededToWin && coordInsideField(column, row))
	{
		if (vecField[coordToField(column, row)] == currentPlayer)
			points += static_cast<int>(vecField[coordToField(column, row)]);
		else
			points = static_cast<int>(vecField[coordToField(column, row)]);
		if (abs(points) == pointsNeededToWin)
			return true;
		currentPlayer = vecField[coordToField(column--, row++)];
	}
	return false;
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