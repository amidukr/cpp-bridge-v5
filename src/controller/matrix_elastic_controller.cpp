#include "controller/matrix_elastic_controller.h"

#include "model/bridge/junction.h"
#include "service/bridge_matrix_service.h"

void MatrixElasticController::updateJunctionsVelocity(double elapsed_time) {
	BridgeModel& bridge_model = this->get_bridge_model();
	SimulationModel& simulation_model = this->get_simulation_model();

	std::unique_ptr<MatrixEquation> matrix_equation = BridgeMatrixService::create_bridge_equation(bridge_model, simulation_model, elapsed_time);

	std::vector<Junction*>& soft_junctions = *matrix_equation->soft_junctions.get();

	for (int i = 0; i < soft_junctions.size(); i++) {
		Junction& junction = *soft_junctions.at(i);

		Eigen::Vector2d dv = matrix_equation->get_junction_dv(i);

		junction.set_velocity(junction.get_velocity() + dv);
	}
}