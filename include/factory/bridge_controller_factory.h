#ifndef BRIDGE_CONTROLLER_FACTORY_H
#define BRIDGE_CONTROLLER_FACTORY

#include <string>
#include <memory>

class BridgeController;

class BridgeControllerFactory {
public:
	static const std::string ELASTIC_BRIDGE_CONTROLLER;
	static const std::string MATRIX_ELASTIC_BRIDGE_CONTROLLER;
	static const std::string MATRIX_BRIDGE_CONTROLLER;

	BridgeControllerFactory();

	std::unique_ptr<BridgeController> create_controller(std::string controller_name);

private:
	// Disable copy constructor
	BridgeControllerFactory(const BridgeControllerFactory&); // no implementation 
	BridgeControllerFactory& operator=(const BridgeControllerFactory&); // no implementation 
};

#endif // !BRIDGE_CONTROLLER_FACTORY_H

