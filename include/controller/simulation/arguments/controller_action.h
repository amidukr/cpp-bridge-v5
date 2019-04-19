#ifndef CONTROLLER_ACTION_H
#define CONTROLLER_ACTION_H

class ControllerAction {

	long elapsed_time = 0;
public:
	ControllerAction();

	void set_elapsed_time_micro(long elapsed_time);
	long get_elapsed_time_micro();
	double get_elapsed_time_seconds();

private:
	// Disable copy constructor
	ControllerAction(const ControllerAction&); // no implementation 
	ControllerAction& operator=(const ControllerAction&); // no implementation
};

#endif /*CONTROLLER_ACTION_H*/
