#include "Field.h"
#include <cmath>
Field::Field(int size) : nFieldSide(sqrt(size))
{
	vecField.reserve(size);
	while (size--)
		vecField.emplace_back(player::None);
	vecStates.reserve(2 * nFieldSide + 2); // rows, columns, diagonals
	for(int i = 0; i< 2 * nFieldSide + 2; i++)
		vecStates.emplace_back(field::None);
}


void Field::nullify()
{
	for (auto& p : vecField)
		p = player::None;
	for (auto& s : vecStates)
		s = field::None;
}

void Field::set(int i, player p)
{
	vecField[i] = p;
	fieldsTaken += p == player::None ? -1 : 1;
		updateState(i);
}

void Field::updateState(int i)
{
	vecStates[getRow(i)] = checkRow(getRow(i));
	vecStates[nFieldSide + getColumn(i)] = checkColumn(getColumn(i));
	if (isOnFirstDiagonal(i))
		vecStates[2 * nFieldSide] = checkFirstDiagonal();
	if (isOnSecondDiagonal(i))
		vecStates[2 * nFieldSide + 1] = checkSecondDiagonal();
	if (hasWon())
		fieldState = field::Won;
	else if (isDraw())
		fieldState = field::Draw;
	else
		fieldState = field::None;
}

field Field::checkRow(int row)
{
	int column = 0; 
	int sum = 0;
	while (column == abs(sum) && coordInsideField(column, row))
		sum += static_cast<int>(vecField[coordToField(column++, row)]);
	if (abs(sum) == nFieldSide)
		return field::Won;
	return field::None;
}

field Field::checkColumn(int column)
{
	int row = 0;
	int sum = 0;
	while (row == abs(sum) && coordInsideField(column, row))
		sum += static_cast<int>(vecField[coordToField(column, row++)]);
	if (abs(sum) == nFieldSide)
		return field::Won;
	return field::None;
}

field Field::checkFirstDiagonal()
{
	int row = 0, column = 0;
	int sum = 0;
	while (row == abs(sum) && coordInsideField(column, row))
		sum += static_cast<int>(vecField[coordToField(column++, row++)]);
	if (abs(sum) == nFieldSide)
		return field::Won;
	return field::None;
}

field Field::checkSecondDiagonal()
{
	int row = 0, column = nFieldSide-1;
	int sum = 0;
	while (row == abs(sum) && coordInsideField(column, row))
		sum += static_cast<int>(vecField[coordToField(column--, row++)]);
	if (abs(sum) == nFieldSide)
		return field::Won;
	return field::None;
}
