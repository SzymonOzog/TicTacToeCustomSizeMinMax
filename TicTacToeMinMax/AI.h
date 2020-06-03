#pragma once
#include <memory>
#include "Field.h"
class AI
{
public:
	AI() = delete;
	AI(std::shared_ptr<Field> f) : field(f) { nFieldSide = sqrt(f->size()); }

	std::pair<int, int> findBestMove(int reverseDepth = nFieldSide * nFieldSide, std::pair<int, int> bestScoreMove = { 0, -1 }, player currentPlayer = player::AI, int alpha = INT_MIN, int beta = INT_MAX, int lastPlay = -1);
private:
	static int nFieldSide;
	inline player getOpponent(player p) { return p == player::AI ? player::Human : player::AI; }
	std::shared_ptr<Field> field;
};

