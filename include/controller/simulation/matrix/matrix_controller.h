#ifndef __MATRIX_CONTROLLER_H
#define __MATRIX_CONTROLLER_H

#include "controller/simulation/bridge_controller.h"

class MatrixController : public BridgeController {
public:
	void update(ControllerAction& controller_action) override;
};

#endif // __MATRIX_CONTROLLER_H
