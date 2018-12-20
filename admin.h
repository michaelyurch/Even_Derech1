#ifndef ADMIN_H
#define ADMIN_H

#include <vector>
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
#include "ConnectCommand.h"
#include "VarCommand.h"
#include "AssignmentCommand.h"
#include "BindCommand.h"
#include "ConditionCommand.h"
#include "LoopCommand.h"
#include "BiggerCommand.h"
#include "BiggerEqualsCommand.h"
#include "SmallerCommand.h"
#include "SmallerEqualsCommand.h"
#include "EqualsCommand.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "OpenDataServerCommand.h"

class admin {
public:
    std::vector<std::string> lexer (std::string input);
    void parcer (std::vector<std::string> items);
    Expression* determineCurrentOperation(std::string expression);
    bool isExpressionToCalculation(std::string input);
    bool isContainsSpacesOnly(std::string input);
};

#endif