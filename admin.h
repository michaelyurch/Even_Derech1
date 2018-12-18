#ifndef ADMIN_H
#define ADMIN_H

#include <list>
#include <map>
#include <string.h>
#include <iostream>
#include <fstream>
//#include "Command.h"
#include "Expression.h"
#include "Number.h"
#include "PlusOperation.h"

class admin {
public:
    std::list<std::string> lexer (std::string input);
    void parcer (std::list<std::string> input);
    Expression* determineCurrentOperation(std::string expression);
};

#endif