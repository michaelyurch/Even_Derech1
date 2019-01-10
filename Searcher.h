#ifndef SEARCHER_H
#define SEARCHER_H

#include "Solution.h"
#include "Searchable.h"

#include <string>
#include <vector>

class Searcher
{
public:
	virtual Solution search(Searchable* searchable) = 0;
	virtual int getNumberOfNodesEvaluated() = 0;
};

#endif
