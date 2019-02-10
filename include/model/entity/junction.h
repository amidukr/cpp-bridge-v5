#ifndef JUNCTION_H
#define JUNCTION_H

#include<array>

class Junction {

	int index;
	bool hard = false;
	std::array<double, 2> coordinate;

public:
	Junction(int index, bool hard, double x, double y);

	std::array<double, 2> get_coordinate();
	double get_x();
	double get_y();

	bool is_hard();

	int get_index();

private:
	// Disable copy constructor
	Junction(const Junction&); // no implementation 
	Junction& operator=(const Junction&); // no implementation
};

#endif /*JUNCTION_H*/