#include "context/application_context.h"

#include "factory/simulation_context_factory.h"
#include "controller/command_line_controller.h"
#include "model/application_configuration.h"


ApplicationContext::ApplicationContext(int argc, char ** argv)
{
	this->argc = argc;
	this->argv = argv;

	this->application_configuration.reset(new ApplicationConfiguration());
	this->simulation_context_factory.reset(new SimulationContextFactory(this->application_configuration));
	this->command_line_controller.reset(new CommandLineController(this->application_configuration, this->simulation_context_factory));
}



int ApplicationContext::get_argc() {
	return this->argc;
}

char ** ApplicationContext::get_argv() {
	return this->argv;
}

std::shared_ptr<SimulationContextFactory> ApplicationContext::get_simulation_context_factory() const {
	return this->simulation_context_factory;
}

std::shared_ptr<ApplicationConfiguration> ApplicationContext::get_application_configuration() const {
	return this->application_configuration;
}

std::vector<std::shared_ptr<BridgeSimulationContext>>& ApplicationContext::get_bridge_simulation_context() {
	return this->bridge_simulation_context;
}

std::shared_ptr<CommandLineController> ApplicationContext::get_command_line_controller() const {
	return this->command_line_controller;
}
