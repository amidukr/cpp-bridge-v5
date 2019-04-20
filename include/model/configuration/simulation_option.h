#ifndef __SIMULATION_OPTION_H
#define __SIMULATION_OPTION_H

#include <string>
#include <vector>

class SimulationOption
{
	std::vector<std::string> controller_types;
	std::vector<std::string> bridge_models;
	std::vector<std::string> simulatio_types;

public:
	SimulationOption();

	const std::vector<std::string>& get_controller_types() const;
	const std::vector<std::string>& get_bridge_models() const;
	const std::vector<std::string>& get_simulatio_types() const;
	
	void add_controller_type(std::string controller_type);
	void add_bridge_model(std::string bridge_model);
	void add_simulation_type(std::string simulatio_type);

private:
	// Disable copy constructor
	SimulationOption(const SimulationOption&); // no implementation 
	SimulationOption& operator=(const SimulationOption&); // no implementation 
};

#endif /* __SIMULATION_OPTION_H */
