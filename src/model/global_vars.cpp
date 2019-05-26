#include "model/global_vars.h"

bool GlobalVars::headless_mode_flag = false;

void GlobalVars::set_headless_mode_flag(bool headless_mode) {
	GlobalVars::headless_mode_flag = headless_mode;
}

bool GlobalVars::get_headless_mode_flag() {
	return GlobalVars::headless_mode_flag;
}
