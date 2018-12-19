#ifndef CONDITION_COMMAND_H
#define CONDITION_COMMAND_H

#include "Command.h"

class ConditionCommand : public Command
{
public:
	int execute();
};

#endif