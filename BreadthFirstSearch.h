#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H

#include "Searcher.h"
#include "Searchable.h"
#include "Solution.h"
#include "State.h"

#include <vector>
#include <map>
#include <iostream>

class BreadthFirstSearch : public Searcher
{
Searchable* searchable;
int numberOfNodesEvaluated;

public:
	BreadthFirstSearch();
	Solution search(Searchable* _searchable);
	int getNumberOfNodesEvaluated();
};

#endif
