#ifndef __MATRIX_CONTROLLER_H
#define __MATRIX_CONTROLLER_H

#include "controller/simulation/kinematic_bridge_controller.h"

class MatrixController : public KinematicBridgeController {
public:
	void updateJunctionsVelocity(double elapsed_time) override;
};

#endif // __MATRIX_CONTROLLER_H
