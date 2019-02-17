#ifndef BRIDGE_SIMULATION_CONTEXT_H
#define BRIDGE_SIMULATION_CONTEXT_H

#include <memory>
#include <chrono>

class GLWindow;
class BridgeController;

class BridgeSimulationContext {

	std::unique_ptr<GLWindow> bridge_window;
	std::unique_ptr<BridgeController> bridge_controller;
public:
	BridgeSimulationContext(std::unique_ptr<GLWindow> bridge_window, std::unique_ptr<BridgeController> bridge_controller);

	GLWindow& get_window();

	bool init();
	bool update(const std::chrono::microseconds elapsed_time);

private:
	// Disable copy constructor
	BridgeSimulationContext(const BridgeSimulationContext&); // no implementation 
	BridgeSimulationContext& operator=(const BridgeSimulationContext&); // no implementation
};

#endif // BRIDGE_SIMULATION_CONTEXT_H

