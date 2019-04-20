#ifndef __SIMULATION_CONTEXT_FACTORY_H
#define __SIMULATION_CONTEXT_FACTORY_H

#include <vector>
#include <memory>

class ApplicationConfiguration;
class ApplicationContext;
class BridgeSimulationContext;
class SampleDataModel;
class BridgeControllerFactory;

class SimulationContextFactory
{
	std::shared_ptr<ApplicationConfiguration> application_configuration;
	std::shared_ptr<BridgeControllerFactory> bridge_controller_factory;
	std::shared_ptr<SampleDataModel> sample_data_model;

	std::unique_ptr<BridgeSimulationContext> create_simulation_context(std::string controller_type, std::string bridge_model_name, std::string simulation_model_name);
	void add_simulation(std::vector<std::shared_ptr<BridgeSimulationContext>>& simulations, const std::string& controller_type, const std::string& bridge_model, const std::string& simulation_type);
	void demo_simulations(std::vector<std::shared_ptr<BridgeSimulationContext>>& simulations);
	int build_from_configuration(std::vector<std::shared_ptr<BridgeSimulationContext>>& simulations);

public:
	SimulationContextFactory(std::shared_ptr<ApplicationConfiguration> application_configuration);

	int build_simulation_context(std::vector<std::shared_ptr<BridgeSimulationContext>>& result);

	const std::vector<std::string>& get_controller_types() const;
	const std::vector<std::string>& get_bridge_models() const;
	const std::vector<std::string>& get_simulation_types() const;
private:
	// Disable copy constructor
	SimulationContextFactory(const SimulationContextFactory&); // no implementation 
	SimulationContextFactory& operator=(const SimulationContextFactory&); // no implementation 
};

#endif /* __SIMULATION_CONTEXT_FACTORY_H */