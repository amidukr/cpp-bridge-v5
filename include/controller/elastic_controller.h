#ifndef __ELASTIC_CONTROLLER_H
#define __ELASTIC_CONTROLLER_H

#include "controller/base_elastic_bridge_controller.h"

class ElasticController : public BaseElasticBridgeController
{
protected:
	void updateJunctionsVelocity(double elapsed_time) override;
};

#endif /*__GRAVITY_ELASTIC_CONTROLLER_H*/