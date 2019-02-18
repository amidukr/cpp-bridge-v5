#include <gtest/gtest.h>

#include "utils/compare_matrices_utils.h"
#include "utils/matrix_equation.h"

TEST(MatrixEquationTest, test_equation_defaults) {
	MatrixEquation equation{ 3, ScalarIndex{3} };

	Eigen::MatrixXd left_expected(3, 3);
	Eigen::VectorXd righ_expected(3);

	left_expected.setZero();
	righ_expected.setZero();

	compare_matrices(equation.get_left(), left_expected);

	ASSERT_EQ(equation.get_left().rows(), 3);
	ASSERT_EQ(equation.get_left().cols(), 3);
	ASSERT_EQ(equation.get_right().size(), 3);

	ASSERT_TRUE(compare_matrices(equation.get_left(), left_expected));
	ASSERT_TRUE(compare_matrices(equation.get_right(), righ_expected));
}

TEST(MatrixEquationTest, test_solve) {
	ScalarIndex index1{ 1 };
	ScalarIndex index2{ index1, 2 };

	MatrixEquation equation{ 4, index2 };

	equation.get_left() <<
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;

	equation.get_right() <<
		5,
		6,
		7,
		8;

	equation.solve();

	ASSERT_EQ(equation.get_indexed_root_scalar(0), 6);
	ASSERT_EQ(equation.get_indexed_root_scalar(1), 7);

	ASSERT_EQ(equation.get_indexed_root_vector(0), Eigen::Vector2d(6, 7));
}
