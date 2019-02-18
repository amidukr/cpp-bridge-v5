#ifndef JUNCTION_H
#define JUNCTION_H

#include<array>

#include <Eigen/Dense>

class Junction {

	int index;
	int floating_index;

	bool fixed = false;

	Eigen::Vector2d coordinate;
	Eigen::Vector2d velocity = {0, 0};

public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	Junction(int index, int floating_index, bool fixed, double x, double y);

	Eigen::Vector2d get_velocity();
	void set_velocity(Eigen::Vector2d velocity);

	void set_coordinate(Eigen::Vector2d coordinate);
	Eigen::Vector2d get_coordinate();
	double get_x();
	double get_y();

	bool is_fixed();

	int get_index();
	int get_floating_index();

private:
	// Disable copy constructor
	Junction(const Junction&); // no implementation 
	Junction& operator=(const Junction&); // no implementation
};

#endif /*JUNCTION_H*/