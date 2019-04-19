#include "model/aplication_configuration.h"

ApplicationConfiguration::ApplicationConfiguration()
{
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