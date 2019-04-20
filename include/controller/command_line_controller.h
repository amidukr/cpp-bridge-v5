#ifndef __COMMAND_LINE_CONTROLLER_H
#define __COMMAND_LINE_CONTROLLER_H

#include <memory>
#include <vector>

class ApplicationConfiguration;
class SimulationContextFactory;

class CommandLineController
{
	std::shared_ptr<ApplicationConfiguration> application_configuration;
	std::shared_ptr<SimulationContextFactory> simulation_context_factory;

	int parse_simulations(const std::vector<std::string>& simulations);
	void print_simulation_help();

public:
	static const int SUCCESS = 0;
	static const int COMPLITION = 1;
	static const int HELP = 2;
	static const int ERROR = 3;

	CommandLineController(std::shared_ptr<ApplicationConfiguration> application_configuration, std::shared_ptr<SimulationContextFactory> simulation_context_factory);

	int parse_arguments(int argc, const char* const argv[]);

private:
	// Disable copy constructor
	CommandLineController(const CommandLineController&); // no implementation 
	CommandLineController& operator=(const CommandLineController&); // no implementation
};

#endif /*__COMMAND_LINE_CONTROLLER_H*/