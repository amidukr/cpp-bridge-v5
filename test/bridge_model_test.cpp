#include<gtest/gtest.h>
#include "model/bridge_model.h"

TEST(BridgeModelTest, test_bridge_model) {
	BridgeModel bridge;

	auto junction1 = bridge.add_junction(25.0, 30.0);
	auto junction2 = bridge.add_junction(80.0, 90.0);
	auto junction3 = bridge.add_junction(45.0, 15.0);

	auto girder1 = bridge.add_girder(junction1, junction2);
	auto girder2 = bridge.add_girder(junction2, junction3);

	ASSERT_EQ(junction1->get_index(), 0);
	ASSERT_EQ(junction2->get_index(), 1);
	ASSERT_EQ(junction3->get_index(), 2);

	ASSERT_EQ(girder1->get_index(), 0);
	ASSERT_EQ(girder2->get_index(), 1);

	ASSERT_EQ(girder1->get_junction1_id(), 0);
	ASSERT_EQ(girder1->get_junction2_id(), 1);


	ASSERT_EQ(girder2->get_junction1_id(), 1);
	ASSERT_EQ(girder2->get_junction2_id(), 2);

	ASSERT_EQ(bridge.get_junctions_len(), 3);
	ASSERT_EQ(bridge.get_junction(0)->get_index(), 0);
	ASSERT_EQ(bridge.get_junction(1)->get_index(), 1);
	ASSERT_EQ(bridge.get_junction(2)->get_index(), 2);


	ASSERT_EQ(bridge.get_girder_len(), 2);
	ASSERT_EQ(bridge.get_girder(0)->get_index(), 0);
	ASSERT_EQ(bridge.get_girder(1)->get_index(), 1);
}
