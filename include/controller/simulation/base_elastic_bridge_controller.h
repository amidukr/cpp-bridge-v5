#ifndef __BASE_ELASTIC_BRIDGE_CONTROLLER_H
#define __BASE_ELASTIC_BRIDGE_CONTROLLER_H

#include "controller/simulation/bridge_controller.h"

class BaseElasticBridgeController : public BridgeController {

protected:
	virtual void updateJunctionsVelocity(double elapsed_time) = 0;

public:
	void update(ControllerAction& controller_action) override;
};

#endif //__BASE_ELASTIC_BRIDGE_CONTROLLER_H
