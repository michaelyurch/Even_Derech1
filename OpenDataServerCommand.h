#ifndef OPEN_DATA_SERVER_COMMAND_H
#define OPEN_DATA_SERVER_COMMAND_H

#include "Command.h"

class OpenDataServerCommand : public Command
{
public:
	int execute();
};

#endif