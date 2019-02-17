#include <model/bridge/junction.h>

Junction::Junction(int index, bool fixed, double x, double y) {
	this->index = index;
	this->fixed = fixed;
	this->coordinate = { x, y };
}

int Junction::get_index() {
	return this->index;
}

Eigen::Vector2d Junction::get_velocity() {
	return this->velocity;
}

void Junction::set_velocity(Eigen::Vector2d velocity) {
	this->velocity = velocity;
}

void Junction::set_coordinate(Eigen::Vector2d coordinate) {
	this->coordinate = coordinate;
}

Eigen::Vector2d Junction::get_coordinate() {
	return this->coordinate;
}

double Junction::get_x() {
	return this->coordinate[0];
}

double Junction::get_y() {
	return this->coordinate[1];
}

bool Junction::is_fixed() {
	return this->fixed;
}