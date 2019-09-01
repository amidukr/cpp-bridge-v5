#include "controller/simulation/elastic/elastic_controller.h"
#include "model/bridge_model.h"
#include "model/simulation_model.h"

void ElasticController::updateJunctionsVelocity(double elapsed_time) {
	BridgeModel& bridge_model = this->get_bridge_model();
	int junctions_len = bridge_model.get_junctions_len();

	const Eigen::Vector2d G = this->get_simulation_model().get_gravity();

	for (int i = 0; i < junctions_len; i++) {
		Junction& junction = bridge_model.get_junction(i);
		if (!junction.is_fixed()) {
			junction.set_velocity(junction.get_velocity() + G);
		}
	}
}
