#ifndef SLEEP_COMMAND_H
#define SLEEP_COMMAND_H

#include "Command.h"

class SleepCommand : public Command
{
public:
	int execute();
};

#endif