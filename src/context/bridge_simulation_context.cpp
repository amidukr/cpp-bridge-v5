#include "context/bridge_simulation_context.h"

#include "ui/bridge_window.h"
#include "controller/controller.h"
#include "controller/arguments/controller_action.h"

BridgeSimulationContext::BridgeSimulationContext(std::unique_ptr<BridgeWindow> bridge_window, std::unique_ptr<Controller> controller) {
	this->bridge_window = std::move(bridge_window);
	this->controller = std::move(controller);
}

BridgeWindow& BridgeSimulationContext::get_window() {
	return *this->bridge_window;
}

bool BridgeSimulationContext::init() {
	return this->bridge_window->create();
}

bool BridgeSimulationContext::loop(std::chrono::microseconds elapsed_time) {
	if (!this->bridge_window->is_active()) {
		return false;
	}

	ControllerAction controller_action;
	controller_action.set_elapsed_time_micro(elapsed_time.count());

	this->controller->update(controller_action);

	return this->bridge_window->loop();
}
