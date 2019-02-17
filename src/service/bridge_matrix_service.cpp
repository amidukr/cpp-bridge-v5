#include "service/bridge_matrix_service.h"
#include "model/bridge_model.h"
#include <vector>
#include <model/simulation_model.h>
#include <utils/matrix_utils.h>
#include <math.h>


Eigen::Vector2d MatrixEquation::get_junction_dv(int i) {
	return 	Eigen::Vector2d(this->roots(this->col_dv.x_index(i)), this->roots(this->col_dv.y_index(i)));
}

MatrixEquation::MatrixEquation(VectorIndex col_dv) 
	: col_dv(col_dv)
{}

std::unique_ptr<MatrixEquation> BridgeMatrixService::create_bridge_equation(BridgeModel& bridge_model, SimulationModel& simulation_model, double elapsedTime) {
	std::unique_ptr<std::vector<Junction*>> soft_junctions(new std::vector<Junction*>());
	std::vector<int> soft_junctions_index;

	for (int i = 0; i < bridge_model.get_junctions_len(); i++) {
		Junction& junction = bridge_model.get_junction(i);

		if (junction.is_hard()) {
			soft_junctions_index.push_back(-1);
			continue;
		}
		else {
			soft_junctions_index.push_back(soft_junctions->size());
			soft_junctions->push_back(&junction);
		}
	}

	std::vector<Girder*> soft_girders;
	std::vector<int> soft_girder_index;

	for (int i = 0; i < bridge_model.get_girder_len(); i++) {
		Girder& girder = bridge_model.get_girder(i);
		Junction& l = bridge_model.get_junction(girder.get_junction1_id());
		Junction& r = bridge_model.get_junction(girder.get_junction2_id());

		if (l.is_hard() && r.is_hard()) {
			soft_girder_index.push_back(-1);
			continue;
		}
		else {
			soft_girder_index.push_back(soft_girders.size());
			soft_girders.push_back(&girder);
		}
	}

	VectorIndex col_dv(soft_junctions->size());
	ScalarIndex col_fxy(col_dv, soft_girders.size());
	
	VectorIndex row_f(soft_junctions->size());
	ScalarIndex row_dvr(row_f, soft_girders.size());
	

	int n = row_dvr.get_end_offset();

	std::unique_ptr<MatrixEquation> matrix_equation(new MatrixEquation(col_dv));

	matrix_equation->left = Eigen::MatrixXd(n, n);
	matrix_equation->right = Eigen::VectorXd(n);

	matrix_equation->left.setZero();
	matrix_equation->right.setZero();

	for (int i = 0; i < soft_junctions->size(); i++) {
		Junction& junction = *soft_junctions->at(i);

		std::vector<Girder*> girders = bridge_model.get_junction_girders(junction);

		matrix_equation->left(row_f.x_index(i), col_dv.x_index(i)) = 1;
		matrix_equation->left(row_f.y_index(i), col_dv.y_index(i)) = 1;

		//matrix_equation->left(row_f.x_index(i), col_dv.x_index(i)) = 1;
		//matrix_equation->left(row_f.y_index(i), col_dv.y_index(i)) = 1;

		matrix_equation->right[row_f.x_index(i)] = simulation_model.get_gravity()[0];
		matrix_equation->right[row_f.y_index(i)] = simulation_model.get_gravity()[1];
	}

	for (int i = 0; i < soft_girders.size(); i++) {
		Girder& girder = *soft_girders.at(i);

		Junction& j1 = bridge_model.get_junction(girder.get_junction1_id());
		Junction& j2 = bridge_model.get_junction(girder.get_junction2_id());

		Eigen::Vector2d r12 = j2.get_coordinate() - j1.get_coordinate();
		Eigen::Vector2d norm_r12 = r12;

		norm_r12.normalize();

		if (!j1.is_hard()) {
			int soft_index = soft_junctions_index.at(j1.get_index());

			matrix_equation->left(row_f.x_index(soft_index), col_fxy.index(i)) = norm_r12[0];
			matrix_equation->left(row_f.y_index(soft_index), col_fxy.index(i)) = norm_r12[1];

			matrix_equation->left(row_dvr.index(i), col_dv.x_index(soft_index)) = norm_r12[0];
			matrix_equation->left(row_dvr.index(i), col_dv.y_index(soft_index)) = norm_r12[1];

			matrix_equation->right(row_dvr.index(i)) -= norm_r12.dot(j1.get_velocity());
		}

		if (!j2.is_hard()) {
			int soft_index = soft_junctions_index.at(j2.get_index());

			matrix_equation->left(row_f.x_index(soft_index), col_fxy.index(i)) = -norm_r12[0];
			matrix_equation->left(row_f.y_index(soft_index), col_fxy.index(i)) = -norm_r12[1];

			matrix_equation->left(row_dvr.index(i), col_dv.x_index(soft_index)) = -norm_r12[0];
			matrix_equation->left(row_dvr.index(i), col_dv.y_index(soft_index)) = -norm_r12[1];

			matrix_equation->right(row_dvr.index(i)) += norm_r12.dot(j2.get_velocity());
		}

		double expected_len_change = r12.norm() - girder.get_original_size();

		matrix_equation->right(row_dvr.index(i)) += expected_len_change / elapsedTime;
	}

	if (n != 0) {
		matrix_equation->roots = matrix_equation->left.colPivHouseholderQr().solve(matrix_equation->right);
	}

	matrix_equation->soft_junctions = std::move(soft_junctions);

	return matrix_equation;
}
