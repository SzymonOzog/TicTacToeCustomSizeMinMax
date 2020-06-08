#pragma once
#include <memory>
#include "Field.h"
class AI
{
public:
	AI() = delete;
	AI(std::shared_ptr<Field> f) : field(f) {}

	std::pair<int, int> findBestMove(int reverseDepth = 10, std::pair<int, int> bestScoreMove = { 0, -1 }, player currentPlayer = player::AI, int alpha = INT_MIN, int beta = INT_MAX, int lastPlay = -1);
private:
	inline player getOpponent(player p) { return p == player::AI ? player::Human : player::AI; }
	std::shared_ptr<Field> field;
};

