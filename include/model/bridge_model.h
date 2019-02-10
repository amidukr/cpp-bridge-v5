#ifndef BRIDGE_MODEL_H
#define BRIDGE_MODEL_H

#include<vector>
#include<memory>

#include<model/bridge/girder.h>
#include<model/bridge/junction.h>

class BridgeModel {

	double prefered_scale_out_factor = 10;
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

	double get_prefered_scale_out_factor();
	void set_prefered_scale_out_factor(double prefered_scale_out_factor);

	int get_girder_len();
	int get_junctions_len();

	std::array<double, 4> BridgeModel::get_bounds();

private:
	// Disable copy constructor
	BridgeModel(const BridgeModel&); // no implementation 
	BridgeModel& operator=(const BridgeModel&); // no implementation 
};

#endif /* BRIDGE_MODEL_H */