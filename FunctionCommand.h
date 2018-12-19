#ifndef FUNCTION_COMMAND_H
#define FUNCTION_COMMAND_H

#include "Command.h"

class FunctionCommand : public Command
{
public:
	int execute();
};

#endif