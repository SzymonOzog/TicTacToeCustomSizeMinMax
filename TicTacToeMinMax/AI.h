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
	inline int evaluateScore(player p) { return (field->getEmptyCoords() + 1) * static_cast<int>(p); }
	inline player getOpponent(player p) { return p == player::AI ? player::Human : player::AI; }
	EntryType getEntryType(std::pair<int, int> scoreMove, int alpha, int beta);
	std::shared_ptr<Field> field;
	std::unique_ptr<TranspositionTable> tTable;
	unsigned long long hash;
};

