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

TEST(BridgeModelTest, test_floating_index) {
	BridgeModel bridge;

	Junction& j1 = bridge.add_fixed_junction(0, 0);
	Junction& j2 = bridge.add_junction(0, 0);
	Junction& j3 = bridge.add_junction(0, 0);
	Junction& j4 = bridge.add_fixed_junction(0, 0);
	Junction& j5 = bridge.add_junction(0, 0);

	Girder& g1 = bridge.add_girder(j1, j4);
	Girder& g2 = bridge.add_girder(j1, j2);
	Girder& g3 = bridge.add_girder(j4, j1);
	Girder& g4 = bridge.add_girder(j2, j3);
	Girder& g5 = bridge.add_girder(j4, j3);

	ASSERT_EQ(j1.get_index(), 0);
	ASSERT_EQ(j2.get_index(), 1);
	ASSERT_EQ(j3.get_index(), 2);
	ASSERT_EQ(j4.get_index(), 3);
	ASSERT_EQ(j5.get_index(), 4);

	ASSERT_EQ(j1.get_floating_index(), -1);
	ASSERT_EQ(j2.get_floating_index(),  0);
	ASSERT_EQ(j3.get_floating_index(),  1);
	ASSERT_EQ(j4.get_floating_index(), -1);
	ASSERT_EQ(j5.get_floating_index(),  2);
	

	ASSERT_EQ(g1.get_index(), 0);
	ASSERT_EQ(g2.get_index(), 1);
	ASSERT_EQ(g3.get_index(), 2);
	ASSERT_EQ(g4.get_index(), 3);
	ASSERT_EQ(g5.get_index(), 4);

	ASSERT_EQ(g1.get_floating_index(), -1);
	ASSERT_EQ(g2.get_floating_index(),  0);
	ASSERT_EQ(g3.get_floating_index(), -1);
	ASSERT_EQ(g4.get_floating_index(),  1);
	ASSERT_EQ(g5.get_floating_index(),  2);

	std::vector<Junction*> expected_floating_junctions;

	expected_floating_junctions.push_back(&j2);
	expected_floating_junctions.push_back(&j3);
	expected_floating_junctions.push_back(&j5);

	ASSERT_EQ(bridge.get_floating_junctions(), expected_floating_junctions);

	std::vector<Girder*> expected_floating_girders;

	expected_floating_girders.push_back(&g2);
	expected_floating_girders.push_back(&g4);
	expected_floating_girders.push_back(&g5);

	ASSERT_EQ(bridge.get_floating_girders(), expected_floating_girders);
}
