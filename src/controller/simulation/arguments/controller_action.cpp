#include "controller/simulation/arguments/controller_action.h"

ControllerAction::ControllerAction() {

}

void ControllerAction::set_elapsed_time_micro(long elapsed_time) {
	this->elapsed_time = elapsed_time;
}

long ControllerAction::get_elapsed_time_micro() {
	return this->elapsed_time;
}

double ControllerAction::get_elapsed_time_seconds() {
	return this->elapsed_time / 1000000.0;
}
