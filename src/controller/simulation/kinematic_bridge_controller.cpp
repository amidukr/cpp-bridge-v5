#include "controller/simulation/kinematic_bridge_controller.h"

#include "model/bridge_model.h"
#include "model/simulation_model.h"
#include "controller/simulation/arguments/controller_action.h"


void KinematicBridgeController::update(ControllerAction& action) {
	BridgeModel& bridge_model = this->get_bridge_model();
	SimulationModel& simulation_model = this->get_simulation_model();

	double elapsed_time = action.get_elapsed_time_seconds() * simulation_model.get_time_factor();

	double Q = simulation_model.get_dumping_ratio();

	int junctions_len = bridge_model.get_junctions_len();

	for (int i = 0; i < junctions_len; i++) {
		Junction& junction = bridge_model.get_junction(i);

		junction.set_velocity(junction.get_velocity() * Q);
	}

	this->updateJunctionsVelocity(elapsed_time);

	for (int i = 0; i < junctions_len; i++) {
		Junction& junction = bridge_model.get_junction(i);
		junction.set_coordinate(junction.get_coordinate() + junction.get_velocity() * elapsed_time);
	}
}
