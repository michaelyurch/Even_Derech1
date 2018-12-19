#ifndef ASSIGNMENT_COMMAND_H
#define ASSIGNMENT_COMMAND_H

#include "Command.h"

class AssignmentCommand : public Command
{
public:
	int execute();
};

#endif