#include <utils/viewport_utils.h>

Viewport::Viewport(double point_size, std::array<double, 4> ortho_matrix, std::array<double, 4> viewport_matrix) {
	this->point_size = point_size;
	this->ortho_matrix = ortho_matrix;
	this->viewport_matrix = viewport_matrix;
}

double Viewport::get_point_size() {
	return this->point_size;
}

std::array<double, 4> Viewport::get_ortho_matrix() {
	return this->ortho_matrix;
}

std::array<double, 4> Viewport::get_viewport_matrix() {
	return this->viewport_matrix;
}

Viewport ViewportUtil::calculate_viewport(double windowWidth, double windowHeight, double boundsLeft, double boundsBottom, double boundsRight, double boundsTop, double scaleOutFactor) {
	double width = boundsRight - boundsLeft;
	double height = boundsTop - boundsBottom;

	double max_size = std::max(width, height);
	std::array<double, 2> center = { (boundsLeft + boundsRight) / 2.0,
								     (boundsTop  + boundsBottom) / 2.0, };

	double point_size = max_size / 100;

	std::array<double, 4> orht_matrix = { center[0] - max_size * scaleOutFactor/2.0,
								          center[0] + max_size * scaleOutFactor / 2.0,
									      center[1] - max_size * scaleOutFactor / 2.0,
									      center[1] + max_size * scaleOutFactor / 2.0 };

	double window_min_dimension = std::min(windowWidth, windowHeight);

	std::array<double, 4> viewport_matrix;
	double viewport_shift_offset = std::abs(windowWidth - windowHeight) / 2;


	if (windowWidth > windowHeight) {
		viewport_matrix = { viewport_shift_offset , 0, window_min_dimension, window_min_dimension };
	}
	else {
		viewport_matrix = { 0, viewport_shift_offset, window_min_dimension, window_min_dimension };
	};

	return Viewport(point_size, orht_matrix, viewport_matrix);
}
