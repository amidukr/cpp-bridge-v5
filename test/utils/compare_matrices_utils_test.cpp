#include <gtest/gtest.h>

#include <Eigen/Dense>

#include "utils/compare_matrices_utils.h"

TEST(CompareMatricesUtilsTest, test_compare) {
	Eigen::Matrix2d matrix_x2_one_1;
	Eigen::Matrix2d matrix_x2_one_2;
	Eigen::Matrix2d matrix_x2_zero_1;

	matrix_x2_one_1 << 1.0, 1.0, 1.0, 1.0;
	matrix_x2_one_2 << 1.0, 1.0, 1.0, 1.0;
	matrix_x2_zero_1 << 0, 0, 0, 0;

	ASSERT_TRUE(compare_matrices(Eigen::Vector2d(1, 1), Eigen::Vector2d(1, 1)));
	ASSERT_TRUE(compare_matrices(matrix_x2_one_1, matrix_x2_one_2));

	ASSERT_FALSE(compare_matrices(Eigen::Vector2d(1, 2), Eigen::Vector2d(1, 1)));
	ASSERT_FALSE(compare_matrices(matrix_x2_one_1, matrix_x2_zero_1));


	ASSERT_FALSE(compare_matrices(Eigen::VectorXd(3), Eigen::VectorXd(2)));
	ASSERT_FALSE(compare_matrices(Eigen::MatrixXd(1, 2), Eigen::MatrixXd(1, 3)));
	ASSERT_FALSE(compare_matrices(Eigen::MatrixXd(2, 1), Eigen::MatrixXd(1, 1)));
}
