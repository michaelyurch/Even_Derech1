#ifndef BIND_COMMAND_H
#define BIND_COMMAND_H

#include "Command.h"

class BindCommand : public Command
{
public:
	int execute();
};

#endif