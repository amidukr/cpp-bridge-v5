#include<gtest/gtest.h>

#include "model/sample_data_model.h"

TEST(SampleDataModelTest, test_bridge_models) {
	SampleDataModel sample_data_model;
	
	ASSERT_TRUE(sample_data_model.load_bridge_model(SampleDataModel::ROPE_BRIDGE));
	ASSERT_TRUE(sample_data_model.load_bridge_model(SampleDataModel::SWING_BRIDGE));
	ASSERT_TRUE(sample_data_model.load_bridge_model(SampleDataModel::PANDULUM_BRIDGE));
	ASSERT_TRUE(sample_data_model.load_bridge_model(SampleDataModel::SQUARE_BRIDGE));
	ASSERT_TRUE(sample_data_model.load_bridge_model(SampleDataModel::HEART_BRIDGE));
	ASSERT_TRUE(sample_data_model.load_bridge_model(SampleDataModel::LINE_UP));
	ASSERT_TRUE(sample_data_model.load_bridge_model(SampleDataModel::LINE_DIAGONAL));
	ASSERT_TRUE(sample_data_model.load_bridge_model(SampleDataModel::TRIANGLE_GRID));

	try {
		sample_data_model.load_bridge_model("error-name");
		FAIL();
	}
	catch (...) {

	}
}

TEST(SampleDataModelTest, test_simulation_models) {
	SampleDataModel sample_data_model;

	ASSERT_TRUE(sample_data_model.load_simulation_model(SampleDataModel::OPTIMAL_WITH_DELAY_SIMULATION));
	ASSERT_TRUE(sample_data_model.load_simulation_model(SampleDataModel::TEN_TIME_LOW_DUMPING));
	ASSERT_TRUE(sample_data_model.load_simulation_model(SampleDataModel::TEN_TIME_FACTOR_SIMULATION));
	ASSERT_TRUE(sample_data_model.load_simulation_model(SampleDataModel::HUNDRED_TIME_FACTOR_SIMULATION));

	try {
		sample_data_model.load_simulation_model("error-name");
		FAIL();
	}
	catch (...) {

	}
}

