#include "AI.h"
#include <iostream>
int AI::findBestMove()
{
	hash = tTable->recalculateHash();
	int bestMove = minMax().second;
	return bestMove;
}

std::pair<int, int> AI::minMax(int reverseDepth, std::pair<int, int> bestScoreMove, player currentPlayer, int alpha, int beta, int lastPlay)
{
	if ((*tTable)[hash] != tTable->nullEntry)
		return (*tTable)[hash].scoreMove;
	else if (reverseDepth == 0)
		return { 0, -1 };
	else if (field->canDrawOrWin() && lastPlay != -1)
	{
		if (field->hasWon(lastPlay))
			return { (field->getEmptyCoords() + 1) * static_cast<int>(currentPlayer), -1 };
		else if (field->isDraw())
			return { 0, -1 };
	}
	bestScoreMove.first = currentPlayer == player::AI ? INT_MIN : INT_MAX;
	for (int i = 0; i < field->size(); i++)
	{
		if ((*field)[i] == player::None && field->isCoordWorthChecking(i))
		{
			(*field)[i] = currentPlayer;
			hash = tTable->calculateHash(hash, i);
			std::pair<int, int> scoreMove = minMax(reverseDepth - 1, bestScoreMove, getOpponent(currentPlayer), alpha, beta, i);
			if (currentPlayer == player::AI)
			{
				alpha = std::max(alpha, scoreMove.first);
				if (bestScoreMove.first < scoreMove.first)
					bestScoreMove = { scoreMove.first, i };
			}
			else
			{
				beta = std::min(beta, scoreMove.first);
				if (bestScoreMove.first > scoreMove.first)
					bestScoreMove = { scoreMove.first, i };
			}
			tTable->placeEntry(hash, scoreMove);
			hash = tTable->calculateHash(hash, i);
			(*field)[i] = player::None;
			if (beta <= alpha)
				break;
		}
	}
	return bestScoreMove;
}

void AI::printCollisions()
{
	std::cout << tTable->collisions << std::endl;
}
