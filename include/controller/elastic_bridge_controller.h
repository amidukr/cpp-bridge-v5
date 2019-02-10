#ifndef ELASTIC_BRIDGE_CONTROLLER_H
#define ELASTIC_BRIDGE_CONTROLLER_H

#include "controller/bridge_controller.h"

class ElasticBridgeController : public BridgeController {
public:
	void update(ControllerAction& controller_action) override;
};

#endif //ELASTIC_BRIDGE_CONTROLLER_H
