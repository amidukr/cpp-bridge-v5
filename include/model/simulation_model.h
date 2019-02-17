#ifndef SIMULATION_MODEL_H
#define SIMULATION_MODEL_H

#include <Eigen/Dense>

class SimulationModel {
	Eigen::Vector2d gravity = { 0, 0 };
	double spring_characteristic = 0;
	double time_factor = 0;
	long iteration_delay = 0;
	double dumping_ratio = 0;

public:
	SimulationModel();

	void set_gravity(Eigen::Vector2d gravity);
	Eigen::Vector2d get_gravity();

	void set_spring_characteristic(double spring_characteristic);
	double get_spring_characteristic();

	void set_time_factor(double time_factor);
	double get_time_factor();

	void set_iteration_delay(long iteration_delay);
	long get_iteration_delay();

	void set_dumping_ratio(double dumping_ratio);
	double get_dumping_ratio();
};

#endif SIMULATION_SETTINGS_MODEL_H