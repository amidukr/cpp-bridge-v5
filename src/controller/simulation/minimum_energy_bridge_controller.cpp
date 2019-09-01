#include <controller/simulation/minimum_energy_bridge_controller.h>

#include"model/bridge_model.h"
#include "model/simulation_model.h"
#include"controller/simulation/arguments/controller_action.h"

void MinimumEnergyBridgeController::update(ControllerAction& action) {

	BridgeModel& bridge_model = this->get_bridge_model();
	SimulationModel& simulation_model = this->get_simulation_model();

	double elapsed_time = action.get_elapsed_time_seconds() * simulation_model.get_time_factor();

	const std::vector<Junction*>& junctions = bridge_model.get_floating_junctions();
	int junctions_len = junctions.size();

	std::vector<Eigen::Vector2d> old_pos(junctions_len);

	for (int i = 0; i < junctions_len; i++) {
		old_pos[i] = junctions.at(i)->get_coordinate();
	}

	KinematicBridgeController::update(action);

	const std::vector<Girder*>& girders = bridge_model.get_floating_girders();
	int girder_len = girders.size();
	for (int n = 0; n < 5; n++) {

		for (int i = 0; i < girder_len; i++) {
			Girder& girder = *girders.at(i);
			Junction& junction1 = bridge_model.get_junction(girder.get_junction1_id());
			Junction& junction2 = bridge_model.get_junction(girder.get_junction2_id());

			Eigen::Vector2d r12 = junction2.get_coordinate() - junction1.get_coordinate();
			Eigen::Vector2d r12_norm = r12;

			r12_norm.normalize();

			double force = (r12.norm() - girder.get_original_size()) * 0.5;

			if (!junction2.is_fixed()) {
				junction2.set_coordinate(junction2.get_coordinate() - r12_norm * force);
			}

			if (!junction1.is_fixed()) {
				junction1.set_coordinate(junction1.get_coordinate() + r12_norm * force);
			}
		}
	}
	
	for (int i = 0; i < junctions_len; i++) {
		Junction& junction = *junctions.at(i);
		junction.set_velocity((junction.get_coordinate() - old_pos[i]) / elapsed_time);
	}
}
