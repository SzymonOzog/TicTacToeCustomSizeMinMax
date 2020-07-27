#pragma once
#include "Field.h"
#include <memory>
class WinCheckerTemplate
{
public:
	WinCheckerTemplate(Field* _field) : field(_field) {}
	bool checkForWin(const int& coord)
	{
		points = 0;
		updateCoord(coord);
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
protected:
	bool canWin() { return maxPossiblePoints() >= field->pointsNeededToWin && field->coordInsideField(column, row); }
	virtual void updateCoord(const int& coord) = 0;
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
	virtual void updateCoord(const int& coord) { row = coord / field->fieldSide; column = 0; }
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
	virtual void updateCoord(const int& coord) { row = 0; column = coord % field->fieldSide; }
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
	virtual void updateCoord(const int& coord) { row = getForwardDiagonalCoord(coord).second; column = getForwardDiagonalCoord(coord).first; }
	inline std::pair<int, int> getForwardDiagonalCoord(int i) { int row = i / field->fieldSide; column = i % field->fieldSide; int diff = std::min(row, column); return { column - diff, row - diff }; }

	virtual int maxPossiblePoints() {
		return field->fieldSide - row + abs(points);
	}
	virtual void stepFurther() { column++; row++; }
};

class BackwardDiagonalChecker : public WinCheckerTemplate
{
public:
	BackwardDiagonalChecker(Field* _field) : WinCheckerTemplate(_field) {}
protected:
	virtual void updateCoord(const int& coord) { row = getBackwardDiagonalCoord(coord).second; column = getBackwardDiagonalCoord(coord).first;}
	inline std::pair<int, int> getBackwardDiagonalCoord(int i) { int row = i / field->fieldSide; column = i % field->fieldSide; int diff = std::min(row, (field->fieldSide - 1 - column)); return { column + diff, row - diff }; }
	virtual int maxPossiblePoints() {
		return field->fieldSide - row + abs(points);
	}
	virtual void stepFurther() { column--; row++; }
};
