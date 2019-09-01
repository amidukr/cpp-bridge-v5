#ifndef __MINIMUM_ENERGY_BRIDGE_CONTROLLER_H
#define __MINIMUM_ENERGY_BRIDGE_CONTROLLER_H

#include "controller/simulation/kinematic_bridge_controller.h"

class MinimumEnergyBridgeController : public KinematicBridgeController {
public:
	void update(ControllerAction& controller_action) override;
};

#endif //__MINIMUM_ENERGY_BRIDGE_CONTROLLER_H
