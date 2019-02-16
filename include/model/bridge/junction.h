#ifndef JUNCTION_H
#define JUNCTION_H

#include<array>

#include <Eigen/Dense>

class Junction {

	int index;
	bool hard = false;

	Eigen::Vector2d coordinate;
	Eigen::Vector2d velocity = {0, 0};

public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	Junction(int index, bool hard, double x, double y);

	Eigen::Vector2d get_velocity();
	void set_velocity(Eigen::Vector2d velocity);

	void set_coordinate(Eigen::Vector2d coordinate);
	Eigen::Vector2d get_coordinate();
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