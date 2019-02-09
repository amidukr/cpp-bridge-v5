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

	std::vector<std::shared_ptr<Junction>> junctions;
	std::vector<std::shared_ptr<Girder>> girders;

public:
	BridgeModel();

	std::shared_ptr<Junction> add_junction(double x, double y);
	std::shared_ptr<Girder> add_girder(std::shared_ptr<Junction> junction1, std::shared_ptr<Junction> junction2);
	std::shared_ptr<Junction> get_junction(int i);
	std::shared_ptr<Girder> get_girder(int i);

	int get_girder_len();
	int get_junctions_len();
private:
	// Disable copy constructor
	BridgeModel(const BridgeModel&); // no implementation 
	BridgeModel& operator=(const BridgeModel&); // no implementation 
};

#endif /* BRIDGE_MODEL_H */