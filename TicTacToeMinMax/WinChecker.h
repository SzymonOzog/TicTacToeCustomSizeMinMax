#pragma once
#include "Field.h"
#include <memory>
class WinCheckerTemplate
{
public:
	WinCheckerTemplate(Field* _field) : field(_field) {}
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
	Field* field;
	int row = 0, column = 0;
	int points = 0;
	player currentPlayer = player::None;
};

class RowChecker : public WinCheckerTemplate
{
public:
	RowChecker(Field* _field) : WinCheckerTemplate(_field) {}
protected:
	virtual int maxPossiblePoints() {
		return field->fieldSide - column + abs(points);
	}
	virtual void stepFurther() { column++; }
};

class ColumnChecker : public WinCheckerTemplate
{
public:
	ColumnChecker(Field* _field) : WinCheckerTemplate(_field) {}
protected:
	virtual int maxPossiblePoints() {
		return field->fieldSide - row + abs(points);
	}
	virtual void stepFurther() { row++; }
};

class ForwardDiagonalChecker : public WinCheckerTemplate
{
public:
	ForwardDiagonalChecker(Field* _field) : WinCheckerTemplate(_field) {}
protected:
	virtual int maxPossiblePoints() {
		return field->fieldSide - row + abs(points);
	}
	virtual void stepFurther() { column++; row++; }
};
