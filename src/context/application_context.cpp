#include "context/application_context.h"

#include "model/aplication_configuration.h"


ApplicationContext::ApplicationContext()
{
	this->application_configuration.reset(new ApplicationConfiguration());
}

std::shared_ptr<ApplicationConfiguration> ApplicationContext::get_application_configuration() const {
	return this->application_configuration;
}

std::vector<std::shared_ptr<BridgeSimulationContext>>& ApplicationContext::get_bridge_simulation_context() {
	return this->bridge_simulation_context;
}
