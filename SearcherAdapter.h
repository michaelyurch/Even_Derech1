#ifndef SEARCHER_ADAPTER_H
#define SEARCHER_ADAPTER_H

#include "Searcher.h"
#include "Searchable.h"
#include "Solver.h"

#include <string>

class SearcherAdapter : public Solver
{
Searcher* searcher;
public:
	SearcherAdapter(Searcher* _searcher) {
		this->searcher = _searcher;	
	}
	
	Solution solve(Searchable* searchable) {
		Solution solution = this->searcher->search(searchable);
		return solution;
	}
};

#endif
