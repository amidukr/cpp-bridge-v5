#ifndef __BRIDGE_CONTROLLER_FACTORY_H
#define __BRIDGE_CONTROLLER_FACTORY_H

#include <string>
#include <memory>
#include <vector>

class BridgeController;

class BridgeControllerFactory {
	std::vector<std::string> controller_types;

public:
	static const std::string ELASTIC_CONTROLLER;
	static const std::string MATRIX_ELASTIC_CONTROLLER;
	static const std::string MATRIX_CONTROLLER;
	
	BridgeControllerFactory();

	const std::vector<std::string>& get_controller_types() const;

	std::unique_ptr<BridgeController> create_controller(std::string controller_name);

private:
	// Disable copy constructor
	BridgeControllerFactory(const BridgeControllerFactory&); // no implementation 
	BridgeControllerFactory& operator=(const BridgeControllerFactory&); // no implementation 
};

#endif // __BRIDGE_CONTROLLER_FACTORY_H

