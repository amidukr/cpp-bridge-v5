#ifndef __APPLICATION_CONTEXT_H
#define __APPLICATION_CONTEXT_H

#include<memory>
#include<vector>

class ApplicationConfiguration;
class BridgeSimulationContext;
class CommandLineController;
class SimulationContextFactory;

class ApplicationContext
{
	
	int argc;
	char ** argv;

	std::shared_ptr<CommandLineController> command_line_controller;

	std::shared_ptr<SimulationContextFactory> simulation_context_factory;

	std::shared_ptr<ApplicationConfiguration> application_configuration;
	std::vector<std::shared_ptr<BridgeSimulationContext>> bridge_simulation_context;

public:
	ApplicationContext(int argc,  char ** argv);

	int get_argc();
	char ** get_argv();

	std::shared_ptr<CommandLineController> get_command_line_controller() const;
	std::shared_ptr<SimulationContextFactory> get_simulation_context_factory() const;
	std::shared_ptr<ApplicationConfiguration> get_application_configuration() const;

	std::vector<std::shared_ptr<BridgeSimulationContext>>& get_bridge_simulation_context();

private:
	// Disable copy constructor
	ApplicationContext(const ApplicationContext&); // no implementation 
	ApplicationContext& operator=(const ApplicationContext&); // no implementation
};

#endif /*__APPLICATION_CONTEXT_H*/
