#ifndef __MATRIX_EQUATION_HEADER
#define __MATRIX_EQUATION_HEADER

#include <Eigen/Dense>

#include "utils/matrix_utils.h"


class MatrixEquation {
	Eigen::MatrixXd left;
	Eigen::VectorXd right;
	ScalarIndex root_indices;
	Eigen::VectorXd matrix_roots;

public:
	MatrixEquation(int n, const ScalarIndex& root_indices);

	Eigen::MatrixXd& get_left();
	Eigen::VectorXd& get_right();

	void solve();

	double get_indexed_root_scalar(int i);
	Eigen::Vector2d get_indexed_root_vector(int i);
};

#endif // __MATRIX_EQUATION_HEADER