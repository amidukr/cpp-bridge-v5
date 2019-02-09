#include "model/bridge_model.h"

Junction::Junction(int index, double x, double y) {
	this->index = index;
}

Girder::Girder(int index, int jucntion1_id, int junction2_id) {
	this->index = index;
	this->junction1_id = jucntion1_id;
	this->junction2_id = junction2_id;
}

BridgeModel::BridgeModel() {

}

std::shared_ptr<Junction> BridgeModel::add_junction(double x, double y) {
	std::shared_ptr<Junction> junction(new Junction(this->junctions.size(), x, y));

	this->junctions.push_back(junction);

	return junction;
}

std::shared_ptr<Girder> BridgeModel::add_girder(std::shared_ptr<Junction> junction1, std::shared_ptr<Junction> junction2) {
	std::shared_ptr<Girder> girder(new Girder(this->girders.size(), junction1->get_index(), junction2->get_index()));

	this->girders.push_back(girder);

	return girder;
}

std::shared_ptr<Junction> BridgeModel::get_junction(int index) {
	return this->junctions.at(index);
}

std::shared_ptr<Girder> BridgeModel::get_girder(int index) {
	return this->girders.at(index);
}

int BridgeModel::get_girder_len() {
	return this->girders.size();
}

int BridgeModel::get_junctions_len() {
	return this->junctions.size();
}

int Junction::get_index() {
	return this->index;
}

int Girder::get_index() {
	return this->index;
}

int Girder::get_junction1_id() {
	return this->junction1_id;
}

int Girder::get_junction2_id() {
	return this->junction2_id;
}
