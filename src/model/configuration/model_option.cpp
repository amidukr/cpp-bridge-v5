#include "model/configuration/model_option.h"


ModelOption::ModelOption()
{
}


const std::vector<std::string>& ModelOption::get_controllers() const {
	return this->controllers;
}

const std::vector<std::string>& ModelOption::get_maps() const {
	return this->maps;
}

const std::vector<std::string>& ModelOption::get_options() const {
	return this->options;
}

void ModelOption::add_controller(std::string controller) {
	this->controllers.push_back(controller);
}

void ModelOption::add_map(std::string map) {
	this->maps.push_back(map);
}

void ModelOption::add_option(std::string option) {
	this->options.push_back(option);
}
