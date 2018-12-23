#ifndef SLEEP_COMMAND_H
#define SLEEP_COMMAND_H

#include "Command.h"

class SleepCommand : public Command
{
	std::string timeToSleep;
public:
	int execute();
	void getFirstArgument(std::string arg){this->timeToSleep = arg;}
	void getSecondArgument(std::string arg){}
	void getThirdArgument(std::string arg){}
};

#endif