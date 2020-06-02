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
	//TODO this line makes HasWon and isDraw test fail
	//TODO this line makes human loose after making first move
	//if (canDrawOrWin())
		updateState(i);
}

void Field::updateState(int i)
{
	vecStates[getRow(i)] = checkRow(i);
	vecStates[nFieldSide + getColumn(i)] = checkColumn(i);
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

field Field::checkRow(int i)
{
	int row = getRow(i); 
	bool isAI= false, isHuman = false;
	int sum = 0;
	for (int column = 0; column < nFieldSide; column++)
	{
		if (vecField[row * nFieldSide + column] == player::AI)
			isAI = true;
		else if (vecField[row * nFieldSide + column] == player::Human)
			isHuman = true;
		sum += static_cast<int>(vecField[row * nFieldSide + column]);
	}
	if (abs(sum) == nFieldSide)
		return field::Won;
	else if (isAI && isHuman)
		return field::Draw;
	return field::None;
}

field Field::checkColumn(int i)
{
	int column = getColumn(i);
	bool isAI = false, isHuman = false;
	int sum = 0;
	for (int row = 0; row < nFieldSide; row++)
	{
		if (vecField[row * nFieldSide + column] == player::AI)
			isAI = true;
		else if (vecField[row * nFieldSide + column] == player::Human)
			isHuman = true;
		sum += static_cast<int>(vecField[row * nFieldSide + column]);
	}
	if (abs(sum) == nFieldSide)
		return field::Won;
	else if (isAI && isHuman)
		return field::Draw;
	return field::None;
}

field Field::checkFirstDiagonal()
{
	bool isAI = false, isHuman = false;
	int sum = 0;
	for (int row = 0, column = 0; row < nFieldSide && column < nFieldSide; row++, column++)
	{
		if (vecField[row * nFieldSide + column] == player::AI)
			isAI = true;
		else if (vecField[row * nFieldSide + column] == player::Human)
			isHuman = true;
		sum += static_cast<int>(vecField[row * nFieldSide + column]);
	}
	if (abs(sum) == nFieldSide)
		return field::Won;
	else if (isAI && isHuman)
		return field::Draw;
	return field::None;
}

field Field::checkSecondDiagonal()
{
	bool isAI = false, isHuman = false;
	int sum = 0;
	for (int row = 0, column = nFieldSide - 1; row < nFieldSide && column >= 0; row++, column--)
	{
		if (vecField[row * nFieldSide + column] == player::AI)
			isAI = true;
		else if (vecField[row * nFieldSide + column] == player::Human)
			isHuman = true;
		sum += static_cast<int>(vecField[row * nFieldSide + column]);
	}
	if (abs(sum) == nFieldSide)
		return field::Won;
	else if (isAI && isHuman)
		return field::Draw;
	return field::None;
}
