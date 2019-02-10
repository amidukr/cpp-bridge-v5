#ifndef MATRIX_BRIDGE_CONTROLLER_H
#define MATRIX_BRIDGE_CONTROLLER_H

#include "controller/bridge_controller.h"

class MatrixBridgeController : public BridgeController {
public:
	void update(ControllerAction& controller_action) override;
};

#endif //MATRIX_BRIDGE_CONTROLLER_H
