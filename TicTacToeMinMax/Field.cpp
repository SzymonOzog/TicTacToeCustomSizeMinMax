#include "Field.h"
#include <cmath>
Field::Field(int side)
{
	fieldSide = side;
	int size = side * side;
	vecField.reserve(size);
	while (size--)
		vecField.emplace_back(player::None);
}
bool Field::hasWon()
{
	for (int i = 0; i < fieldSide; i++)
	{
		if (checkRow(i))
			return true;
		if (checkColumn(i))
			return true;
	}
	if (checkFirstDiagonal())
		return true;
	if (checkSecondDiagonal())
		return true;
	return false;
}
bool Field::hasWon(int i)
{

	if (checkRow(getRow(i)))
		return true;
	if (checkColumn(getColumn(i)))
		return true;
	if(isOnFirstDiagonal(i))
		if (checkFirstDiagonal())
			return true;
	if(isOnSecondDiagonal(i))
		if (checkSecondDiagonal())
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
	int sum = 0;
	while (column == abs(sum) && coordInsideField(column, row))
		sum += static_cast<int>(vecField[coordToField(column++, row)]);
	if (abs(sum) == fieldSide)
		return true;
	return false;
}

bool Field::checkColumn(int column)
{
	int row = 0;
	int sum = 0;
	while (row == abs(sum) && coordInsideField(column, row))
		sum += static_cast<int>(vecField[coordToField(column, row++)]);
	if (abs(sum) == fieldSide)
		return true;
	return false;
}

bool Field::checkFirstDiagonal()
{
	int row = 0, column = 0;
	int sum = 0;
	while (row == abs(sum) && coordInsideField(column, row))
		sum += static_cast<int>(vecField[coordToField(column++, row++)]);
	if (abs(sum) == fieldSide)
		return true;
	return false;
}

bool Field::checkSecondDiagonal()
{
	int row = 0, column = fieldSide - 1;
	int sum = 0;
	while (row == abs(sum) && coordInsideField(column, row))
		sum += static_cast<int>(vecField[coordToField(column--, row++)]);
	if (abs(sum) == fieldSide)
		return true;
	return false;
}
