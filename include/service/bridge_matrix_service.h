#ifndef BRIDGE_MATRIX_SERVICE_H
#define BRIDGE_MATRIX_SERVICE_H

#include <memory>
#include <Eigen/Dense>
#include <vector>

#include "utils/matrix_equation.h"


class BridgeModel;
class SimulationModel;
class Junction;

class BridgeMatrixService
{
public:
	static std::unique_ptr<MatrixEquation> create_floating_junctions_equation(BridgeModel& bridge_model, SimulationModel& simulation_model, double elapsedTime);

private:
	// Disable copy constructor
	BridgeMatrixService(const BridgeMatrixService&); // no implementation 
	BridgeMatrixService& operator=(const BridgeMatrixService&); // no implementation 
};

#endif
