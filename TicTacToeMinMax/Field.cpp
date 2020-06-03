#include "Field.h"
#include <cmath>
Field::Field(int size) : nFieldSide(sqrt(size))
{
	vecField.reserve(size);
	while (size--)
		vecField.emplace_back(player::None);
}


void Field::nullify()
{
	for (auto& p : vecField)
		p = player::None;
}

void Field::set(int i, player p)
{
	vecField[i] = p;
	fieldsTaken += p == player::None ? -1 : 1;
	if(canDrawOrWin() || p == player::None)
		updateState(i);
}

void Field::updateState(int i)
{
	if (checkRow(getRow(i)) || checkColumn(getColumn(i)) || checkFirstDiagonal() || checkSecondDiagonal())
		fieldState = field::Won;
	else if (isDraw())
		fieldState = field::Draw;
	else
		fieldState = field::None;
}

bool Field::checkRow(int row)
{
	int column = 0; 
	int sum = 0;
	while (column == abs(sum) && coordInsideField(column, row))
		sum += static_cast<int>(vecField[coordToField(column++, row)]);
	if (abs(sum) == nFieldSide)
		return true;
	return false;
}

bool Field::checkColumn(int column)
{
	int row = 0;
	int sum = 0;
	while (row == abs(sum) && coordInsideField(column, row))
		sum += static_cast<int>(vecField[coordToField(column, row++)]);
	if (abs(sum) == nFieldSide)
		return true;
	return false;
}

bool Field::checkFirstDiagonal()
{
	int row = 0, column = 0;
	int sum = 0;
	while (row == abs(sum) && coordInsideField(column, row))
		sum += static_cast<int>(vecField[coordToField(column++, row++)]);
	if (abs(sum) == nFieldSide)
		return true;
	return false;
}

bool Field::checkSecondDiagonal()
{
	int row = 0, column = nFieldSide-1;
	int sum = 0;
	while (row == abs(sum) && coordInsideField(column, row))
		sum += static_cast<int>(vecField[coordToField(column--, row++)]);
	if (abs(sum) == nFieldSide)
		return true;
	return false;
}
