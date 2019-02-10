#include "model/simulation_model.h"

SimulationModel::SimulationModel() {

}

void SimulationModel::set_gravity(Eigen::Vector2d gravity) {
	this->gravity = gravity;
}

Eigen::Vector2d SimulationModel::get_gravity(){
	return this->gravity;
}

void SimulationModel::set_spring_characteristic(double spring_characteristic) {
	this->spring_characteristic = spring_characteristic;
}

double SimulationModel::get_spring_characteristic(){
	return this->spring_characteristic;
}

void SimulationModel::set_time_factor(double time_factor) {
	this->time_factor = time_factor;
}

double SimulationModel::get_time_factor() {
	return time_factor;
}

void SimulationModel::set_iteration_delay(long iteration_delay) {
	this->iteration_delay = iteration_delay;
}

long SimulationModel::get_iteration_delay() {
	return this->iteration_delay;
}

void SimulationModel::set_dumping_ration(double dumping_ration) {
	this->dumping_ration = dumping_ration;
}

double SimulationModel::get_dumping_ration() {
	return this->dumping_ration = dumping_ration;
}
