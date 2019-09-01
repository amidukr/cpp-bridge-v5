#ifndef __KINEMATIC_BRIDGE_CONTROLLER_H
#define __KINEMATIC_BRIDGE_CONTROLLER_H

#include "controller/simulation/bridge_controller.h"

class KinematicBridgeController : public BridgeController {

protected:
	virtual void updateJunctionsVelocity(double elapsed_time) = 0;

public:
	void update(ControllerAction& controller_action) override;
};

#endif //__MINIMUM_ENERGY_BRIDGE_CONTROLLER_H
