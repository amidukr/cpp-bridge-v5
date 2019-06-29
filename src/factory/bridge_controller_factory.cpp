#include "factory/bridge_controller_factory.h"
#include "controller/simulation/elastic_controller.h"
#include "controller/simulation/matrix_elastic_controller.h"
#include "controller/simulation/matrix_bridge_controller.h"

const std::string BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER = "elastic";
const std::string BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER = "matrix-elastic";
const std::string BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER = "matrix";

BridgeControllerFactory::BridgeControllerFactory() {
	this->controller_types.push_back(BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER);
	this->controller_types.push_back(BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER);
	this->controller_types.push_back(BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER);
}

const std::vector<std::string>& BridgeControllerFactory::get_controller_types() const {
	return this->controller_types;
}

std::unique_ptr<BridgeController> BridgeControllerFactory::create_controller(std::string controller_name) {
	if (controller_name == BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER) {
		return std::unique_ptr<BridgeController>(new ElasticController());
	}

	if (controller_name == BridgeControllerFactory::MATRIX_ELASTIC_BRIDGE_CONTROLLER) {
		return std::unique_ptr<BridgeController>(new MatrixElasticController());
	}

	if (controller_name == BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER) {
		return std::unique_ptr<BridgeController>(new MatrixBridgeController());
	}

	throw "Bridge Controller for given name not found";
}
