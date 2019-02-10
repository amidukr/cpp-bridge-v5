#ifndef BRIDGE_MODEL_H
#define BRIDGE_MODEL_H

#include<vector>
#include<memory>

class Junction {

	int index;

public:
	Junction(int index, double x, double y);

	int get_index();

private:
	// Disable copy constructor
	Junction(const Junction&); // no implementation 
	Junction& operator=(const Junction&); // no implementation
};

class Girder {

	int index;
	int junction1_id;
	int junction2_id;

public:
	Girder(int index, int junction1_id, int junction2_id);

	int get_index();
	int get_junction1_id();
	int get_junction2_id();

private:
	// Disable copy constructor
	Girder(const Girder&); // no implementation 
	Girder& operator=(const Girder&); // no implementation
};

class BridgeModel {

	std::vector<std::unique_ptr<Junction>> junctions;
	std::vector<std::unique_ptr<Girder>> girders;

public:
	BridgeModel();

	Junction& add_junction(double x, double y);
	Girder& add_girder(Junction& junction1, Junction& junction2);
	Junction& get_junction(int i);
	Girder& get_girder(int i);

	int get_girder_len();
	int get_junctions_len();
private:
	// Disable copy constructor
	BridgeModel(const BridgeModel&); // no implementation 
	BridgeModel& operator=(const BridgeModel&); // no implementation 
};

#endif /* BRIDGE_MODEL_H */