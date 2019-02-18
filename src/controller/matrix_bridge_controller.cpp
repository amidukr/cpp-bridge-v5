#include "controller/matrix_bridge_controller.h"

#include <chrono>
#include <thread>

#include "model/bridge_model.h"
#include "model/simulation_model.h"
#include "controller/arguments/controller_action.h"
#include "service/bridge_matrix_service.h"

#include <iostream>

void MatrixBridgeController::update(ControllerAction& action) {
	BridgeModel& bridge_model = this->get_bridge_model();
	SimulationModel& simulation_model = this->get_simulation_model();

	double elapsed_time = action.get_elapsed_time_seconds() * simulation_model.get_time_factor();

	const Eigen::Vector2d G = simulation_model.get_gravity();
	double Q = simulation_model.get_dumping_ratio();
	
	int junctions_len = bridge_model.get_junctions_len();

	std::unique_ptr<MatrixEquation> matrix_equation = BridgeMatrixService::create_floating_junctions_equation(bridge_model, simulation_model, elapsed_time);

	const std::vector<Junction*>& floating_junctions = bridge_model.get_floating_junctions();

	for (int i = 0; i < floating_junctions.size(); i++) {
		Junction& junction = *floating_junctions.at(i);

		Eigen::Vector2d dv = matrix_equation->get_indexed_root_vector(i);

		junction.set_velocity(junction.get_velocity() + dv);
	}

	for (int i = 0; i < junctions_len; i++) {
		Junction& junction = bridge_model.get_junction(i);
		junction.set_coordinate(junction.get_coordinate() + junction.get_velocity() * elapsed_time);
	}

	for (int i = 0; i < junctions_len; i++) {
		Junction& junction = bridge_model.get_junction(i);

		junction.set_velocity(junction.get_velocity() * Q);
	}
}
