#pragma once
#include <memory>
#include "TranspositionTable.h"
class AI
{
public:
	AI() = delete;
	AI(std::shared_ptr<Field> f) : field(f) { tTable = std::make_unique<TranspositionTable>(field); }
	int findBestMove();
	std::pair<int, int> minMax(int reverseDepth = 10, std::pair<int, int> bestScoreMove = { 0, -1 }, player currentPlayer = player::AI, int alpha = INT_MIN, int beta = INT_MAX, int lastPlay = -1);
	void printCollisions();
private:
	inline player getOpponent(player p) { return p == player::AI ? player::Human : player::AI; }
	inline bool isValidEntry(std::pair<int, int> scoreMove) { return scoreMove.second != -2; }
	std::shared_ptr<Field> field;
	std::unique_ptr<TranspositionTable> tTable;
	unsigned long long hash;
};

