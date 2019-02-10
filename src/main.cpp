#include <stdio.h>
#include <stdlib.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "model/bridge_model.h"
#include "ui/bridge_window.h"
#include "controller/arguments/controller_action.h"
#include "controller/controller.h"
#include "model/sample_data_model.h"


#ifdef RUN_GTEST_FROM_MAIN
#include <gtest/gtest.h>
#endif

class BridgeModel;
class SimulationModel;

void create_windows() {
	SampleDataModel sample_data_model;

	std::shared_ptr<BridgeModel> bridge_model = sample_data_model.load_bridge_model(SampleDataModel::LINE_DIAGONAL);
	std::shared_ptr<SimulationModel> simulation_model = sample_data_model.load_simulation_model(SampleDataModel::TEN_TIME_FACTOR_SIMULATION);

	BridgeWindow bridge_window(bridge_model);
	Controller controller(bridge_model, simulation_model);

	bridge_window.create();
	
	auto prev = std::chrono::high_resolution_clock::now();
	while (bridge_window.loop()) {
		ControllerAction action;
		
		auto current = std::chrono::high_resolution_clock::now();
		action.set_elapsed_time_micro(std::chrono::duration_cast<std::chrono::microseconds>(current - prev).count());

		controller.update(action);
		prev = current;
	}
}

int main(int argc, char* argv[]) {

	#ifdef RUN_GTEST_FROM_MAIN
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	#endif

	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	create_windows();

	glfwTerminate();
	
	return 0;
}
