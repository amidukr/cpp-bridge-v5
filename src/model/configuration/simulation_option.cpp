#include "model/configuration/simulation_option.h"


SimulationOption::SimulationOption()
{
}


const std::vector<std::string>& SimulationOption::get_controller_types() const {
	return this->controller_types;
}

const std::vector<std::string>& SimulationOption::get_bridge_models() const {
	return this->bridge_models;
}

const std::vector<std::string>& SimulationOption::get_simulatio_types() const {
	return this->simulatio_types;
}

void SimulationOption::add_controller_type(std::string controller) {
	this->controller_types.push_back(controller);
}

void SimulationOption::add_bridge_model(std::string map) {
	this->bridge_models.push_back(map);
}

void SimulationOption::add_simulation_type(std::string option) {
	this->simulatio_types.push_back(option);
}
