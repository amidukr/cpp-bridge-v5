#ifndef __MATRIX_ELASTIC_CONTROLLER_H
#define __MATRIX_ELASTIC_CONTROLLER_H

#include "controller/simulation/base_elastic_bridge_controller.h"

class MatrixElasticController : public BaseElasticBridgeController
{
protected:
	void updateJunctionsVelocity(double elapsed_time) override;
};

#endif /*__MATRIX_ELASTIC_CONTROLLER_H*/