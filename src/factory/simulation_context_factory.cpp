#include "factory/simulation_context_factory.h"

#include "model/sample_data_model.h"
#include "factory/bridge_controller_factory.h"
#include "ui/bridge_window.h"
#include "controller/simulation/bridge_controller.h"
#include "context/application_context.h"
#include "context/bridge_simulation_context.h"

#include "model/application_configuration.h"
#include "model/configuration/simulation_option.h"

SimulationContextFactory::SimulationContextFactory(std::shared_ptr<ApplicationConfiguration> application_configuration) {
	this->application_configuration = application_configuration;
	this->bridge_controller_factory.reset(new BridgeControllerFactory());
	this->sample_data_model.reset(new SampleDataModel());
}

const std::vector<std::string>& SimulationContextFactory::get_controller_types() const {
	return this->bridge_controller_factory->get_controller_types();
}

const std::vector<std::string>& SimulationContextFactory::get_bridge_models() const {
	return this->sample_data_model->get_bridge_models();
}

const std::vector<std::string>& SimulationContextFactory::get_simulation_types() const {
	return this->sample_data_model->get_simulation_types();
}

std::unique_ptr<BridgeSimulationContext> SimulationContextFactory::create_simulation_context(std::string controller_type, std::string bridge_model_name, std::string simulation_model_name) {
	std::shared_ptr<BridgeModel> bridge_model = this->sample_data_model->load_bridge_model(bridge_model_name);
	std::shared_ptr<SimulationModel> simulation_model = this->sample_data_model->load_simulation_model(simulation_model_name);

	std::unique_ptr<BridgeWindow> bridge_window(new BridgeWindow(bridge_model, this->application_configuration));

	bridge_window->set_title(std::string("GL Window: ") + controller_type.substr(0, 15) + " " + simulation_model_name + " " + bridge_model_name);

	std::unique_ptr<BridgeController> bridge_controller = this->bridge_controller_factory->create_controller(controller_type);

	bridge_controller->set_bridge_model(bridge_model);
	bridge_controller->set_simulation_model(simulation_model);

	return std::unique_ptr<BridgeSimulationContext>(new BridgeSimulationContext(std::move(bridge_window), std::move(bridge_controller)));
}

void SimulationContextFactory::add_simulation(std::vector<std::shared_ptr<BridgeSimulationContext>>& simulations, const std::string& controller_type, const std::string& bridge_model, const std::string& simulation_type) {
	simulations.push_back(this->create_simulation_context(controller_type, bridge_model, simulation_type));
}

void SimulationContextFactory::demo_simulations(std::vector<std::shared_ptr<BridgeSimulationContext>>& simulations) {
	this->add_simulation(simulations, BridgeControllerFactory::ELASTIC_CONTROLLER, SampleDataModel::LINE_DIAGONAL, SampleDataModel::HUNDRED_TIME_FACTOR_SIMULATION);
	this->add_simulation(simulations, BridgeControllerFactory::MATRIX_ELASTIC_CONTROLLER, SampleDataModel::LINE_DIAGONAL, SampleDataModel::HUNDRED_TIME_FACTOR_SIMULATION);

	this->add_simulation(simulations, BridgeControllerFactory::ELASTIC_CONTROLLER, SampleDataModel::LINE_DIAGONAL, SampleDataModel::TEN_TIME_FACTOR_SIMULATION);
	this->add_simulation(simulations, BridgeControllerFactory::MATRIX_ELASTIC_CONTROLLER, SampleDataModel::LINE_DIAGONAL, SampleDataModel::TEN_TIME_FACTOR_SIMULATION);
}

int SimulationContextFactory::build_from_configuration(std::vector<std::shared_ptr<BridgeSimulationContext>>& simulations) {
	for (auto option : this->application_configuration->get_simulation_options()) {
		std::vector<std::string> controllers = option->get_controller_types();
		std::vector<std::string> bridge_models = option->get_bridge_models();
		std::vector<std::string> simulation_types = option->get_simulatio_types();
		
		if (controllers.size() == 1 && controllers.at(0) == "*") {
			controllers = this->get_controller_types();
		}

		if (bridge_models.size() == 1 && bridge_models.at(0) == "*") {
			bridge_models = this->get_bridge_models();
		}

		if (simulation_types.size() == 1 && simulation_types.at(0) == "*") {
			simulation_types = this->get_simulation_types();
		}

		for (auto controller : controllers) {
			for (auto bridge_model : bridge_models) {
				for (auto simulation_type : simulation_types) {

					try {
						this->add_simulation(simulations, controller, bridge_model, simulation_type);
					} catch (...) {
						return 1;
					}
				}
			}
		}
	}

	return 0;
}

int SimulationContextFactory::build_simulation_context(std::vector<std::shared_ptr<BridgeSimulationContext>>& result) {
	if (this->application_configuration->get_simulation_options().size() == 0) {
		this->demo_simulations(result);
	} else {
		if (this->build_from_configuration(result)) return 1;
	}

	return 0;
}
