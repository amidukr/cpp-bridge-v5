#include "factory/bridge_controller_factory.h"

#include <controller/simulation/elastic/elastic_controller.h>
#include <controller/simulation/matrix/matrix_elastic_controller.h>
#include "controller/simulation/matrix/matrix_controller.h"

const std::string BridgeControllerFactory::ELASTIC_CONTROLLER = "elastic";
const std::string BridgeControllerFactory::MATRIX_ELASTIC_CONTROLLER = "matrix-elastic";
const std::string BridgeControllerFactory::MATRIX_CONTROLLER = "matrix";

BridgeControllerFactory::BridgeControllerFactory() {
	this->controller_types.push_back(BridgeControllerFactory::ELASTIC_CONTROLLER);
	this->controller_types.push_back(BridgeControllerFactory::MATRIX_ELASTIC_CONTROLLER);
	this->controller_types.push_back(BridgeControllerFactory::MATRIX_CONTROLLER);
}

const std::vector<std::string>& BridgeControllerFactory::get_controller_types() const {
	return this->controller_types;
}

std::unique_ptr<BridgeController> BridgeControllerFactory::create_controller(std::string controller_name) {
	if (controller_name == BridgeControllerFactory::ELASTIC_CONTROLLER) {
		return std::unique_ptr<BridgeController>(new ElasticController());
	}

	if (controller_name == BridgeControllerFactory::MATRIX_ELASTIC_CONTROLLER) {
		return std::unique_ptr<BridgeController>(new MatrixElasticController());
	}

	if (controller_name == BridgeControllerFactory::MATRIX_CONTROLLER) {
		return std::unique_ptr<BridgeController>(new MatrixController());
	}

	throw "Bridge Controller for given name not found";
}
