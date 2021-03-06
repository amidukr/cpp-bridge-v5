#include "model/application_configuration.h"

ApplicationConfiguration::ApplicationConfiguration()
{
}

const std::vector<std::shared_ptr<SimulationOption>>& ApplicationConfiguration::get_simulation_options() const {
	return this->simulation_options;
}

void ApplicationConfiguration::add_simulation_option(std::shared_ptr<SimulationOption> model_option) {
	this->simulation_options.push_back(model_option);
}

bool ApplicationConfiguration::get_write_video_flag() const {
	return this->write_video_flag;
}

bool ApplicationConfiguration::get_run_test_flag() const {
	return this->run_test_flag;
}


void ApplicationConfiguration::set_write_video_flag(bool write_video_flag) {
	this->write_video_flag = write_video_flag;
}


void ApplicationConfiguration::set_run_test_flag(bool run_test_flag) {
	this->run_test_flag = run_test_flag;
}

void ApplicationConfiguration::set_headless_mode_flag(bool headless_mode) {
	this->headless_mode_flag = headless_mode;
}

bool ApplicationConfiguration::get_headless_mode_flag() {
	return this->headless_mode_flag;
}
