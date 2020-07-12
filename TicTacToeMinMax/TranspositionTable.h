#pragma once
#include "Field.h"
#include <memory>
struct Entry
{
	Entry() = default;
	Entry(std::pair<int, int> _scoreMove, unsigned long long _hash, int _depth) : scoreMove(_scoreMove), hash(_hash), depth(_depth) {}
	std::pair<int, int> scoreMove = { 0, -2 };
	unsigned long long hash = 0;
	int depth = 0;
	bool operator == (const Entry& lhs) { return this->hash == lhs.hash; }
	bool operator != (const Entry & lhs) { return !((*this) == lhs); }
	operator bool() { return hash; }
};
class TranspositionTable
{
public:
	TranspositionTable() = delete;
	TranspositionTable(std::shared_ptr<Field> f);

	unsigned long long recalculateHash();
	inline unsigned long long calculateHash(unsigned long long hash, int index) { return hash ^ zobristKeys[getKeyIndex(index)]; }
	void placeEntry(unsigned long long hash, std::pair<int, int> scoreMove, int depth);
	void updateEntry(Entry& e, unsigned long long hash, std::pair<int, int> scoreMove, int depth);

	Entry& operator[](unsigned long long h) { 
		if (entries[h % entries.size()].hash == h) return entries[h % entries.size()]; 
		else return nullEntry; }
public:
	Entry nullEntry;
	unsigned int entryCollisions = 0;
private:
	inline int getKeyIndex(int i) { int index = 2 * i; index += (*field)[i] == player::AI ? 1 : 0; return index; }
private:
	std::shared_ptr<Field> field;
	std::vector<unsigned long long> zobristKeys;
	std::vector<Entry> entries;
	unsigned long long bigPrimeNumber = 29030401;
};

