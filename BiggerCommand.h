#ifndef BIGGER_COMMAND_H
#define BIGGER_COMMAND_H

#include "Command.h"

class BiggerCommand : public Command
{
public:
	int execute();
};

#endif