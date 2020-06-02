#include "AI.h"
std::pair<int, int> AI::findBestMove(int reverseDepth, std::pair<int, int> bestScoreMove, player currentPlayer, int alpha, int beta)
{
	if (field->canDrawOrWin())
	{
		if (field->getState() == field::Won)
			return { reverseDepth * static_cast<int>(currentPlayer), -1 };
		else if (field->getState() == field::Draw)
			return { 0, -1 };
	}
	bestScoreMove.first = (currentPlayer == player::AI ? INT_MIN : INT_MAX);
	for (int i = 0; i < field->size(); i++)
	{
		if (field->at(i) == player::None)
		{
			field->set(i, currentPlayer);
			int score = findBestMove(reverseDepth - 1, bestScoreMove, getOpponent(currentPlayer), alpha, beta).first;
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
			field->set(i, player::None);
			if (beta <= alpha)
				break;
		}
	}
	return bestScoreMove;
}