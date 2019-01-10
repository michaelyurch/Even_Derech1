#ifndef SEARCHABLE_H
#define SEARCHABLE_H

#include "State.h"

#include <vector>

class Searchable
{
public:
virtual State getInitialState() = 0;
virtual State getGoalState() = 0;
virtual std::vector<State> getAllPossibleSDtates(State s) = 0;
virtual std::vector<State> getListOfStates() = 0;
};

#endif
