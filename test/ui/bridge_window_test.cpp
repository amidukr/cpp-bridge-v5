#include <gtest/gtest.h>

#include<memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ui/bridge_window.h"
#include "model/bridge_model.h"
#include "model/aplication_configuration.h"


class BridgeWindowTest : public ::testing::Test {

protected:
	void SetUp() {
		glewExperimental = true; // Needed for core profile
		glfwInit();
	}

	void TearDown() {
		glfwTerminate();
	}
};

TEST_F(BridgeWindowTest, bridge_window_test) {
	std::shared_ptr<BridgeModel> bridge_model{ new BridgeModel() };

	Junction& j1 = bridge_model->add_fixed_junction(0, 0);
	Junction& j2 = bridge_model->add_junction(1, 1);

	bridge_model->add_girder(j1, j2);


	BridgeWindow window{ bridge_model, std::shared_ptr<ApplicationConfiguration>(new ApplicationConfiguration()) };

	ASSERT_FALSE(window.is_active());
	ASSERT_TRUE(window.create());
	ASSERT_TRUE(window.is_active());
	ASSERT_TRUE(window.update());
	ASSERT_TRUE(window.close());
	ASSERT_FALSE(window.is_active());
	ASSERT_FALSE(window.update());
}