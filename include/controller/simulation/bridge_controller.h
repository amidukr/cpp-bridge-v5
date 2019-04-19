#ifndef BRIDGE_CONTROLLER_H
#define BRIDGE_CONTROLLER_H

#include<memory>

class BridgeModel;
class SimulationModel;
class ControllerAction;


class BridgeController {

	std::shared_ptr<BridgeModel> bridge_model;
	std::shared_ptr<SimulationModel> simulation_model;

protected:

public:
	BridgeController();

	void set_bridge_model(std::shared_ptr<BridgeModel> bridge_model);
	BridgeModel& get_bridge_model();

	void set_simulation_model(std::shared_ptr<SimulationModel> simulation_model);
	SimulationModel& get_simulation_model();
	

	virtual void update(ControllerAction& controller_action) = 0;

private:
	// Disable copy constructor
	BridgeController(const BridgeController&); // no implementation 
	BridgeController& operator=(const BridgeController&); // no implementation
};

#endif // ! CONTROLLER_H

