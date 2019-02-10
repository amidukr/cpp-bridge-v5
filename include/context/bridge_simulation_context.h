#ifndef BRIDGE_SIMULATION_CONTEXT_H
#define BRIDGE_SIMULATION_CONTEXT_H

#include <memory>
#include <chrono>

class BridgeWindow;
class Controller;

class BridgeSimulationContext {

	std::unique_ptr<BridgeWindow> bridge_window;
	std::unique_ptr<Controller> controller;
public:
	BridgeSimulationContext(std::unique_ptr<BridgeWindow> bridge_window, std::unique_ptr<Controller> controller);

	BridgeWindow& get_window();

	bool init();
	bool loop(const std::chrono::microseconds elapsed_time);

private:
	// Disable copy constructor
	BridgeSimulationContext(const BridgeSimulationContext&); // no implementation 
	BridgeSimulationContext& operator=(const BridgeSimulationContext&); // no implementation
};

#endif // BRIDGE_SIMULATION_CONTEXT_H

