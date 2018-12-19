#ifndef LOOP_COMMAND_H
#define LOOP_COMMAND_H

#include "Command.h"

class LoopCommand : public Command
{
public:
	int execute();
};

#endif