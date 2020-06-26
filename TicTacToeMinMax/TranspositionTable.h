#pragma once
#include "Field.h"
#include <memory>
struct Entry
{
	Entry() : scoreMove({ 0, 2 }), hash(0) {}
	Entry(std::pair<int, int> _scoreMove, unsigned long long _hash) : scoreMove(_scoreMove), hash(_hash) {}
	std::pair<int, int> scoreMove;
	unsigned long long hash;
	bool operator == (const Entry& lhs) { return this->hash == lhs.hash; }
	bool operator != (const Entry & lhs) { return !((*this) == lhs); }
};
class TranspositionTable
{
public:
	TranspositionTable() = delete;
	TranspositionTable(std::shared_ptr<Field> f);


	unsigned long long calculateHash();
	inline unsigned long long recalculateHash(unsigned long long hash, int index) { return hash ^ zobristKeys[getKeyIndex(index)]; }
	Entry& operator[](int h) { 
		if (entries[h % entries.size()].hash == h) return entries[h % entries.size()]; 
		else return nullEntry; }
	void placeEntry(unsigned long long hash, std::pair<int, int> scoreMove);
public:
	Entry nullEntry;
private:
	int getKeyIndex(int i) { int index = 2 * i; index += (*field)[i] == player::AI ? 1 : 0; return index; }
private:
	std::shared_ptr<Field> field;
	std::vector<unsigned long long> zobristKeys;
	std::vector<Entry> entries;
	int bigPrimeNumber = 29030401;

};

