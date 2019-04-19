#include <gtest/gtest.h>

#include "model/simulation_model.h"
#include "model/bridge_model.h"
#include "controller/simulation/base_elastic_bridge_controller.h"
#include "controller/simulation/arguments/controller_action.h"

class MockedElasticBridgeController : public BaseElasticBridgeController {
double last_elapsed_time_seconds = -1;
bool update_invoked = false;
protected:
	virtual void updateJunctionsVelocity(double elapsed_time) {
		this->update_invoked = true;
		this->last_elapsed_time_seconds = elapsed_time;
	}

public:
	double get_last_elapsed_time_seconds() {
		return this->last_elapsed_time_seconds;
	}
	
	bool is_update_invoked() {
		return this->update_invoked;
	}

};

TEST(BaseElasticBridgeControllerTest, test_update_flow) {
	MockedElasticBridgeController mocked_controller{};
	ControllerAction action;
	std::shared_ptr<SimulationModel> simulation_model = std::shared_ptr<SimulationModel>(new SimulationModel());
	
	simulation_model->set_time_factor(2);

	mocked_controller.set_simulation_model(simulation_model);
	mocked_controller.set_bridge_model(std::shared_ptr<BridgeModel>(new BridgeModel()));

	action.set_elapsed_time_micro(800);

	ASSERT_FALSE(mocked_controller.is_update_invoked());

	mocked_controller.update(action);

	ASSERT_TRUE(mocked_controller.is_update_invoked());
	ASSERT_EQ(mocked_controller.get_last_elapsed_time_seconds(), 0.0016);
}
