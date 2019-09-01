#ifndef __ELASTIC_CONTROLLER_H
#define __ELASTIC_CONTROLLER_H

#include "controller/simulation/minimum_energy_bridge_controller.h"

class ElasticController : public MinimumEnergyBridgeController
{
protected:
	void updateJunctionsVelocity(double elapsed_time) override;
};

#endif /*__ELASTIC_CONTROLLER_H*/
