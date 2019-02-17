#include "controller/base_elastic_bridge_controller.h"

#include <chrono>
#include <thread>

#include"model/bridge_model.h"
#include "model/simulation_model.h"
#include"controller/arguments/controller_action.h"


void BaseElasticBridgeController::update(ControllerAction& action) {

	BridgeModel& bridge_model = this->get_bridge_model();
	SimulationModel& simulation_model = this->get_simulation_model();

	double elapsed_time = action.get_elapsed_time_seconds() * simulation_model.get_time_factor();

	const Eigen::Vector2d G = simulation_model.get_gravity();
	const double K = simulation_model.get_spring_characteristic();
	double Q = simulation_model.get_dumping_ratio();
	
	int junctions_len = bridge_model.get_junctions_len();
	int girder_len = bridge_model.get_girder_len();

	std::vector<Eigen::Vector2d> old_pos(junctions_len);

	for (int i = 0; i < junctions_len; i++) {
		Junction& junction = bridge_model.get_junction(i);

		old_pos[i] = bridge_model.get_junction(i).get_coordinate();
	}

	this->updateJunctionsVelocity(elapsed_time);

	for (int i = 0; i < junctions_len; i++) {
		Junction& junction = bridge_model.get_junction(i);
		if (!junction.is_hard()) {
			bridge_model.get_junction(i).set_coordinate(junction.get_coordinate() + elapsed_time * junction.get_velocity() * Q);
		}
	}
	for (int n = 0; n < 5; n++) {

		for (int i = 0; i < girder_len; i++) {
			Girder& girder = bridge_model.get_girder(i);
			Junction& junction1 = bridge_model.get_junction(girder.get_junction1_id());
			Junction& junction2 = bridge_model.get_junction(girder.get_junction2_id());

			Eigen::Vector2d r12 = junction2.get_coordinate() - junction1.get_coordinate();
			Eigen::Vector2d r12_norm = r12;

			r12_norm.normalize();

			double force = (r12.norm() - girder.get_original_size()) * 0.5;

			if (!junction2.is_hard()) {
				junction2.set_coordinate(junction2.get_coordinate() - r12_norm * force);
			}

			if (!junction1.is_hard()) {
				junction1.set_coordinate(junction1.get_coordinate() + r12_norm * force);
			}
		}
	}
	
	for (int i = 0; i < junctions_len; i++) {
		Junction& junction = bridge_model.get_junction(i);

		if (!junction.is_hard()) {
			junction.set_velocity((junction.get_coordinate() - old_pos[i])/elapsed_time);
		}	
	}
}