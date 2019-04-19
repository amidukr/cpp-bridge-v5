#include <gtest/gtest.h>

#include "controller/simulation/arguments/controller_action.h"

TEST(ControllerActionTest, test_elapsed_time) {
	ControllerAction controller_action;
	
	controller_action.set_elapsed_time_micro(1000);

	ASSERT_EQ(controller_action.get_elapsed_time_micro(), 1000);
	ASSERT_EQ(controller_action.get_elapsed_time_seconds(), 0.001);
}