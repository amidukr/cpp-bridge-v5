#include "factory/bridge_controller_factory.h"
#include "controller/elastic_bridge_controller.h"
#include "controller/matrix_bridge_controller.h"

const std::string BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER = "elastic-bridge-controller";
const std::string BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER = "matrix-bridge-controller";

BridgeControllerFactory::BridgeControllerFactory() {
}

std::unique_ptr<BridgeController> BridgeControllerFactory::create_controller(std::string controller_name) {
	if (controller_name == BridgeControllerFactory::ELASTIC_BRIDGE_CONTROLLER) {
		return std::unique_ptr<BridgeController>(new ElasticBridgeController());
	}

	if (controller_name == BridgeControllerFactory::MATRIX_BRIDGE_CONTROLLER) {
		return std::unique_ptr<BridgeController>(new MatrixBridgeController());
	}

	throw "Bridge Controller for given name not found";
}
