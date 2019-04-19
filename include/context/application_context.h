#ifndef __APPLICATION_CONTEXT_H
#define __APPLICATION_CONTEXT_H

#include<memory>
#include<vector>

class ApplicationConfiguration;
class BridgeSimulationContext;

class ApplicationContext
{
	std::shared_ptr<ApplicationConfiguration> application_configuration;
	std::vector<std::shared_ptr<BridgeSimulationContext>> bridge_simulation_context;

public:
	ApplicationContext();

	std::shared_ptr<ApplicationConfiguration> get_application_configuration() const;
	std::vector<std::shared_ptr<BridgeSimulationContext>>& get_bridge_simulation_context();

private:
	// Disable copy constructor
	ApplicationContext(const ApplicationContext&); // no implementation 
	ApplicationContext& operator=(const ApplicationContext&); // no implementation
};

#endif /*__APPLICATION_CONTEXT_H*/
