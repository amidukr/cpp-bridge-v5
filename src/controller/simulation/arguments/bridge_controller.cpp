#include"controller/simulation/bridge_controller.h"

BridgeController::BridgeController() {
	
}

void BridgeController::set_bridge_model(std::shared_ptr<BridgeModel> bridge_model) {
	this->bridge_model = bridge_model;
}

BridgeModel& BridgeController::get_bridge_model() {
	return *this->bridge_model;
}

void BridgeController::set_simulation_model(std::shared_ptr<SimulationModel> simulation_model) {
	this->simulation_model = simulation_model;
}

SimulationModel& BridgeController::get_simulation_model() {
	return *this->simulation_model;
}
