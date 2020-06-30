#include "TranspositionTable.h"
#include <chrono>
#include <random>
TranspositionTable::TranspositionTable(std::shared_ptr<Field> f) : field(f)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<unsigned long long> distribution;
	zobristKeys.reserve(2 * field->size());
	for (int i = 0; i < 2 * field->size(); i++)
	{
		unsigned long long rand = distribution(generator);
		while (std::find(zobristKeys.begin(), zobristKeys.end(), rand) != zobristKeys.end())
			rand = distribution(generator);
		zobristKeys.emplace_back(rand);
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

void TranspositionTable::placeEntry(unsigned long long hash, std::pair<int, int> scoreMove)
{
	Entry& e = entries[hash % entries.size()];
	if (e.hash != hash)
	{
		collisions += e.hash == 0 ? 0 : 1;
		e.hash = hash;
		e.scoreMove = scoreMove;
	}
}


