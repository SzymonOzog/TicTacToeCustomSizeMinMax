#include "Field.h"
#include <cmath>
Field::Field(int size) : nFieldSide(sqrt(size))
{
	vecField.reserve(size);
	while (size--)
		vecField.emplace_back(player::None);
}

bool Field::hasWon()
{
	int sum, winningCase;
	for (int i = 0; i < nFieldSide; i++)
	{
		sum = 0;
		winningCase = 0;
		//check horizontally
		while (abs(sum) == winningCase && winningCase < nFieldSide)
			sum += static_cast<int>(vecField[winningCase++ + i * nFieldSide]);
		if (abs(sum) == nFieldSide)
			return true;
		//check veritically 
		sum = 0;
		winningCase = 0;
		while (abs(sum) == winningCase && winningCase < nFieldSide)
			sum += static_cast<int>(vecField[nFieldSide * winningCase++ + i]);
		if (abs(sum) == nFieldSide)
			return true;
	}
	//check first diagonal
	sum = 0;
	for (int x = 0, y = 0; y < nFieldSide && x < nFieldSide; x++, y++)
		sum += static_cast<int>(vecField[y * nFieldSide + x]);
	if (abs(sum) == nFieldSide)
		return true;
	//check second diagonal
	sum = 0;
	for (int x = nFieldSide - 1, y = 0; y < nFieldSide && x >= 0; x--, y++)
		sum += static_cast<int>(vecField[y * nFieldSide + x]);
	if (abs(sum) == nFieldSide)
		return true;
	return false;
}

bool Field::isDraw()
{
	bool isAI, isHuman;
	for (int i = 0; i < nFieldSide; i++)
	{
		isAI = false;
		isHuman = false;
		for (int j = 0; j < nFieldSide; j++)
		{
			if (vecField[i * nFieldSide + j] == player::AI)
				isAI = true;
			else if (vecField[i * nFieldSide + j] == player::Human)
				isHuman = true;
		}
		if (!(isAI && isHuman))
			return false;

		isAI = false;
		isHuman = false;
		for (int j = 0; j < nFieldSide; j++)
		{
			if (vecField[i + nFieldSide * j] == player::AI)
				isAI = true;
			else if (vecField[i + nFieldSide * j] == player::Human)
				isHuman = true;
		}
		if (!(isAI && isHuman))
			return false;
	}
	//check first diagonal
	isAI = false;
	isHuman = false;
	for (int x = 0, y = 0; y < nFieldSide && x < nFieldSide; x++, y++)
	{
		if (vecField[x + nFieldSide * y] == player::AI)
			isAI = true;
		else if (vecField[x + nFieldSide * y] == player::Human)
			isHuman = true;
	}
	if (!(isAI && isHuman))
		return false;
	//check second diagonal
	isAI = false;
	isHuman = false;
	for (int x = nFieldSide - 1, y = 0; y < nFieldSide && x >= 0; x--, y++)
	{
		if (vecField[x + nFieldSide * y] == player::AI)
			isAI = true;
		else if (vecField[x + nFieldSide * y] == player::Human)
			isHuman = true;
	}
	if (!(isAI && isHuman))
		return false;
	return true;
}

void Field::nullify()
{
	for (auto& p : vecField)
		p = player::None;
}
