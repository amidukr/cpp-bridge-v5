#include<gtest/gtest.h>

#include "utils/compare_matrices_utils.h"

#include "service/bridge_matrix_service.h"
#include "model/bridge_model.h"
#include "model/simulation_model.h"





TEST(BridgeMatrixService, test_pendulum) {
	BridgeModel bridge_model;
	SimulationModel simulation_model;

	simulation_model.set_gravity(Eigen::Vector2d(20, 30));

	Junction& fixed = bridge_model.add_fixed_junction(20, 10);
	Junction& floating = bridge_model.add_junction(24, 7);

	bridge_model.add_girder(fixed, floating);

	std::unique_ptr<MatrixEquation> matrix_equation = BridgeMatrixService::create_floating_junctions_equation(bridge_model, simulation_model, 100);

	Eigen::MatrixXd matrix_expected(3, 3);
	matrix_expected <<
		//   V1X       V1Y         F12
		       1,        0,   -4.0 / 5,
		       0,        1,    3.0 / 5,
		-4.0 / 5,  3.0 / 5,          0;


	Eigen::VectorXd right_side_exptected(3);

	right_side_exptected << 20, 30, 0;
	
	ASSERT_TRUE(compare_matrices(matrix_equation->get_left(), matrix_expected));
	ASSERT_TRUE(compare_matrices(matrix_equation->get_right(), right_side_exptected));
	ASSERT_TRUE(compare_matrices(matrix_equation->get_indexed_root_vector(0), Eigen::Vector2d(36 * 3.0 / 5 , 36 * 4.0 / 5)));
}

TEST(BridgeMatrixService, test_free_fall_junction) {
	BridgeModel bridge_model;
	SimulationModel simulation_model;

	simulation_model.set_gravity(Eigen::Vector2d(20, 30));

	bridge_model.add_fixed_junction(1, 2);
	bridge_model.add_junction(3, 4);
	bridge_model.add_junction(5, 6);

	std::unique_ptr<MatrixEquation> matrix_equation = BridgeMatrixService::create_floating_junctions_equation(bridge_model, simulation_model, 100);

	Eigen::MatrixXd matrix_expected(4, 4);
	matrix_expected <<
		//dV1X dV1Y dV2X dV2Y
		    1,   0,   0,   0,
		    0,   1,   0,   0,
		    0,   0,   1,   0,
		    0,   0,   0,   1;

	Eigen::VectorXd right_side_exptected(4);

	right_side_exptected << 20, 30, 20, 30;

	ASSERT_TRUE(compare_matrices(matrix_equation->get_left(), matrix_expected));
	ASSERT_TRUE(compare_matrices(matrix_equation->get_right(), right_side_exptected));
	ASSERT_TRUE(compare_matrices(Eigen::Vector2d(20, 30), matrix_equation->get_indexed_root_vector(0)));
	ASSERT_TRUE(compare_matrices(Eigen::Vector2d(20, 30), matrix_equation->get_indexed_root_vector(1)));
}

TEST(BridgeMatrixService, test_free_fall_girder) {
	BridgeModel bridge_model;
	SimulationModel simulation_model;

	simulation_model.set_gravity(Eigen::Vector2d(20, 30));

	Junction& j1 =  bridge_model.add_junction(10, 20);
	Junction& j2 = bridge_model.add_junction(13, 24);

	bridge_model.add_girder(j1, j2);

	std::unique_ptr<MatrixEquation> matrix_equation = BridgeMatrixService::create_floating_junctions_equation(bridge_model, simulation_model, 100);

	Eigen::MatrixXd matrix_expected(5, 5);
	matrix_expected <<
		//  dV1X       dV1Y       dV2X       dV2Y      F12X
		       1,         0,         0,         0,    3.0/5, 
		       0,         1,         0,         0,    4.0/5, 
		       0,         0,         1,         0,   -3.0/5, 
		       0,         0,         0,         1,   -4.0/5, 
		 3.0 / 5,   4.0 / 5,  -3.0 / 5,  -4.0 / 5,        0;

	Eigen::VectorXd right_side_exptected(5);

	right_side_exptected << 20, 30, 20, 30, 0;

	ASSERT_TRUE(compare_matrices(matrix_equation->get_left(), matrix_expected));
	ASSERT_TRUE(compare_matrices(matrix_equation->get_right(), right_side_exptected));
	ASSERT_TRUE(compare_matrices(Eigen::Vector2d(20, 30), matrix_equation->get_indexed_root_vector(0)));
	ASSERT_TRUE(compare_matrices(Eigen::Vector2d(20, 30), matrix_equation->get_indexed_root_vector(1)));
}

TEST(BridgeMatrixService, test_fixed_junction) {
	BridgeModel bridge_model;
	SimulationModel simulation_model;

	simulation_model.set_gravity(Eigen::Vector2d(20, 30));

	Junction& j1 = bridge_model.add_fixed_junction(10, 20);
	Junction& j2 = bridge_model.add_fixed_junction(12, 24);

	bridge_model.add_girder(j1, j2);

	std::unique_ptr<MatrixEquation> matrix_equation = BridgeMatrixService::create_floating_junctions_equation(bridge_model, simulation_model, 100);

	Eigen::MatrixXd matrix_expected(0, 0);
	Eigen::VectorXd right_side_exptected;

	ASSERT_TRUE(compare_matrices(matrix_equation->get_left(), matrix_expected));
	ASSERT_TRUE(compare_matrices(matrix_equation->get_right(), right_side_exptected));
}

TEST(BridgeMatrixService, test_triangle) {
	BridgeModel bridge_model;
	SimulationModel simulation_model;

	simulation_model.set_gravity(Eigen::Vector2d(40, 50));

	Junction& j1 = bridge_model.add_fixed_junction(10, 20);
	Junction& j2 = bridge_model.add_junction(12, 16);
	Junction& j3 = bridge_model.add_junction(6, 17);

	bridge_model.add_girder(j1, j2);
	bridge_model.add_girder(j2, j3);
	bridge_model.add_girder(j3, j1);

	std::unique_ptr<MatrixEquation> matrix_equation = BridgeMatrixService::create_floating_junctions_equation(bridge_model, simulation_model, 15);

	Eigen::Vector2d r23 = Eigen::Vector2d(6 - 12, 17 - 16);
	r23.normalize();
	
	Eigen::MatrixXd matrix_expected(7, 7);
	matrix_expected <<
	//         dV2X               dV2Y      dV3X      dV3Y              F12       F23       F31
		          1,                 0,        0,        0,   -2.0/sqrt(20),   r23(0),        0,
		          0,                 1,        0,        0,    4.0/sqrt(20),   r23(1),        0,
		          0,                 0,        1,        0,               0,  -r23(0),    4.0/5,
		          0,                 0,        0,        1,               0,  -r23(1),    3.0/5,
     -2.0 / sqrt(20),   4.0 / sqrt(20),        0,        0,               0,        0,        0,
		      r23(0),           r23(1),  -r23(0),  -r23(1),               0,        0,        0,
		          0,                 0,    4.0/5,    3.0/5,               0,        0,        0;


	Eigen::VectorXd right_side_exptected(7);

	right_side_exptected << 40, 50, 40, 50, 0, 0, 0;

	Eigen::Vector2d expected_dv2 = 4 * Eigen::Vector2d(4,  2);
	Eigen::Vector2d expected_dv3 = 4 * Eigen::Vector2d(3, -4);

	ASSERT_TRUE(compare_matrices(matrix_equation->get_left(), matrix_expected));
	ASSERT_TRUE(compare_matrices(matrix_equation->get_right(), right_side_exptected));
	ASSERT_TRUE(compare_matrices(expected_dv2, matrix_equation->get_indexed_root_vector(0)));
	ASSERT_TRUE(compare_matrices(expected_dv3, matrix_equation->get_indexed_root_vector(1)));
}
