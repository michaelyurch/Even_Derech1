#ifndef ADMIN_H
#define ADMIN_H

#include <list>
#include <map>
#include <string.h>
#include <iostream>
#include <fstream>

#include "Command.h"
#include "Expression.h"
#include "Number.h"
#include "PlusOperation.h"
#include "MinusOperation.h"
#include "MulOperation.h"
#include "DivOperation.h"

#include "OpenDataServerCommand.h"

class admin {
public:
    std::list<std::string> lexer (std::string input);
    void parcer (std::list<std::string> items);
    Expression* determineCurrentOperation(std::string expression);
    bool isExpression(std::string input);
    bool isContainsSpacesOnly(std::string input);
};

#endif