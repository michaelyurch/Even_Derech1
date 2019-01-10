#include "Problem.h"

Problem::Problem(std::vector<std::vector<std::string>> _matrix, std::string _inCoordinate
        , std::string _outCoordinate) {

    this->matrix = _matrix;

    this->linesNum = matrix.size();

    this->columnsNum = 0;
    if (matrix.size() > 0) {
        this->columnsNum = matrix[0].size();
    }

    this->inCoord = Coordinate(this->getXCoord(_inCoordinate)
        , this->getYCoord(_inCoordinate));
    this->outCoord = Coordinate(this->getXCoord(_outCoordinate)
        , this->getYCoord(_outCoordinate));

//    std::cout<<"Problem constr: "<<this->inCoord.getString()<<"\n";
}

State Problem::getInitialState() {
    State s(this->inCoord.getString(), this->getValueByCoordinate(this->inCoord)
        , "-1,-1", "none");
    return s;
}

State Problem::getGoalState() {
    State s(this->outCoord.getString(), this->getValueByCoordinate(this->outCoord)
        , "-1,-1", "none");
    return s;
}
    
std::vector<State> Problem::getAllPossibleSDtates(State s) {
    std::vector<State> allPossibleSDtates;

    std::string curCoordStr = s.getState();

    int curCoordX = this->getXCoord(curCoordStr);
    int curCoordY = this->getYCoord(curCoordStr);

//1
    if (this->isPointInMatrixScope(curCoordX - 1, curCoordY)) {

        std::string newCoordStr = std::to_string(curCoordX - 1);
        newCoordStr += ",";
        newCoordStr += std::to_string(curCoordY);

        allPossibleSDtates.push_back(State(newCoordStr
                , this->getValueByCoordinate(Coordinate(curCoordX - 1, curCoordY))
                , curCoordStr, "up"));
    }

//2
    if (this->isPointInMatrixScope(curCoordX + 1, curCoordY)) {

        std::string newCoordStr = std::to_string(curCoordX + 1);
        newCoordStr += ",";
        newCoordStr += std::to_string(curCoordY);

        allPossibleSDtates.push_back(State(newCoordStr
                , this->getValueByCoordinate(Coordinate(curCoordX + 1, curCoordY))
                , curCoordStr, "down"));
    }
//3
    if (this->isPointInMatrixScope(curCoordX, curCoordY - 1)) {

        std::string newCoordStr = std::to_string(curCoordX);
        newCoordStr += ",";
        newCoordStr += std::to_string(curCoordY - 1);

        allPossibleSDtates.push_back(State(newCoordStr
                , this->getValueByCoordinate(Coordinate(curCoordX, curCoordY - 1))
                , curCoordStr, "left"));
    }
//4
    if (this->isPointInMatrixScope(curCoordX, curCoordY + 1)) {

        std::string newCoordStr = std::to_string(curCoordX);
        newCoordStr += ",";
        newCoordStr += std::to_string(curCoordY + 1);

        allPossibleSDtates.push_back(State(newCoordStr
                , this->getValueByCoordinate(Coordinate(curCoordX, curCoordY + 1))
                , curCoordStr, "right"));
    }
/*
//5
    if (this->isPointInMatrixScope(curCoordX - 1, curCoordY -1)) {

        std::string newCoordStr = std::to_string(curCoordX - 1);
        newCoordStr += ",";
        newCoordStr += std::to_string(curCoordY - 1);

        allPossibleSDtates.push_back(State(newCoordStr
                , this->getValueByCoordinate(Coordinate(curCoordX - 1, curCoordY - 1))
                , curCoordStr));
    }
//6
    if (this->isPointInMatrixScope(curCoordX + 1, curCoordY + 1)) {

        std::string newCoordStr = std::to_string(curCoordX + 1);
        newCoordStr += ",";
        newCoordStr += std::to_string(curCoordY + 1);

        allPossibleSDtates.push_back(State(newCoordStr
                , this->getValueByCoordinate(Coordinate(curCoordX + 1, curCoordY + 1))
                , curCoordStr));
    }
//7
    if (this->isPointInMatrixScope(curCoordX - 1, curCoordY + 1)) {

        std::string newCoordStr = std::to_string(curCoordX - 1);
        newCoordStr += ",";
        newCoordStr += std::to_string(curCoordY + 1);

        allPossibleSDtates.push_back(State(newCoordStr
                , this->getValueByCoordinate(Coordinate(curCoordX - 1, curCoordY + 1))
                , curCoordStr));
    }
//8
    if (this->isPointInMatrixScope(curCoordX + 1, curCoordY - 1)) {

        std::string newCoordStr = std::to_string(curCoordX + 1);
        newCoordStr += ",";
        newCoordStr += std::to_string(curCoordY - 1);

        allPossibleSDtates.push_back(State(newCoordStr
                , this->getValueByCoordinate(Coordinate(curCoordX + 1, curCoordY - 1))
                , curCoordStr));
    }
*/
    return allPossibleSDtates;
}

std::vector<State> Problem::getListOfStates() {
    std::vector<State> allPossibleSDtates;

    for (int i = 0; i < this->matrix.size(); ++i) {
        std::vector<std::string> curLine = matrix[i];
        for (int i2 = 0; i2 < curLine.size(); ++ i2) {

            std::string curState = std::to_string(i);
            curState += ",";
            curState += std::to_string(i2);

            allPossibleSDtates.push_back(State(curState
                    , this->getValueByCoordinate(Coordinate(i, i2))
                    , "-1,-1", "none"));
        }
    }

    return allPossibleSDtates;
}

bool Problem::isPointInMatrixScope(int coordX, int coordY) {
    if (coordX < 0 || coordY < 0 
            || coordX > this->linesNum - 1 || coordY > this->columnsNum - 1) {

        return false;    
    }

    return true;
}

int Problem::getXCoord(std::string coordinate) {

    std::string xCoord;

    for (int i = 0; i < coordinate.length(); i++) {
        if (coordinate[i] == ',') {
            break;
        }
        xCoord += coordinate[i];
    }

    return std::stoi(xCoord);
}

int Problem::getYCoord(std::string coordinate) {

    std::string yCoord;
    bool isCommaApeared = false;

    for (int i = 0; i < coordinate.length(); i++) {
        if (coordinate[i] == ',') {
            isCommaApeared = true;
            continue;
        }

        else if (isCommaApeared) {
            yCoord += coordinate[i];
        }
    }

    return std::stoi(yCoord);
}

double Problem::getValueByCoordinate(Coordinate coord) {
    std::vector<std::string> curLine = this->matrix[coord.getX()]; 
    return std::stod(curLine[coord.getY()]);
}