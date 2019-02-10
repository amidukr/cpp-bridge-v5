#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <memory>
#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "model/bridge_model.h"
#include "ui/bridge_window.h"

#ifdef RUN_GTEST_FROM_MAIN
#include <gtest/gtest.h>
#endif

std::shared_ptr<BridgeModel> create_bridge() {
	std::shared_ptr<BridgeModel> bridge_model(new BridgeModel());

	Junction& junction_bl = bridge_model->add_junction(20, 20);
	Junction& junction_br = bridge_model->add_junction(40, 20);
	Junction& junction_tl = bridge_model->add_hard_junction(20, 40);
	Junction& junction_tr = bridge_model->add_junction(40, 40);

	bridge_model->add_girder(junction_bl, junction_br);
	bridge_model->add_girder(junction_br, junction_tr);
	bridge_model->add_girder(junction_tl, junction_tr);
	bridge_model->add_girder(junction_tl, junction_bl);

	return bridge_model;
}

void create_windows() {
	BridgeWindow bridge_window(create_bridge());

	bridge_window.create();

	while (bridge_window.loop());
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
