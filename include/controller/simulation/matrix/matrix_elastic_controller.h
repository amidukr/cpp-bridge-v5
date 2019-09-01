#ifndef __MATRIX_ELASTIC_CONTROLLER_H
#define __MATRIX_ELASTIC_CONTROLLER_H

#include "controller/simulation/minimum_energy_bridge_controller.h"

class MatrixElasticController : public MinimumEnergyBridgeController
{
protected:
	void updateJunctionsVelocity(double elapsed_time) override;
};

#endif /*__MATRIX_ELASTIC_CONTROLLER_H*/
