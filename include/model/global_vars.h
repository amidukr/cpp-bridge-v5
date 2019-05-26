#ifndef __GLOBAL_VARS_H
#define __GLOBAL_VARS_H



class GlobalVars
{
	static bool headless_mode_flag;

public:

	static void set_headless_mode_flag(bool headless_mode);
	static bool get_headless_mode_flag();

private:
	GlobalVars();

	// Disable copy constructor
	GlobalVars(const GlobalVars&); // no implementation 
	GlobalVars& operator=(const GlobalVars&); // no implementation 
};

#endif /* __GLOBAL_VARS_H */

