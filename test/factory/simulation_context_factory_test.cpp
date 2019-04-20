#include <gtest/gtest.h>

#include "factory/simulation_context_factory.h"
#include "model/aplication_configuration.h"
#include "model/configuration/model_option.h"

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

	std::shared_ptr<ModelOption> model_option (new ModelOption());

	model_option->add_controller(BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER);
	model_option->add_map(SampleDataModel::PANDULUM_BRIDGE);
	model_option->add_option(SampleDataModel::TEN_TIME_FACTOR_SIMULATION);

	application_configuration->add_model_option(model_option);

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;
	ASSERT_EQ(factory.build_simulation_context(simulation), 0);

	ASSERT_TRUE(simulation.size() > 0);
}

TEST(SimulationContextFactoryTest, test_wrong) {
	std::shared_ptr<ApplicationConfiguration> application_configuration(new ApplicationConfiguration());
	SimulationContextFactory factory{ application_configuration };

	std::shared_ptr<ModelOption> model_option(new ModelOption());

	model_option->add_controller("wrong-controller-name");
	model_option->add_map(SampleDataModel::PANDULUM_BRIDGE);
	model_option->add_option(SampleDataModel::TEN_TIME_FACTOR_SIMULATION);

	application_configuration->add_model_option(model_option);

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;
	ASSERT_EQ(factory.build_simulation_context(simulation), 1);

	ASSERT_EQ(simulation.size(), 0);
}

TEST(SimulationContextFactoryTest, test_controller_asteriks) {
	std::shared_ptr<ApplicationConfiguration> application_configuration(new ApplicationConfiguration());
	SimulationContextFactory factory{ application_configuration };

	std::shared_ptr<ModelOption> model_option(new ModelOption());

	model_option->add_controller("*");
	model_option->add_map(SampleDataModel::PANDULUM_BRIDGE);
	model_option->add_option(SampleDataModel::TEN_TIME_FACTOR_SIMULATION);

	application_configuration->add_model_option(model_option);

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;
	ASSERT_EQ(factory.build_simulation_context(simulation), 0);

	ASSERT_EQ(simulation.size(), factory.get_controller_types().size());
}

TEST(SimulationContextFactoryTest, test_map_asteriks) {
	std::shared_ptr<ApplicationConfiguration> application_configuration(new ApplicationConfiguration());
	SimulationContextFactory factory{ application_configuration };

	std::shared_ptr<ModelOption> model_option(new ModelOption());

	model_option->add_controller(BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER);
	model_option->add_map("*");
	model_option->add_option(SampleDataModel::TEN_TIME_FACTOR_SIMULATION);

	application_configuration->add_model_option(model_option);

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;
	ASSERT_EQ(factory.build_simulation_context(simulation), 0);

	ASSERT_EQ(simulation.size(), factory.get_bridge_models().size());
}

TEST(SimulationContextFactoryTest, test_option_asteriks) {
	std::shared_ptr<ApplicationConfiguration> application_configuration(new ApplicationConfiguration());
	SimulationContextFactory factory{ application_configuration };

	std::shared_ptr<ModelOption> model_option(new ModelOption());

	model_option->add_controller(BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER);
	model_option->add_map(SampleDataModel::PANDULUM_BRIDGE);
	model_option->add_option("*");

	application_configuration->add_model_option(model_option);

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;
	ASSERT_EQ(factory.build_simulation_context(simulation), 0);

	ASSERT_EQ(simulation.size(), factory.get_simulation_types().size());
}

TEST(SimulationContextFactoryTest, test_two_models) {
	std::shared_ptr<ApplicationConfiguration> application_configuration(new ApplicationConfiguration());
	SimulationContextFactory factory{ application_configuration };

	std::shared_ptr<ModelOption> model_option1(new ModelOption());

	model_option1->add_controller(BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER);
	model_option1->add_map(SampleDataModel::PANDULUM_BRIDGE);
	model_option1->add_option(SampleDataModel::TEN_TIME_FACTOR_SIMULATION);

	application_configuration->add_model_option(model_option1);

	std::shared_ptr<ModelOption> model_option2(new ModelOption());

	model_option2->add_controller(BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER);
	model_option2->add_map(SampleDataModel::ROPE_BRIDGE);
	model_option2->add_option(SampleDataModel::HUNDRED_TIME_FACTOR_SIMULATION);

	application_configuration->add_model_option(model_option2);

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;
	ASSERT_EQ(factory.build_simulation_context(simulation), 0);

	ASSERT_EQ(simulation.size(), 2);
}

TEST(SimulationContextFactoryTest, test_two_maps_two_controllers) {
	std::shared_ptr<ApplicationConfiguration> application_configuration(new ApplicationConfiguration());
	SimulationContextFactory factory{ application_configuration };

	std::shared_ptr<ModelOption> model_option(new ModelOption());

	model_option->add_controller(BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER);
	model_option->add_controller(BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER);
	model_option->add_map(SampleDataModel::PANDULUM_BRIDGE);
	model_option->add_map(SampleDataModel::ROPE_BRIDGE);
	model_option->add_option(SampleDataModel::TEN_TIME_FACTOR_SIMULATION);

	application_configuration->add_model_option(model_option);

	std::vector<std::shared_ptr<BridgeSimulationContext>> simulation;
	ASSERT_EQ(factory.build_simulation_context(simulation), 0);

	ASSERT_EQ(simulation.size(), 4);
}
