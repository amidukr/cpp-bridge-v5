#ifndef BRIDGE_MODEL_H
#define BRIDGE_MODEL_H

#include<vector>
#include<memory>

#include<model/entity/girder.h>
#include<model/entity/junction.h>

class BridgeModel {

	std::vector<std::unique_ptr<Junction>> junctions;
	std::vector<std::unique_ptr<Girder>> girders;

	Junction& BridgeModel::add_junction(bool hard, double x, double y);
public:
	BridgeModel();

	Junction& add_junction(double x, double y);
	Junction& add_hard_junction(double x, double y);
	Girder& add_girder(Junction& junction1, Junction& junction2);
	Junction& get_junction(int i);
	Girder& get_girder(int i);

	int get_girder_len();
	int get_junctions_len();

	std::array<double, 4> BridgeModel::get_bounds();

private:
	// Disable copy constructor
	BridgeModel(const BridgeModel&); // no implementation 
	BridgeModel& operator=(const BridgeModel&); // no implementation 
};

#endif /* BRIDGE_MODEL_H */