#include <algorithm>

#include "model/bridge_model.h"


BridgeModel::BridgeModel() {
	
}

double BridgeModel::get_prefered_scale_out_factor() {
	return this->prefered_scale_out_factor;
}

void BridgeModel::set_prefered_scale_out_factor(double prefered_scale_out_factor) {
	this->prefered_scale_out_factor = prefered_scale_out_factor;
}


Junction& BridgeModel::add_junction(bool fixed, double x, double y) {
	int index = this->junctions.size();
	int floating_index = fixed ? -1 : this->floating_junctions.size();

	Junction* junction = new Junction(index, floating_index, fixed, x, y);
	
	this->junctions.push_back(std::unique_ptr<Junction>(junction));
	junction_girders.push_back(std::vector<Girder*>());

	if (!fixed) {
		this->floating_junctions.push_back(junction);
	}

	return *junction;
}

Junction& BridgeModel::add_junction(double x, double y) {
	return this->add_junction(false, x, y);
}

Junction& BridgeModel::add_fixed_junction(double x, double y) {
	return this->add_junction(true, x, y);
}


Girder& BridgeModel::add_girder(Junction& junction1, Junction& junction2) {
	double original_size = (junction2.get_coordinate() - junction1.get_coordinate()).norm();
	bool fixed = junction1.is_fixed() && junction2.is_fixed();

	int index = this->girders.size();
	int floating_index = fixed ? -1 : this->floating_girders.size();

	Girder* girder = new Girder(index, floating_index, original_size, junction1.get_index(), junction2.get_index());

	this->girders.push_back(std::unique_ptr<Girder>(girder));
	junction_girders[junction1.get_index()].push_back(girder);
	junction_girders[junction2.get_index()].push_back(girder);

	if (!fixed) {
		this->floating_girders.push_back(girder);
	}

	return *girder;
}

const std::vector<Junction*>& BridgeModel::get_floating_junctions() {
	return this->floating_junctions;
}

const std::vector<Girder*>& BridgeModel::get_floating_girders() {
	return this->floating_girders;
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
		Eigen::Vector2d coordinate = this->get_junction(0).get_coordinate();
		result = { coordinate[0], coordinate[1], coordinate[0], coordinate[1] };
	}

	for (int i = 1; i < this->get_junctions_len(); i++) {
		Eigen::Vector2d coordinate = this->get_junction(i).get_coordinate();

		result[0] = std::min(result[0], coordinate[0]);
		result[1] = std::min(result[1], coordinate[1]);

		result[2] = std::max(result[2], coordinate[0]);
		result[3] = std::max(result[3], coordinate[1]);
	}

	return result;
}

const std::vector<Girder*>& BridgeModel::get_junction_girders(Junction& junction) {
	return junction_girders.at(junction.get_index());
}