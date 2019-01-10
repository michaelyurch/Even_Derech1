#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>

class Coordinate
{
int x;
int y;
public:
	Coordinate() {
        this->x = 0;
        this->y = 0;
    }
	Coordinate(int _x, int _y) {
        this->x = _x;
        this->y = _y;
    }
    void setX(int _x) {
        this->x = x;
    }
    void setY(int _y) {
        this->y=  _y;
    }
    int getX() {
        return this->x;
    }
    int getY() {
        return this->y;
    }
    std::string getString() {
        std::string str = std::to_string(this->x);
        str += ",";
        str += std::to_string(this->y);
        return str;
    }
};

#endif
