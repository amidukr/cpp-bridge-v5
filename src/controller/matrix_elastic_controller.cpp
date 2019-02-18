#include "controller/matrix_elastic_controller.h"

#include "model/bridge_model.h"
#include "model/bridge/junction.h"
#include "service/bridge_matrix_service.h"

void MatrixElasticController::updateJunctionsVelocity(double elapsed_time) {
	BridgeModel& bridge_model = this->get_bridge_model();
	SimulationModel& simulation_model = this->get_simulation_model();

	std::unique_ptr<MatrixEquation> matrix_equation = BridgeMatrixService::create_floating_junctions_equation(bridge_model, simulation_model, elapsed_time);

	const std::vector<Junction*>& floating_junctions = bridge_model.get_floating_junctions();

	for (int i = 0; i < floating_junctions.size(); i++) {
		Junction& junction = *floating_junctions.at(i);

		Eigen::Vector2d dv = matrix_equation->get_indexed_root_vector(i);

		junction.set_velocity(junction.get_velocity() + dv);
	}
}
