#ifndef ADMIN_H
#define ADMIN_H

#include <list>
#include <map>
#include <string.h>
#include <iostream>
#include <fstream>
//#include "Command.h"
//#include "Expression.h"

class admin {
public:
    std::list<std::string> lexer (std::string input);
    void parcer (std::list<std::string> input);
    int determineCurrentOperation(std::string expression);
};

#endif