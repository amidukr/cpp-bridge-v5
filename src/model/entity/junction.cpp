#include <model/entity/junction.h>

Junction::Junction(int index, bool hard, double x, double y) {
	this->index = index;
	this->hard = hard;
	this->coordinate = { x, y };
}

int Junction::get_index() {
	return this->index;
}

std::array<double, 2> Junction::get_coordinate() {
	return this->coordinate;
}

double Junction::get_x() {
	return this->coordinate[0];
}

double Junction::get_y() {
	return this->coordinate[1];
}

bool Junction::is_hard() {
	return this->hard;
}