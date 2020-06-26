#include "AI.h"
int AI::findBestMove()
{
	hash = tTable->calculateHash();
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
			hash = tTable->recalculateHash(hash, i);
			int score = minMax(reverseDepth - 1, bestScoreMove, getOpponent(currentPlayer), alpha, beta, i).first;
			if (currentPlayer == player::AI)
			{
				alpha = std::max(alpha, score);
				if (bestScoreMove.first < score)
					bestScoreMove = { score, i };
			}
			else
			{
				beta = std::min(beta, score);
				if (bestScoreMove.first > score)
					bestScoreMove = { score, i };
			}
			hash = tTable->recalculateHash(hash, i);
			(*field)[i] = player::None;
			if (beta <= alpha)
				break;
		}
	}
	tTable->placeEntry(hash, bestScoreMove);
	return bestScoreMove;
}