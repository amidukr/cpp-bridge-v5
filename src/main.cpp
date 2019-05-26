#include <stdio.h>
#include <stdlib.h>

#include <chrono>
#include <thread>
#include <cmath>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <gtest/gtest.h>

#include "context/application_context.h"
#include "context/bridge_simulation_context.h"
#include "factory/simulation_context_factory.h"
#include "controller/command_line_controller.h"
#include "model/global_vars.h"
#include "model/application_configuration.h"

#include "ui/gl_window.h"


int parse_arguments(ApplicationContext& context) {
	bool result = context.get_command_line_controller()->parse_arguments(context.get_argc(), context.get_argv());

	ApplicationConfiguration& application_configuration = *context.get_application_configuration();

	GlobalVars::set_headless_mode_flag(application_configuration.get_headless_mode_flag());

	return result;
}

int run_test(ApplicationContext& context) {
	try {
		int args = context.get_argc();
		::testing::InitGoogleTest(&args, context.get_argv());
		bool result = RUN_ALL_TESTS();
		
		if(!result) {
			printf("All tests executed succesfully\n");	
		}

		return result;

	}
	catch (...) {
		fprintf(stderr, "Exception during unit test run\n");
		return 1;
	}
}

int init_gl() {

	glewExperimental = true; // Needed for core profile
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	return 0;
}

int create_simulations(ApplicationContext& context) {
	std::vector<std::shared_ptr<BridgeSimulationContext>>& simulations = context.get_bridge_simulation_context();

	return context.get_simulation_context_factory()->build_simulation_context(simulations);
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

printf("argc = %d\n", argc);
for(int i=0;i<argc;i++) {
	printf("%s ",argv[i]);
}
printf("\n");


	ApplicationContext context{ argc, argv };

	if (parse_arguments(context)) return 1;
	
	ApplicationConfiguration& application_configuration = *context.get_application_configuration();
	
	if (application_configuration.get_run_test_flag()) {
		return run_test(context);
	}

	if (init_gl()) return 1;
	if (create_simulations(context)) return 1;
	layout_windows(context);
	start_simulation(context);

	glfwTerminate();
	
	return 0;
}
