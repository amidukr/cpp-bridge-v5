#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<memory>

class BridgeModel;
class SimulationModel;
class ControllerAction;


class Controller {

	std::shared_ptr<BridgeModel> bridge_model;
	std::shared_ptr<SimulationModel> simulation_model;

public:
	Controller(std::shared_ptr<BridgeModel> bridge_model, std::shared_ptr<SimulationModel> simulation_model);

	void update(ControllerAction& controller_action);

private:
	// Disable copy constructor
	Controller(const Controller&); // no implementation 
	Controller& operator=(const Controller&); // no implementation
};

#endif // ! CONTROLLER_H

