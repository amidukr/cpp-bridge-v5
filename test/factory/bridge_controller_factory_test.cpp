#include <gtest/gtest.h>

#include "factory/bridge_controller_factory.h"

#include <controller/simulation/elastic_controller.h>
#include <controller/simulation/matrix_bridge_controller.h>
#include <controller/simulation/matrix_elastic_controller.h>

class ElasticController;
class MatrixBridgeController;
class MatrixElasticController;

TEST(BridgeControllerFactoryTest, test_controlers) {
	BridgeControllerFactory factory;

	std::unique_ptr<BridgeController> elastic_controller = factory.create_controller(BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER);
	std::unique_ptr<BridgeController> matrix_bridge_controller = factory.create_controller(BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER);
	std::unique_ptr<BridgeController> matrix_elastic_controller = factory.create_controller(BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER);

	ASSERT_EQ(typeid(*elastic_controller.get()), typeid(ElasticController));
	ASSERT_EQ(typeid(*matrix_bridge_controller.get()), typeid(MatrixBridgeController));
	ASSERT_EQ(typeid(*matrix_elastic_controller.get()), typeid(MatrixElasticController));

	try {
		factory.create_controller("error-name");
		FAIL();
	}
	catch (...) {

	}
}
