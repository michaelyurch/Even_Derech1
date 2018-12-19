#ifndef VAR_COMMAND_H
#define VAR_COMMAND_H

#include "Command.h"

class VarCommand : public Command
{
public:
	int execute();
};

#endif