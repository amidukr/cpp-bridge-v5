#include <algorithm>

#include "model/bridge_model.h"
#include "model/entity/junction.h"
#include "model/entity/girder.h"



BridgeModel::BridgeModel() {

}

Junction& BridgeModel::add_junction(bool hard, double x, double y) {
	Junction* junction = new Junction(this->junctions.size(), hard, x, y);
	
	this->junctions.push_back(std::unique_ptr<Junction>(junction));

	return *junction;
}

Junction& BridgeModel::add_junction(double x, double y) {
	return this->add_junction(false, x, y);
}

Junction& BridgeModel::add_hard_junction(double x, double y) {
	return this->add_junction(true, x, y);
}


Girder& BridgeModel::add_girder(Junction& junction1, Junction& junction2) {
	Girder* girder = new Girder(this->girders.size(), junction1.get_index(), junction2.get_index());

	this->girders.push_back(std::unique_ptr<Girder>(girder));

	return *girder;
}

Junction& BridgeModel::get_junction(int index) {
	return *this->junctions.at(index);
}

Girder& BridgeModel::get_girder(int index) {
	return *this->girders.at(index);
}

int BridgeModel::get_girder_len() {
	return this->girders.size();
}

int BridgeModel::get_junctions_len() {
	return this->junctions.size();
}

std::array<double, 4> BridgeModel::get_bounds() {
	std::array<double, 4> result = {0, 0, 0, 0};

	if (this->get_junctions_len() > 0) {
		std::array<double, 2> coordinate = this->get_junction(0).get_coordinate();
		result = { coordinate[0], coordinate[1], coordinate[0], coordinate[1] };
	}

	for (int i = 1; i < this->get_junctions_len(); i++) {
		std::array<double, 2> coordinate = this->get_junction(i).get_coordinate();

		result[0] = std::min(result[0], coordinate[0]);
		result[1] = std::min(result[1], coordinate[1]);

		result[2] = std::max(result[2], coordinate[0]);
		result[3] = std::max(result[3], coordinate[1]);
	}

	return result;
}
