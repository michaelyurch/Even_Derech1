#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include "Searcher.h"
#include "Searchable.h"
#include "Solution.h"
#include "State.h"

#include <vector>
#include <map>
#include <iostream>

class DepthFirstSearch : public Searcher
{
Searchable* searchable;
int numberOfNodesEvaluated;

public:
	DepthFirstSearch();
	Solution search(Searchable* _searchable);
	int getNumberOfNodesEvaluated();
};

#endif
