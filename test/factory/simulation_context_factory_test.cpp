#include <gtest/gtest.h>

#include "factory/simulation_context_factory.h"
#include "model/application_configuration.h"
#include "model/configuration/simulation_option.h"

#include "model/sample_data_model.h"
#include "factory/bridge_controller_factory.h"


TEST(SimulationContextFactoryTest, test_defaults) {
	std::shared_ptr<ApplicationConfiguration> application_configuration(new ApplicationConfiguration());
	SimulationContextFactory factory { application_configuration };

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;

	factory.build_simulation_context(simulation);

	ASSERT_TRUE(simulation.size() > 0);
}

TEST(SimulationContextFactoryTest, test_single) {
	std::shared_ptr<ApplicationConfiguration> application_configuration (new ApplicationConfiguration());
	SimulationContextFactory factory{ application_configuration };

	std::shared_ptr<SimulationOption> model_option (new SimulationOption());

	model_option->add_controller_type(BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER);
	model_option->add_bridge_model(SampleDataModel::PANDULUM_BRIDGE);
	model_option->add_simulation_type(SampleDataModel::TEN_TIME_FACTOR_SIMULATION);

	application_configuration->add_simulation_option(model_option);

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;
	ASSERT_EQ(factory.build_simulation_context(simulation), 0);

	ASSERT_TRUE(simulation.size() > 0);
}

TEST(SimulationContextFactoryTest, test_wrong) {
	std::shared_ptr<ApplicationConfiguration> application_configuration(new ApplicationConfiguration());
	SimulationContextFactory factory{ application_configuration };

	std::shared_ptr<SimulationOption> model_option(new SimulationOption());

	model_option->add_controller_type("wrong-controller-name");
	model_option->add_bridge_model(SampleDataModel::PANDULUM_BRIDGE);
	model_option->add_simulation_type(SampleDataModel::TEN_TIME_FACTOR_SIMULATION);

	application_configuration->add_simulation_option(model_option);

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;
	ASSERT_EQ(factory.build_simulation_context(simulation), 1);

	ASSERT_EQ(simulation.size(), 0);
}

TEST(SimulationContextFactoryTest, test_controller_asteriks) {
	std::shared_ptr<ApplicationConfiguration> application_configuration(new ApplicationConfiguration());
	SimulationContextFactory factory{ application_configuration };

	std::shared_ptr<SimulationOption> model_option(new SimulationOption());

	model_option->add_controller_type("*");
	model_option->add_bridge_model(SampleDataModel::PANDULUM_BRIDGE);
	model_option->add_simulation_type(SampleDataModel::TEN_TIME_FACTOR_SIMULATION);

	application_configuration->add_simulation_option(model_option);

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;
	ASSERT_EQ(factory.build_simulation_context(simulation), 0);

	ASSERT_EQ(simulation.size(), factory.get_controller_types().size());
}

TEST(SimulationContextFactoryTest, test_map_asteriks) {
	std::shared_ptr<ApplicationConfiguration> application_configuration(new ApplicationConfiguration());
	SimulationContextFactory factory{ application_configuration };

	std::shared_ptr<SimulationOption> model_option(new SimulationOption());

	model_option->add_controller_type(BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER);
	model_option->add_bridge_model("*");
	model_option->add_simulation_type(SampleDataModel::TEN_TIME_FACTOR_SIMULATION);

	application_configuration->add_simulation_option(model_option);

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;
	ASSERT_EQ(factory.build_simulation_context(simulation), 0);

	ASSERT_EQ(simulation.size(), factory.get_bridge_models().size());
}

TEST(SimulationContextFactoryTest, test_option_asteriks) {
	std::shared_ptr<ApplicationConfiguration> application_configuration(new ApplicationConfiguration());
	SimulationContextFactory factory{ application_configuration };

	std::shared_ptr<SimulationOption> model_option(new SimulationOption());

	model_option->add_controller_type(BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER);
	model_option->add_bridge_model(SampleDataModel::PANDULUM_BRIDGE);
	model_option->add_simulation_type("*");

	application_configuration->add_simulation_option(model_option);

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;
	ASSERT_EQ(factory.build_simulation_context(simulation), 0);

	ASSERT_EQ(simulation.size(), factory.get_simulation_types().size());
}

TEST(SimulationContextFactoryTest, test_two_models) {
	std::shared_ptr<ApplicationConfiguration> application_configuration(new ApplicationConfiguration());
	SimulationContextFactory factory{ application_configuration };

	std::shared_ptr<SimulationOption> model_option1(new SimulationOption());

	model_option1->add_controller_type(BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER);
	model_option1->add_bridge_model(SampleDataModel::PANDULUM_BRIDGE);
	model_option1->add_simulation_type(SampleDataModel::TEN_TIME_FACTOR_SIMULATION);

	application_configuration->add_simulation_option(model_option1);

	std::shared_ptr<SimulationOption> model_option2(new SimulationOption());

	model_option2->add_controller_type(BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER);
	model_option2->add_bridge_model(SampleDataModel::ROPE_BRIDGE);
	model_option2->add_simulation_type(SampleDataModel::HUNDRED_TIME_FACTOR_SIMULATION);

	application_configuration->add_simulation_option(model_option2);

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;
	ASSERT_EQ(factory.build_simulation_context(simulation), 0);

	ASSERT_EQ(simulation.size(), 2);
}

TEST(SimulationContextFactoryTest, test_two_maps_two_controllers) {
	std::shared_ptr<ApplicationConfiguration> application_configuration(new ApplicationConfiguration());
	SimulationContextFactory factory{ application_configuration };

	std::shared_ptr<SimulationOption> model_option(new SimulationOption());

	model_option->add_controller_type(BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER);
	model_option->add_controller_type(BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER);
	model_option->add_bridge_model(SampleDataModel::PANDULUM_BRIDGE);
	model_option->add_bridge_model(SampleDataModel::ROPE_BRIDGE);
	model_option->add_simulation_type(SampleDataModel::TEN_TIME_FACTOR_SIMULATION);

	application_configuration->add_simulation_option(model_option);

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;
	ASSERT_EQ(factory.build_simulation_context(simulation), 0);

	ASSERT_EQ(simulation.size(), 4);
}
