#ifndef BRIDGE_MATRIX_SERVICE_H
#define BRIDGE_MATRIX_SERVICE_H

#include <memory>
#include <utils/matrix_utils.h>
#include <Eigen/Dense>
#include <vector>

class BridgeModel;
class SimulationModel;
class Junction;


struct MatrixEquation {
	Eigen::MatrixXd left;
	Eigen::VectorXd right;
	Eigen::VectorXd roots;

	VectorIndex col_dv;

	std::unique_ptr<std::vector<Junction*>> floating_junctions;

	Eigen::Vector2d get_junction_dv(int i);

	MatrixEquation(VectorIndex vector_index);
};

class BridgeMatrixService
{
public:
	static std::unique_ptr<MatrixEquation> create_bridge_equation(BridgeModel& bridge_model, SimulationModel& simulation_model, double elapsedTime);

private:
	// Disable copy constructor
	BridgeMatrixService(const BridgeMatrixService&); // no implementation 
	BridgeMatrixService& operator=(const BridgeMatrixService&); // no implementation 
};

#endif
