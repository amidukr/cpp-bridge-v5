#include "utils/matrix_equation.h"

MatrixEquation::MatrixEquation(int n, const ScalarIndex& root_indices) 
	: root_indices(root_indices)
{
	this->left = Eigen::MatrixXd(n, n);
	this->right = Eigen::VectorXd(n);
	this->matrix_roots = Eigen::VectorXd(0);

	this->left.setZero();
	this->right.setZero();
}

Eigen::MatrixXd& MatrixEquation::get_left() {
	return this->left;
}

Eigen::VectorXd& MatrixEquation::get_right() {
	return this->right;
}

void MatrixEquation::solve() {
	if (this->right.size() != 0) {
		this->matrix_roots = this->left.colPivHouseholderQr().solve(this->right);
	}
}

double MatrixEquation::get_indexed_root_scalar(int i) {
	return this->matrix_roots(this->root_indices.index(i));
}

Eigen::Vector2d MatrixEquation::get_indexed_root_vector(int i) {
	return Eigen::Vector2d(this->get_indexed_root_scalar(2 * i), this->get_indexed_root_scalar(2 * i + 1));
}
