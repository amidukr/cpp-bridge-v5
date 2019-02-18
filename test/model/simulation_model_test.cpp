#include <gtest/gtest.h>

#include "model/simulation_model.h"

TEST(SimulationModelTest, test_properties) {
	SimulationModel simulation_model;

	simulation_model.set_dumping_ratio(1.0);
	simulation_model.set_gravity(Eigen::Vector2d(2, 3));
	simulation_model.set_iteration_delay(4);
	simulation_model.set_spring_characteristic(5);
	simulation_model.set_time_factor(6);

	ASSERT_EQ(1.0, simulation_model.get_dumping_ratio());
	ASSERT_EQ(Eigen::Vector2d(2, 3), simulation_model.get_gravity());
	ASSERT_EQ(4.0, simulation_model.get_iteration_delay());
	ASSERT_EQ(5.0, simulation_model.get_spring_characteristic());
	ASSERT_EQ(6.0, simulation_model.get_time_factor());
}
