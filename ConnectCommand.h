#ifndef CONNECT_COMMAND_H
#define CONNECT_COMMAND_H

#include "Command.h"

class ConnectCommand : public Command
{
public:
	int execute();
};

#endif