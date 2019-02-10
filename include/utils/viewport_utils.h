#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <array>

class Viewport {
	std::array<double, 4> ortho_matrix;
	std::array<double, 4> viewport_matrix;
	double point_size;

public: 
	Viewport(double point_size, std::array<double, 4> ortho_matrix, std::array<double, 4> viewport_matrix);

	double get_point_size();
	std::array<double, 4> get_ortho_matrix();
	std::array<double, 4> get_viewport_matrix();
};

class ViewportUtil {
public :
	static Viewport calculate_viewport(double windowWidth, double windowHeight, double left, double bottom, double right, double top, double scaleOutFactor);
};

#endif
