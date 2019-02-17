#include<gtest/gtest.h>
#include "model/bridge_model.h"

TEST(BridgeModelTest, test_bridge_model) {
	BridgeModel bridge;

	Junction& junction1 = bridge.add_junction(25.0, 30.0);
	Junction& junction2 = bridge.add_junction(80.0, 90.0);
	Junction& junction3 = bridge.add_junction(45.0, 15.0);

	Girder& girder1 = bridge.add_girder(junction1, junction2);
	Girder& girder2 = bridge.add_girder(junction2, junction3);

	ASSERT_EQ(junction1.get_index(), 0);
	ASSERT_EQ(junction2.get_index(), 1);
	ASSERT_EQ(junction3.get_index(), 2);

	ASSERT_EQ(girder1.get_index(), 0);
	ASSERT_EQ(girder2.get_index(), 1);

	ASSERT_EQ(girder1.get_junction1_id(), 0);
	ASSERT_EQ(girder1.get_junction2_id(), 1);


	ASSERT_EQ(girder2.get_junction1_id(), 1);
	ASSERT_EQ(girder2.get_junction2_id(), 2);

	ASSERT_EQ(bridge.get_junctions_len(), 3);
	ASSERT_EQ(bridge.get_junction(0).get_index(), 0);
	ASSERT_EQ(bridge.get_junction(1).get_index(), 1);
	ASSERT_EQ(bridge.get_junction(2).get_index(), 2);


	ASSERT_EQ(bridge.get_girder_len(), 2);
	ASSERT_EQ(bridge.get_girder(0).get_index(), 0);
	ASSERT_EQ(bridge.get_girder(1).get_index(), 1);
}

TEST(BridgeModelTest, test_junction_exception) {
	BridgeModel bridge;

	Junction& junction1 = bridge.add_junction(25.0, 30.0);
	Junction& junction2 = bridge.add_junction(80.0, 90.0);
	Junction& junction3 = bridge.add_junction(45.0, 15.0);

	try {
		bridge.get_junction(3);
		FAIL() << "out of bound should be thrown";
	} catch (std::out_of_range& e) {
		//exception is expected by test case
	}
}

TEST(BridgeModelTest, test_junction_model) {
	BridgeModel bridge;

	Junction& junction1 = bridge.add_junction(25.0, 30.0);
	Junction& junction2 = bridge.add_fixed_junction(80.0, 19.0);

	ASSERT_EQ(junction1.get_x(), 25.0);
	ASSERT_EQ(junction1.get_y(), 30.0);
	ASSERT_EQ(junction1.get_coordinate()[0], 25.0);
	ASSERT_EQ(junction1.get_coordinate()[1], 30.0);
	ASSERT_EQ(junction1.is_fixed(), false);

	ASSERT_EQ(junction2.get_x(), 80.0);
	ASSERT_EQ(junction2.get_y(), 19.0);
	ASSERT_EQ(junction2.get_coordinate()[0], 80.0);
	ASSERT_EQ(junction2.get_coordinate()[1], 19.0);
	ASSERT_EQ(junction2.is_fixed(), true);
}



TEST(BridgeModelTest, test_girder_exception) {
	BridgeModel bridge;

	Junction& junction1 = bridge.add_junction(25.0, 30.0);
	Junction& junction2 = bridge.add_junction(80.0, 90.0);
	Junction& junction3 = bridge.add_junction(45.0, 15.0);

	Girder& girder1 = bridge.add_girder(junction1, junction2);
	Girder& girder2 = bridge.add_girder(junction2, junction3);

	try {
		bridge.get_girder(2);
		FAIL() << "out of bound should be thrown";
	}
	catch (std::out_of_range& e) {
		//exception is expected by test case
	}
}

TEST(BridgeModelTest, test_brider_model_bounds) {
	BridgeModel bridge;

	Junction& junction1 = bridge.add_junction(25.0, 30.0);
	Junction& junction2 = bridge.add_junction(80.0, 90.0);
	Junction& junction3 = bridge.add_junction(45.0, 15.0);

	std::array<double, 4> bounds = bridge.get_bounds();

	ASSERT_EQ(bounds[0], 25.0);
	ASSERT_EQ(bounds[1], 15.0);
	ASSERT_EQ(bounds[2], 80.0);
	ASSERT_EQ(bounds[3], 90.0);
}

TEST(BridgeModelTest, test_brider_empty_model_bounds) {
	BridgeModel bridge;

	std::array<double, 4> bounds = bridge.get_bounds();

	ASSERT_EQ(bounds[0], 0);
	ASSERT_EQ(bounds[1], 0);
	ASSERT_EQ(bounds[2], 0);
	ASSERT_EQ(bounds[3], 0);
}
