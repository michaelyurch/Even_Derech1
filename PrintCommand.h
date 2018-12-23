#ifndef PRINT_COMMAND_H
#define PRINT_COMMAND_H

#include "Command.h"

class PrintCommand : public Command
{
	std::string output;
public:
	int execute();
	void getFirstArgument(std::string arg){this->output = arg;}
	void getSecondArgument(std::string arg){}
	void getThirdArgument(std::string arg){}
};

#endif