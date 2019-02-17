#include "context/bridge_simulation_context.h"

#include "ui/bridge_window.h"
#include "controller/bridge_controller.h"
#include "controller/arguments/controller_action.h"

BridgeSimulationContext::BridgeSimulationContext(std::unique_ptr<GLWindow> bridge_window, std::unique_ptr<BridgeController> bridge_controller) {
	this->bridge_window = std::move(bridge_window);
	this->bridge_controller = std::move(bridge_controller);
}

GLWindow& BridgeSimulationContext::get_window() {
	return *this->bridge_window;
}

bool BridgeSimulationContext::init() {
	return this->bridge_window->create();
}

bool BridgeSimulationContext::update(std::chrono::microseconds elapsed_time) {
	if (!this->bridge_window->is_active()) {
		return false;
	}

	ControllerAction controller_action;
	controller_action.set_elapsed_time_micro(elapsed_time.count());

	this->bridge_controller->update(controller_action);

	return this->bridge_window->update();
}
