#include <stdio.h>
#include <stdlib.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "model/bridge_model.h"
#include "ui/bridge_window.h"

#include "controller/bridge_controller.h"
#include "factory/bridge_controller_factory.h"

#include "model/sample_data_model.h"
#include "context/bridge_simulation_context.h"
#include<model/simulation_model.h>

#include <chrono>
#include <thread>

#include "model/aplication_configuration.h"

#include <gtest/gtest.h>

#include <context/application_context.h>

std::unique_ptr<BridgeSimulationContext> create_simulation_context(ApplicationContext& context, std::string controller_type, std::string bridge_model_name, std::string simulation_model_name) {
	SampleDataModel sample_data_model;
	BridgeControllerFactory bridge_controller_factory;


	std::shared_ptr<BridgeModel> bridge_model = sample_data_model.load_bridge_model(bridge_model_name);
	std::shared_ptr<SimulationModel> simulation_model = sample_data_model.load_simulation_model(simulation_model_name);

	std::unique_ptr<BridgeWindow> bridge_window(new BridgeWindow(bridge_model, context.get_application_configuration()));

	bridge_window->set_title(std::string("GL Window: ") + controller_type.substr(0, 15) + " " +simulation_model_name  + " " + bridge_model_name);

	std::unique_ptr<BridgeController> bridge_controller = bridge_controller_factory.create_controller(controller_type);

	bridge_controller->set_bridge_model(bridge_model);
	bridge_controller->set_simulation_model(simulation_model);

	return std::unique_ptr<BridgeSimulationContext>(new BridgeSimulationContext(std::move(bridge_window), std::move(bridge_controller)));
}

template <class T> void insert_vector_to_vector(std::vector<T>& dest, std::vector<T>& src) {
	dest.insert(dest.end(), src.begin(), src.end());
}

typedef std::vector<std::shared_ptr<BridgeSimulationContext>> simulations_vector;

void add_simulation(ApplicationContext& context, const std::string& controller_type, const std::string& bridge_model, const std::string& simulation_type) {
	std::vector<std::shared_ptr<BridgeSimulationContext>>& simulations = context.get_bridge_simulation_context();



	simulations.push_back(create_simulation_context(context, controller_type, bridge_model, simulation_type));
}

void all_speeds(ApplicationContext& context, const std::string& controller_type, const std::string& bridge_model) {
	add_simulation(context, controller_type, bridge_model, SampleDataModel::OPTIMAL_WITH_DELAY_SIMULATION);
	add_simulation(context, controller_type, bridge_model, SampleDataModel::TEN_TIME_FACTOR_SIMULATION);
	add_simulation(context, controller_type, bridge_model, SampleDataModel::HUNDRED_TIME_FACTOR_SIMULATION);
}

void all_matrix_all_speeds(ApplicationContext& context, const std::string& bridge_model) {
	all_speeds(context, BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER, bridge_model);
	all_speeds(context, BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER, bridge_model);
}

void all_controllers_all_speeds(ApplicationContext& context, const std::string& bridge_model) {
	all_speeds(context, BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER, bridge_model);
	all_speeds(context, BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER, bridge_model);
	all_speeds(context, BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER, bridge_model);
}

void all_controlers(ApplicationContext& context, const std::string& bridge_model, const std::string& simulation_type) {
	add_simulation(context, BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER ,bridge_model, simulation_type);
	add_simulation(context, BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER, bridge_model, simulation_type);
	add_simulation(context, BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER, bridge_model, simulation_type);
}

void demo_simulations(ApplicationContext& context) {
	add_simulation(context, BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::LINE_DIAGONAL, SampleDataModel::HUNDRED_TIME_FACTOR_SIMULATION);
	add_simulation(context, BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::LINE_DIAGONAL, SampleDataModel::HUNDRED_TIME_FACTOR_SIMULATION);

	add_simulation(context, BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::LINE_DIAGONAL, SampleDataModel::TEN_TIME_FACTOR_SIMULATION);
	add_simulation(context, BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::LINE_DIAGONAL, SampleDataModel::TEN_TIME_FACTOR_SIMULATION);
}


void create_simulations(ApplicationContext& context) {

	demo_simulations(context);

	//all_controllers_all_speeds(simulations, SampleDataModel::TRIANGLE_GRID);
	//all_matrix_all_speeds(simulations, SampleDataModel::TRIANGLE_GRID);

	//add_simulation(simulations, BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::TRIANGLE_GRID, SampleDataModel::HUNDRED_TIME_FACTOR_SIMULATION);
	//add_simulation(simulations, BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER, SampleDataModel::TRIANGLE_GRID, SampleDataModel::HUNDRED_TIME_FACTOR_SIMULATION);
	//add_simulation(simulations, BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::TRIANGLE_GRID, SampleDataModel::HUNDRED_TIME_FACTOR_SIMULATION);

	//add_simulation(simulations, BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::ROPE_BRIDGE, SampleDataModel::OPTIMAL_WITH_DELAY_SIMULATION);
	//add_simulation(simulations, BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::ROPE_BRIDGE, SampleDataModel::OPTIMAL_WITH_DELAY_SIMULATION);

	//add_simulation(simulations, BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::TRIANGLE_GRID, SampleDataModel::OPTIMAL_WITH_DELAY_SIMULATION);
	//add_simulation(simulations, BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::TRIANGLE_GRID, SampleDataModel::OPTIMAL_WITH_DELAY_SIMULATION);

	//add_simulation(simulations, BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::LINE_DIAGONAL, SampleDataModel::TEN_TIME_FACTOR_SIMULATION);
	//add_simulation(simulations, BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::LINE_DIAGONAL, SampleDataModel::TEN_TIME_FACTOR_SIMULATION);

	//all_speeds(simulations, BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::LINE_DIAGONAL);
	//all_speeds(simulations,  BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::LINE_DIAGONAL);
	//all_matrix_all_speeds(simulations, SampleDataModel::LINE_DIAGONAL);

	//add_simulation(simulations, BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER, SampleDataModel::PANDULUM_BRIDGE, SampleDataModel::OPTIMAL_WITH_DELAY_SIMULATION);
	//all_controlers(simulations, SampleDataModel::HEART_BRIDGE, SampleDataModel::HUNDRED_TIME_FACTOR_SIMULATION);
}

void layout_windows(ApplicationContext& context) {
	std::vector<std::shared_ptr<BridgeSimulationContext>>& simulations = context.get_bridge_simulation_context();

	if (simulations.size() == 0) return;

	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	int work_area_width = mode->width - 200;
	int work_area_height = mode->height - 200;

	int columns = (int)sqrt(simulations.size());

	if (columns*columns != simulations.size()) {
		columns++;
	}

	int rows = simulations.size() / columns;
	if (simulations.size() != rows * columns) {
		rows++;
	}

	int windows_width = work_area_width / columns;
	int windows_height = work_area_height / rows;

	for (int i = 0; i < simulations.size(); i++) {
		auto& window = simulations.at(i)->get_window();
		int column = i % columns;
		int row = i / columns;

		window.set_position({ column * windows_width + 50, row * windows_height + 50 });
		window.set_size({ windows_width - 20, windows_height - 50});
	}
}

void start_simulation(ApplicationContext& context) {
	std::vector<std::shared_ptr<BridgeSimulationContext>>& simulations = context.get_bridge_simulation_context();

	for (auto& simulation : simulations) {
		simulation->init();
	}

	auto prev = std::chrono::high_resolution_clock::now();

	while (simulations.size() > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		auto current = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(current - prev);

		if (elapsed_time > std::chrono::seconds(1)) {
			elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::seconds(1));
		}

		elapsed_time = std::min(elapsed_time, std::chrono::microseconds(10000));

		prev = current;
		for (int i = 0; i < simulations.size(); i++) {
			auto& simulation = simulations.at(i);

			if (!simulation->update(elapsed_time)) {
				return;
			}
		}
	}
}



int main(int argc, char* argv[]) {

	ApplicationContext context;

	ApplicationConfiguration& application_configuration = *context.get_application_configuration();

	if (application_configuration.parse_arguments(argc, argv)) {
		return 1;
	}

	if (application_configuration.get_run_test_flag()) {
		try {
			::testing::InitGoogleTest(&argc, argv);
			RUN_ALL_TESTS();
		}
		catch (...) {
			fprintf(stderr, "Exception during unit test run\n");
		}
	}

	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	create_simulations(context);
	layout_windows(context);
	start_simulation(context);

	glfwTerminate();
	
	return 0;
}
