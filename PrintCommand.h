#ifndef PRINT_COMMAND_H
#define PRINT_COMMAND_H

#include "Command.h"

class PrintCommand : public Command
{
public:
	int execute();
};

#endif