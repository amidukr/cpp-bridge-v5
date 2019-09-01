#include <controller/simulation/elastic/elastic_controller.h>
#include <controller/simulation/matrix/matrix_elastic_controller.h>
#include "controller/simulation/matrix/matrix_controller.h"

#include "utils/compare_matrices_utils.h"

#include "model/bridge_model.h"
#include "model/simulation_model.h"
#include "model/simulation_model.h"

#include "controller/simulation/arguments/controller_action.h"

#include <gtest/gtest.h>

std::shared_ptr<BridgeModel> create_free_fall_bridge_model() {
	std::shared_ptr<BridgeModel> bridge_model{ new BridgeModel{} };

	bridge_model->add_junction(0, 0);

	return bridge_model;
}

std::shared_ptr<SimulationModel> create_simulation_model() {
	std::shared_ptr<SimulationModel> simulation_model { new SimulationModel() };

	simulation_model->set_time_factor(1);
	simulation_model->set_dumping_ratio(1.0);
	simulation_model->set_gravity(Eigen::Vector2d(0, -1));

	return simulation_model;
}

TEST(ControllerLogicTest, free_fall_test) {
	ElasticController elastic_controller;
	MatrixElasticController matrix_elastic_controller;
	MatrixController matrix_bridge_controller;

	elastic_controller.set_bridge_model(create_free_fall_bridge_model());
	elastic_controller.set_simulation_model(create_simulation_model());

	matrix_elastic_controller.set_bridge_model(create_free_fall_bridge_model());
	matrix_elastic_controller.set_simulation_model(create_simulation_model());

	matrix_bridge_controller.set_bridge_model(create_free_fall_bridge_model());
	matrix_bridge_controller.set_simulation_model(create_simulation_model());

	ControllerAction action;
	action.set_elapsed_time_micro(1000000);

	elastic_controller.update(action);
	matrix_elastic_controller.update(action);
	matrix_bridge_controller.update(action);

	Junction& elastic_junction = elastic_controller.get_bridge_model().get_junction(0);
	Junction& matrix_elastic_junction = matrix_elastic_controller.get_bridge_model().get_junction(0);
	Junction& matrix_bridge_junction = matrix_bridge_controller.get_bridge_model().get_junction(0);

	ASSERT_TRUE(compare_matrices(elastic_junction.get_velocity(), Eigen::Vector2d(0, -1)));
	ASSERT_TRUE(compare_matrices(elastic_junction.get_coordinate(), Eigen::Vector2d(0, -1)));

	ASSERT_TRUE(compare_matrices(matrix_elastic_junction.get_velocity(), Eigen::Vector2d(0, -1)));
	ASSERT_TRUE(compare_matrices(matrix_elastic_junction.get_coordinate(), Eigen::Vector2d(0, -1)));

	ASSERT_TRUE(compare_matrices(matrix_bridge_junction.get_velocity(), Eigen::Vector2d(0, -1)));
	ASSERT_TRUE(compare_matrices(matrix_bridge_junction.get_coordinate(), Eigen::Vector2d(0, -1)));
}

TEST(ControllerLogicTest, test_elastic_pandulum) {
	std::shared_ptr<BridgeModel> bridge_model{ new BridgeModel{} };

	Junction& j1 = bridge_model->add_fixed_junction(0, 0);
	Junction& j2 = bridge_model->add_junction(1, -1);
	bridge_model->add_girder(j1, j2);

	ElasticController elastic_controller;

	elastic_controller.set_bridge_model(bridge_model);
	elastic_controller.set_simulation_model(create_simulation_model());

	ControllerAction action;
	action.set_elapsed_time_micro(1000000);

	elastic_controller.update(action);

	ASSERT_TRUE(compare_matrices(j1.get_velocity(), Eigen::Vector2d(0, 0)));
	ASSERT_TRUE(compare_matrices(j1.get_coordinate(), Eigen::Vector2d(0, 0)));

	ASSERT_TRUE(compare_matrices(j2.get_velocity(), Eigen::Vector2d(-0.356059, -0.287883)));
	ASSERT_TRUE(compare_matrices(j2.get_coordinate(), Eigen::Vector2d(0.643941, -1.28788)));
}
