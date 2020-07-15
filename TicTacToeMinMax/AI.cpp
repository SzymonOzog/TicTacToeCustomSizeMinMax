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
	Entry e = (*tTable)[hash];
	if (e && e.depth == reverseDepth)
			return e.scoreMove;
	if (reverseDepth == 0)
		return { 0, -2 };
	else if (field->canDrawOrWin() && lastPlay != -1)
	{
		if (field->hasWon(lastPlay))
			return { evaluateScore(currentPlayer), -1 };
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
			hash = tTable->calculateHash(hash, i);
			(*field)[i] = player::None;
			if (beta <= alpha)
				break;
		}
	}
	tTable->placeEntry(hash, bestScoreMove, reverseDepth, getEntryType(bestScoreMove, alpha, beta));
	return bestScoreMove;
}

void AI::printCollisions()
{
	std::cout << "Entry collisions: " << tTable->entryCollisions << std::endl;
}

EntryType AI::getEntryType(std::pair<int, int> scoreMove, int alpha, int beta)
{
	int score = scoreMove.first;
	if (score == alpha)
		return EntryType::lowerBound;
	else if (score == beta)
		return EntryType::upperBound;
	else if (score < alpha && score > beta)
		return EntryType::trueValue;
	return EntryType::nullEntry;
}
