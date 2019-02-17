#ifndef SAMPLE_DATA_MODEL_H
#define SAMPLE_DATA_MODEL_H

#include<string>
#include<memory>

#include "model/simulation_model.h"
#include "model/bridge_model.h"

class SampleDataModel {

	
public:
	static const std::string OPTIMAL_WITH_DELAY_SIMULATION;
	static const std::string TEN_TIME_LOW_DUMPING;
	static const std::string TEN_TIME_FACTOR_SIMULATION;
	static const std::string HUNDRED_TIME_FACTOR_SIMULATION;
	
	static const std::string ROPE_BRIDGE;
	static const std::string SWING_BRIDGE;
	static const std::string PANDULUM_BRIDGE;
	static const std::string SQUARE_BRIDGE;
	static const std::string HEART_BRIDGE;

	static const std::string LINE_UP;
	static const std::string LINE_DIAGONAL;

	static const std::string TRIANGLE_GRID;

	SampleDataModel();

	std::unique_ptr<BridgeModel> load_bridge_model(std::string model_name);
	std::unique_ptr<SimulationModel> load_simulation_model(std::string model_name);

private:
	// Disable copy constructor
	SampleDataModel(const SampleDataModel&); // no implementation 
	SampleDataModel& operator=(const SampleDataModel&); // no implementation 
};

#endif /*SAMPLE_DATA_MODEL*/