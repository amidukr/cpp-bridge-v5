#ifndef BRIDGE_MATRIX_SERVICE_H
#define BRIDGE_MATRIX_SERVICE_H

#include <memory>
#include <Eigen/Dense>

class BridgeModel;
class SimulationModel;

struct MatrixEquation {
	Eigen::MatrixXd left;
	Eigen::VectorXd right;
};

class BridgeMatrixService
{
public:
	static std::unique_ptr<MatrixEquation> create_bridge_equation(BridgeModel& bridgeModel, SimulationModel& simulation_model, double time);

private:
	// Disable copy constructor
	BridgeMatrixService(const BridgeMatrixService&); // no implementation 
	BridgeMatrixService& operator=(const BridgeMatrixService&); // no implementation 
};

#endif