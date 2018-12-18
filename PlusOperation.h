#ifndef PLUS_H
#define PLUS_H

#include "Expression.h"

class PlusOperation : public Expression
{
    Expression* leftOperand;
    Expression* rightOperand;
public:
    PlusOperation(std::string leftOperand, std::string rightOperand);
	std::string calculate();
};

#endif