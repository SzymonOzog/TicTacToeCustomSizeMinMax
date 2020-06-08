#include "AI.h"
std::pair<int, int> AI::findBestMove(int reverseDepth, std::pair<int, int> bestScoreMove, player currentPlayer, int alpha, int beta, int lastPlay)
{
	if (field->canDrawOrWin() && lastPlay != -1)
	{
		if (field->hasWon(lastPlay))
			return { reverseDepth * static_cast<int>(currentPlayer), -1 };
		else if (field->isDraw())
			return { 0, -1 };
	}
	if (reverseDepth == 0)
		return { 0, -1 };
	bestScoreMove.first = (currentPlayer == player::AI ? INT_MIN : INT_MAX);
	for (int i = 0; i < field->size(); i++)
	{
		if ((*field)[i] == player::None)
		{
			(*field)[i] = currentPlayer;
			int score = findBestMove(reverseDepth - 1, bestScoreMove, getOpponent(currentPlayer), alpha, beta, i).first;
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
			(*field)[i] = player::None;
			if (beta <= alpha)
				break;
		}
	}
	return bestScoreMove;
}