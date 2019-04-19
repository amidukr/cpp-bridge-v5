#include "context/application_context.h"

#include "controller/command_line_controller.h"

#include "model/aplication_configuration.h"


ApplicationContext::ApplicationContext()
{
	this->application_configuration.reset(new ApplicationConfiguration());
	this->command_line_controller.reset(new CommandLineController(this->application_configuration));
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
