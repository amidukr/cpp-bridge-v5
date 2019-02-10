#include "model/entity/girder.h"

Girder::Girder(int index, int jucntion1_id, int junction2_id) {
	this->index = index;
	this->junction1_id = jucntion1_id;
	this->junction2_id = junction2_id;
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
