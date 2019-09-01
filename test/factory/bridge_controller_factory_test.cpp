#include "factory/bridge_controller_factory.h"

#include <controller/simulation/elastic/elastic_controller.h>
#include <controller/simulation/matrix/matrix_controller.h>
#include <controller/simulation/matrix/matrix_elastic_controller.h>

#include <gtest/gtest.h>

class ElasticController;
class MatrixController;
class MatrixElasticController;

TEST(BridgeControllerFactoryTest, test_controlers) {
	BridgeControllerFactory factory;

	std::unique_ptr<BridgeController> elastic_controller = factory.create_controller(BridgeControllerFactory::ELASTIC_CONTROLLER);
	std::unique_ptr<BridgeController> matrix_bridge_controller = factory.create_controller(BridgeControllerFactory::MATRIX_CONTROLLER);
	std::unique_ptr<BridgeController> matrix_elastic_controller = factory.create_controller(BridgeControllerFactory::MATRIX_ELASTIC_CONTROLLER);

	ASSERT_EQ(typeid(*elastic_controller.get()), typeid(ElasticController));
	ASSERT_EQ(typeid(*matrix_bridge_controller.get()), typeid(MatrixController));
	ASSERT_EQ(typeid(*matrix_elastic_controller.get()), typeid(MatrixElasticController));

	try {
		factory.create_controller("error-name");
		FAIL();
	}
	catch (...) {

	}
}
