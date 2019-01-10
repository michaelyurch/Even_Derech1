#ifndef SOLVER_H
#define SOLVER_H

#include "Searchable.h"
#include "Solution.h"

class Solver
{
public:
	virtual Solution solve(Searchable* searchable) = 0;
};

#endif