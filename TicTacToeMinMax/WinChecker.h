#pragma once
#include "Field.h"
#include <memory>
class WinCheckerTemplate
{
public:
	WinCheckerTemplate(std::shared_ptr<Field> _field) : field(_field) {}
	bool checkForWin()
	{
		while (canWin())
		{
			if(field->playerAt(column, row) == currentPlayer)
				points += static_cast<int>(field->playerAt(column, row));
			else
				points = static_cast<int>(field->playerAt(column, row));
			if (abs(points) == field->pointsNeededToWin)
				return true;
			currentPlayer = field->playerAt(column, row);
			stepFurther();
		}
		return false;
	}
	inline void updateCoord(const int& _column, const int& _row) { column = _column; row = _row; }
protected:
	bool canWin() { return maxPossiblePoints() >= field->pointsNeededToWin && field->coordInsideField(column, row); }
	virtual int maxPossiblePoints() = 0;
	virtual void stepFurther() = 0;
	std::shared_ptr<Field> field;
	int row = 0, column = 0;
	int points = 0;
	player currentPlayer = player::None;
};

