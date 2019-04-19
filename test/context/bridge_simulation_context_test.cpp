#include <gtest/gtest.h>
#include <memory>
#include <chrono>

#include "ui/gl_window.h"
#include "controller/simulation/bridge_controller.h"
#include "controller/simulation/arguments/controller_action.h"

#include "context/bridge_simulation_context.h"

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include<ui/gl_window.h>

class BridgeSimulationContextTest : public ::testing::Test {

protected:
	void SetUp() {
		glewExperimental = true; // Needed for core profile
		glfwInit();
	}

	void TearDown() {
		glfwTerminate();
	}
};

class MockGLWindow : public GLWindow{
	
bool initialized = false;
bool drawn = false;

public:
	bool is_initialized() {
		return this->initialized;
	};

	bool is_drawn() {
		return this->drawn;
	};

	void init() override{
		initialized = true;
	};

	void draw() override{
		drawn = true;
	};
};

class MockBridgeController : public BridgeController{
	bool updated = false;
	long last_elapsed_time_micro;

public: 
	bool is_updated() {
		return this->updated;
	}

	long get_last_elapsed_time_micro() {
		return this->last_elapsed_time_micro;
	}
	
	void update(ControllerAction& controller_action) override {
		this->updated = true;
		this->last_elapsed_time_micro = controller_action.get_elapsed_time_micro();
	}
};

TEST_F(BridgeSimulationContextTest, test_context_init_draw_flow)
{
	MockGLWindow* mocked_window = new MockGLWindow();
	MockBridgeController* mocked_controller = new MockBridgeController();

	BridgeSimulationContext ctx{ std::unique_ptr<GLWindow>(mocked_window), std::unique_ptr<BridgeController>(mocked_controller) };

	ASSERT_EQ(mocked_window, &ctx.get_window());

	ASSERT_FALSE(mocked_window->is_drawn());
	ASSERT_FALSE(mocked_window->is_initialized());
	ASSERT_FALSE(mocked_window->is_active());
	ASSERT_FALSE(mocked_controller->is_updated());

	ctx.init();

	ASSERT_FALSE(mocked_window->is_drawn());
	ASSERT_TRUE(mocked_window->is_initialized());
	ASSERT_TRUE(mocked_window->is_active());
	ASSERT_FALSE(mocked_controller->is_updated());

	ctx.update(std::chrono::microseconds(500));

	ASSERT_TRUE(mocked_window->is_drawn());
	ASSERT_TRUE(mocked_window->is_initialized());
	ASSERT_TRUE(mocked_window->is_active());
	ASSERT_TRUE(mocked_controller->is_updated());
	ASSERT_EQ(mocked_controller->get_last_elapsed_time_micro(), 500);
}
