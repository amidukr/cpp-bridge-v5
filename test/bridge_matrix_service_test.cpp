#include<gtest/gtest.h>
#include "service/bridge_matrix_service.h"
#include "model/bridge_model.h"
#include "model/simulation_model.h"

#include <iostream>

bool compare_matrices(Eigen::MatrixXd& actual, Eigen::MatrixXd expected) {
	
	bool approx = actual.rows() == expected.rows() && actual.cols() == expected.cols();
	approx = approx && actual == expected;

	if (!approx) {
		std::cout << actual << std::endl << "doesn't equal to expected" << std::endl << expected << std::endl;

		if (actual.rows() == expected.rows() && actual.cols() == expected.cols()) {
			std::cout << "difference is following: " << std::endl << (expected - actual) << std::endl;
		}
		else {
			std::cout << "difference in matrix sizes" << std::endl;
		}
		
	}

	return approx;
}

TEST(BridgeMatrixService, test_pendulum) {
	BridgeModel bridge_model;
	SimulationModel simulation_model;

	simulation_model.set_gravity(Eigen::Vector2d(20, 30));

	Junction& hard = bridge_model.add_hard_junction(20, 10);
	Junction& soft = bridge_model.add_junction(24, 8);

	bridge_model.add_girder(hard, soft);

	std::unique_ptr<MatrixEquation> matrix_equation = BridgeMatrixService::create_bridge_equation(bridge_model, simulation_model, 100);

	std::cout << matrix_equation->roots << std::endl;

	Eigen::MatrixXd matrix_expected(6, 6);
	matrix_expected << 
	// F1X F1Y F12X F12Y dV1X  dV1Y
		1,   0,   1,   0,   0,    0,
		0,   1,   0,   1,   0,    0,
		0,   0,  -2,  -4,   0,    0,
		0,   0,   0,   0,   4,   -2,
		100, 0,   0,   0,  -1,    0,
		0, 100,   0,   0,   0,   -1;


	Eigen::VectorXd right_side_exptected(6);

	right_side_exptected << 20, 30, 0, 0, 0, 0;

	
	ASSERT_TRUE(compare_matrices(matrix_equation->left, matrix_expected));
	ASSERT_EQ(right_side_exptected, matrix_equation->right);
	ASSERT_EQ(matrix_equation->get_junction_dv(0), Eigen::Vector2d(-2, -4));
}

TEST(BridgeMatrixService, test_free_fall_junction) {
	BridgeModel bridge_model;
	SimulationModel simulation_model;

	simulation_model.set_gravity(Eigen::Vector2d(20, 30));

	bridge_model.add_hard_junction(1, 2);
	bridge_model.add_junction(3, 4);
	bridge_model.add_junction(5, 6);

	std::unique_ptr<MatrixEquation> matrix_equation = BridgeMatrixService::create_bridge_equation(bridge_model, simulation_model, 100);

	Eigen::MatrixXd matrix_expected(8, 8);
	matrix_expected <<
		//F1X  F1Y  F2X  F2Y dV1X dV1Y dV2X dV2Y
		    1,   0,   0,   0,   0,   0,   0,   0,
		    0,   1,   0,   0,   0,   0,   0,   0,
		    0,   0,   1,   0,   0,   0,   0,   0,
		    0,   0,   0,   1,   0,   0,   0,   0,
		  100,   0,   0,   0,  -1,   0,   0,   0,
		    0, 100,   0,   0,   0,  -1,   0,   0,
		    0,   0, 100,   0,   0,   0,  -1,   0,
		    0,   0,   0, 100,   0,   0,   0,  -1;
		

	Eigen::VectorXd right_side_exptected(8);

	right_side_exptected << 20, 30, 20, 30, 0, 0, 0, 0;

	ASSERT_TRUE(compare_matrices(matrix_equation->left, matrix_expected));
	ASSERT_EQ(right_side_exptected, matrix_equation->right);
}

TEST(BridgeMatrixService, test_free_fall_girder) {
	BridgeModel bridge_model;
	SimulationModel simulation_model;

	simulation_model.set_gravity(Eigen::Vector2d(20, 30));

	Junction& j1 =  bridge_model.add_junction(10, 20);
	Junction& j2 = bridge_model.add_junction(12, 24);

	bridge_model.add_girder(j1, j2);

	std::unique_ptr<MatrixEquation> matrix_equation = BridgeMatrixService::create_bridge_equation(bridge_model, simulation_model, 100);

	Eigen::MatrixXd matrix_expected(10, 10);
	matrix_expected <<
		//F1X  F1Y  F2X   F2Y  F12X  F12Y  dV1X  dV1Y  dV2X  dV2Y
		    1,   0,   0,    0,   -1,   0,     0,    0,    0,    0,
		    0,   1,   0,    0,    0,  -1,     0,    0,    0,    0,
		    0,   0,   1,    0,    1,   0,     0,    0,    0,    0,
		    0,   0,   0,    1,    0,   1,     0,    0,    0,    0,
		    0,   0,   0,    0,    4,  -2,     0,    0,    0,    0,
		    0,   0,   0,    0,    0,   0,     2,    4,    2,    4,
		  100,   0,   0,    0,    0,   0,    -1,    0,    0,    0,
		    0, 100,   0,    0,    0,   0,     0,   -1,    0,    0,
		    0,   0, 100,    0,    0,   0,     0,    0,   -1,    0,
		    0,   0,   0,  100,    0,   0,     0,    0,    0,   -1;

	Eigen::VectorXd right_side_exptected(10);

	right_side_exptected << 20, 30, 20, 30, 0, 0, 0, 0, 0, 0;

	ASSERT_TRUE(compare_matrices(matrix_equation->left, matrix_expected));
	ASSERT_EQ(right_side_exptected, matrix_equation->right);
}

TEST(BridgeMatrixService, test_hard_junction) {
	BridgeModel bridge_model;
	SimulationModel simulation_model;

	simulation_model.set_gravity(Eigen::Vector2d(20, 30));

	Junction& j1 = bridge_model.add_hard_junction(10, 20);
	Junction& j2 = bridge_model.add_hard_junction(12, 24);

	bridge_model.add_girder(j1, j2);

	std::unique_ptr<MatrixEquation> matrix_equation = BridgeMatrixService::create_bridge_equation(bridge_model, simulation_model, 100);

	Eigen::MatrixXd matrix_expected(0, 0);
	Eigen::VectorXd right_side_exptected;

	ASSERT_TRUE(compare_matrices(matrix_equation->left, matrix_expected));
	ASSERT_EQ(right_side_exptected, matrix_equation->right);
}

TEST(BridgeMatrixService, test_triangle) {
	BridgeModel bridge_model;
	SimulationModel simulation_model;

	simulation_model.set_gravity(Eigen::Vector2d(40, 50));

	Junction& j1 = bridge_model.add_hard_junction(10, 20);
	Junction& j2 = bridge_model.add_junction(12, 18);
	Junction& j3 = bridge_model.add_junction(7, 17);

	bridge_model.add_girder(j1, j2);
	bridge_model.add_girder(j2, j3);
	bridge_model.add_girder(j3, j1);

	std::unique_ptr<MatrixEquation> matrix_equation = BridgeMatrixService::create_bridge_equation(bridge_model, simulation_model, 15);

	Eigen::MatrixXd matrix_expected(14, 14);
	matrix_expected <<
		//F2X  F2Y  F3X  F3Y  F12X  F12Y  F23X  F23Y  F31X  F31Y  dV2X  dV2Y  dV3X  dV3Y
		    1,   0,   0,   0,    1,    0,  -1,    0,    0,    0,    0,    0,   0,     0,
		    0,   1,   0,   0,    0,    1,   0,   -1,    0,    0,    0,    0,   0,     0,
		    0,   0,   1,   0,    0,    0,   1,    0,   -1,    0,    0,    0,   0,     0,
		    0,   0,   0,   1,    0,    0,   0,    1,    0,   -1,    0,    0,   0,     0,
		    0,   0,   0,   0,   -2,   -2,   0,    0,    0,    0,    0,    0,   0,     0,
		    0,   0,   0,   0,    0,    0,  -1,    5,    0,    0,    0,    0,   0,     0,
		    0,   0,   0,   0,    0,    0,   0,    0,    3,   -3,    0,    0,   0,     0,
		    0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    2,   -2,   0,     0,
		    0,   0,   0,   0,    0,    0,   0,    0,    0,    0,   -5,   -1,  -5,    -1,
		    0,   0,   0,   0,    0,    0,   0,    0,    0,    0,    0,    0,   3,     3,
		   15,   0,   0,   0,    0,    0,   0,    0,    0,    0,   -1,    0,   0,     0,
		    0,  15,   0,   0,    0,    0,   0,    0,    0,    0,    0,   -1,   0,     0,
		    0,   0,  15,   0,    0,    0,   0,    0,    0,    0,    0,    0,  -1,     0,
		    0,   0,   0,  15,    0,    0,   0,    0,    0,    0,    0,    0,   0,    -1;


	Eigen::VectorXd right_side_exptected(14);

	right_side_exptected << 40, 50, 40, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;

	ASSERT_TRUE(compare_matrices(matrix_equation->left, matrix_expected));
	ASSERT_EQ(right_side_exptected, matrix_equation->right);
}
