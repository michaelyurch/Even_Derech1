#ifndef STATE_H
#define STATE_H

#include <string>

class State {
    std::string state;
    double cost;
    std::string cameFrom;
    std::string directionFromCameFrom; // up/down/left/right/none (if came from -1,-1)
    public:
    State(std::string _state, double _cost, std::string _cameFrom, std::string _directionFromCameFrom) {
        this->state = _state;
        this->cost = _cost;
        this->cameFrom = _cameFrom;
        this->directionFromCameFrom = _directionFromCameFrom;
    }

    bool isEqual(State _state) {
        
        int compareResult = this->state.compare(_state.state);
        
        if(compareResult == 0) {
            return true;
        } 

        return false;
    }

    std::string getState() {
        return this->state;
    }

    double getCost() {
        return this->cost;
    }

    std::string getDirection() {
        return this->directionFromCameFrom;
    }

    bool operator < (const State& _state) const {
        if (this->cost > _state.cost) {
            return true;
        }

        return false;
    }
};

#endif