#include "service/bridge_matrix_service.h"
#include "model/bridge_model.h"
#include <vector>
#include <model/simulation_model.h>
#include <utils/matrix_utils.h>
#include <math.h>

std::unique_ptr<MatrixEquation> BridgeMatrixService::create_floating_junctions_equation(BridgeModel& bridge_model, SimulationModel& simulation_model, double elapsedTime) {

	const std::vector<Junction*>& floating_junctions = bridge_model.get_floating_junctions();
	const std::vector<Girder*>& floating_girders = bridge_model.get_floating_girders();

	VectorIndex col_dv(floating_junctions.size());
	ScalarIndex col_fxy(col_dv, floating_girders.size());
	
	VectorIndex row_f(floating_junctions.size());
	ScalarIndex row_dvr(row_f, floating_girders.size());
	

	int n = row_dvr.get_end_offset();

	std::unique_ptr<MatrixEquation> matrix_equation{ new MatrixEquation(n, col_dv.to_scalar_index()) };

	Eigen::MatrixXd& left = matrix_equation->get_left();
	Eigen::VectorXd& right = matrix_equation->get_right();

	for (int i = 0; i < floating_junctions.size(); i++) {
		Junction& junction = *floating_junctions.at(i);

		std::vector<Girder*> girders = bridge_model.get_junction_girders(junction);

		left(row_f.x_index(i), col_dv.x_index(i)) = 1;
		left(row_f.y_index(i), col_dv.y_index(i)) = 1;

		right[row_f.x_index(i)] = simulation_model.get_gravity()[0];
		right[row_f.y_index(i)] = simulation_model.get_gravity()[1];
	}

	for (int i = 0; i < floating_girders.size(); i++) {
		Girder& girder = *floating_girders.at(i);

		Junction& j1 = bridge_model.get_junction(girder.get_junction1_id());
		Junction& j2 = bridge_model.get_junction(girder.get_junction2_id());

		Eigen::Vector2d r12 = j2.get_coordinate() - j1.get_coordinate();
		Eigen::Vector2d norm_r12 = r12;

		norm_r12.normalize();

		if (!j1.is_fixed()) {
			int floating_index = j1.get_floating_index();

			left(row_f.x_index(floating_index), col_fxy.index(i)) = norm_r12[0];
			left(row_f.y_index(floating_index), col_fxy.index(i)) = norm_r12[1];

			left(row_dvr.index(i), col_dv.x_index(floating_index)) = norm_r12[0];
			left(row_dvr.index(i), col_dv.y_index(floating_index)) = norm_r12[1];

			right(row_dvr.index(i)) -= norm_r12.dot(j1.get_velocity());
		}

		if (!j2.is_fixed()) {
			int floating_index = j2.get_floating_index();

			left(row_f.x_index(floating_index), col_fxy.index(i)) = -norm_r12[0];
			left(row_f.y_index(floating_index), col_fxy.index(i)) = -norm_r12[1];

			left(row_dvr.index(i), col_dv.x_index(floating_index)) = -norm_r12[0];
			left(row_dvr.index(i), col_dv.y_index(floating_index)) = -norm_r12[1];

			right(row_dvr.index(i)) += norm_r12.dot(j2.get_velocity());
		}

		double expected_len_change = r12.norm() - girder.get_original_size();

		right(row_dvr.index(i)) += expected_len_change / elapsedTime;
	}

	matrix_equation->solve();

	return matrix_equation;
}
