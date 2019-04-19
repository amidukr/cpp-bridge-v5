#ifndef __COMMAND_LINE_CONTROLLER_H
#define __COMMAND_LINE_CONTROLLER_H

#include <memory>

class ApplicationConfiguration;

class CommandLineController
{
	std::shared_ptr<ApplicationConfiguration> application_configuration;

public:
	CommandLineController(std::shared_ptr<ApplicationConfiguration> application_configuration);

	int parse_arguments(int argc, char* argv[]);

private:
	// Disable copy constructor
	CommandLineController(const CommandLineController&); // no implementation 
	CommandLineController& operator=(const CommandLineController&); // no implementation
};

#endif /*__COMMAND_LINE_CONTROLLER_H*/