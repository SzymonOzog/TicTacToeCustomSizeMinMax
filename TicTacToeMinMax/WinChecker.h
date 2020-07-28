#pragma once
#include "Field.h"
#include <memory>
class WinCheckerTemplate
{
public:
	WinCheckerTemplate(Field* _field) : field(_field) {}
	bool checkAllLines()
	{
		for (auto coord : allCoords())
			if (checkForWin(coord))
				return true;
		return false;
	}
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
			if (abs(points) == field->getPointsNeededToWin())
				return true;
			currentPlayer = field->playerAt(column, row);
			stepFurther();
		}
		return false;
	}
protected:

	bool canWin() { return maxPossiblePoints() >= field->getPointsNeededToWin() && field->coordInsideField(column, row); }
	virtual std::vector<int> allCoords() = 0;
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
	virtual std::vector<int> allCoords()
	{
		std::vector<int> coords;
		for (int i = 0; i < field->size(); i += field->fieldSide)
			coords.push_back(i);
		return coords;
	}
	virtual void updateCoord(const int& coord) { row = field->getRow(coord); column = 0; }
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
	virtual std::vector<int> allCoords()
	{
		std::vector<int> coords;
		for (int i = 0; i < field->fieldSide; i++)
			coords.push_back(i);
		return coords;
	}
	virtual void updateCoord(const int& coord) { row = 0; column = field->getColumn(coord); }
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
	std::vector<int> allCoords()
	{
		std::vector<int> coords;
		int row = 0, column = 0;
		while (field->fieldSide - row >= field->getPointsNeededToWin())
			coords.push_back(field->coordToField(column, row++));
		row = 0;
		while (field->fieldSide - column >= field->getPointsNeededToWin())
			coords.push_back(field->coordToField(column++, row));
		return coords;
	}
	virtual void updateCoord(const int& coord) 
	{ 
		row = field->getRow(coord); 
		column = field->getColumn(coord); 
		int diff = std::min(row, column); 
		column -= diff; 
		row -= diff; 
	}
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
	std::vector<int> allCoords()
	{
		std::vector<int> coords;
		int row = 0, column = 0;
		while (field->fieldSide - row >= field->getPointsNeededToWin())
			coords.push_back(field->coordToField(field->fieldSide - 1 - column, row++));
		row = 0;
		while (field->fieldSide - column >= field->getPointsNeededToWin())
			coords.push_back(field->coordToField(field->fieldSide - 1 - column++, row));
		return coords;
	}
	virtual void updateCoord(const int& coord) 
	{	
		row = field->getRow(coord);
		column = field->getColumn(coord); 
		int diff = std::min(row, (field->fieldSide - 1 - column)); 
		column += diff; 
		row -= diff;
	}
	virtual int maxPossiblePoints() {
		return field->fieldSide - row + abs(points);
	}
	virtual void stepFurther() { column--; row++; }
};
