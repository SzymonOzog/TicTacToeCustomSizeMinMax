#include "TranspositionTable.h"
#include <chrono>
#include <random>
TranspositionTable::TranspositionTable(std::shared_ptr<Field> f) : field(f)
{
	std::mt19937 generator(1729);
	std::uniform_int_distribution<unsigned long long> distribution;
	zobristKeys.reserve(2 * field->size());
	unsigned long long randomKey = 0;
	for (int i = 0; i < 2 * field->size(); i++)
	{
		do {
			randomKey = distribution(generator);
		} while (std::find(zobristKeys.begin(), zobristKeys.end(), randomKey) != zobristKeys.end());
		zobristKeys.emplace_back(randomKey);
	}
	entries.reserve(bigPrimeNumber);
	for (size_t i = 0; i < bigPrimeNumber; i++)
		entries.emplace_back(nullEntry);
}

unsigned long long TranspositionTable::recalculateHash()
{
	unsigned long long hash = 0;
	for (int i = 0; i < field->size(); i++)
		if ((*field)[i] != player::None)
			hash ^= zobristKeys[getKeyIndex(i)];
	return hash;
}

void TranspositionTable::placeEntry(unsigned long long hash, std::pair<int, int> scoreMove, int depth)
{
	Entry& e = entries[hash % entries.size()];
	if (e.hash != hash)
	{
		entryCollisions += e ? 1 : 0;
		updateEntry(e, hash, scoreMove, depth);
	}
	else if (depth > e.depth)
		updateEntry(e, hash, scoreMove, depth);
}

void TranspositionTable::updateEntry(Entry& e, unsigned long long hash, std::pair<int, int> scoreMove, int depth)
{
	e.hash = hash;
	e.scoreMove = scoreMove;
	e.depth = depth;
}


