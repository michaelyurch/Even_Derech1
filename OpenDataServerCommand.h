#ifndef OPEN_DATA_SERVER_COMMAND_H
#define OPEN_DATA_SERVER_COMMAND_H

#include "Command.h"

class OpenDataServerCommand : public Command
{
	std::string port;
	std::string frequency;
public:
	int execute();
	void getFirstArgument(std::string arg){this->port = arg;}
	void getSecondArgument(std::string arg){this->frequency = arg;}
	void getThirdArgument(std::string arg){}
};

#endif