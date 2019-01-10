#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include "Searcher.h"
#include "Searchable.h"
#include "Solution.h"
#include "State.h"

#include <vector>
#include <map>
#include <queue>
#include <iostream>

class BestFirstSearch : public Searcher
{
Searchable* searchable;
int numberOfNodesEvaluated;

public:
	BestFirstSearch();
	Solution search(Searchable* _searchable);
	int getNumberOfNodesEvaluated();
};

#endif
