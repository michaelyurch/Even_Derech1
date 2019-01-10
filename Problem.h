#ifndef PROBLEM_H
#define PROBLEM_H

#include "Searchable.h"
#include "Coordinate.h"

#include <string>
#include <vector>
#include <iostream>

class Problem : public Searchable
{
	std::vector<std::vector<std::string>> matrix;
    Coordinate inCoord;
    Coordinate outCoord;
    int linesNum;
    int columnsNum;

    int getXCoord(std::string coordinate);
    int getYCoord(std::string coordinate);
    double getValueByCoordinate(Coordinate coord);
public:
	Problem(std::vector<std::vector<std::string>> _matrix, std::string _inCoordinate
            , std::string _outCoordinate);
    State getInitialState();
    State getGoalState();
    std::vector<State> getAllPossibleSDtates(State s);
    std::vector<State> getListOfStates();
    bool isPointInMatrixScope(int coordX, int coordY);
};

#endif
