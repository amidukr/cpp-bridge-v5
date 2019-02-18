#include "model/bridge/girder.h"

Girder::Girder(int index, int floating_index, double original_size, int jucntion1_id, int junction2_id) {
	this->index = index;
	this->floating_index = floating_index;
	this->original_size = original_size;
	this->junction1_id = jucntion1_id;
	this->junction2_id = junction2_id;
}

int Girder::get_index() {
	return this->index;
}

int Girder::get_floating_index() {
	return this->floating_index;
}

int Girder::get_junction1_id() {
	return this->junction1_id;
}

int Girder::get_junction2_id() {
	return this->junction2_id;
}

double Girder::get_original_size() {
	return this->original_size;
}
