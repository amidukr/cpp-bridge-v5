#include<gtest/gtest.h>

#include "utils/viewport_utils.h"

TEST(ViewportTest, test_ortho_matrix) {
	Viewport viewport1 = ViewportUtil::calculate_viewport(100, 200, 0, 0, 50, 50, 2.0);
	Viewport viewport2 = ViewportUtil::calculate_viewport(800, 900, 0, 0, 50, 50, 4.0);
	Viewport viewport3 = ViewportUtil::calculate_viewport(200, 100, 0, 0, 20, 50, 2.0);
	Viewport viewport4 = ViewportUtil::calculate_viewport(100, 200, 0, 0, 50, 20, 2.0);

	std::array<double, 4> orhto_matrix1 = viewport1.get_ortho_matrix();
	std::array<double, 4> orhto_matrix2 = viewport2.get_ortho_matrix();
	std::array<double, 4> orhto_matrix3 = viewport3.get_ortho_matrix();
	std::array<double, 4> orhto_matrix4 = viewport4.get_ortho_matrix();

	ASSERT_EQ(orhto_matrix1[0], -25);
	ASSERT_EQ(orhto_matrix1[1],  75);
	ASSERT_EQ(orhto_matrix1[2], -25);
	ASSERT_EQ(orhto_matrix1[3],  75);

	ASSERT_EQ(orhto_matrix2[0], -75);
	ASSERT_EQ(orhto_matrix2[1], 125);
	ASSERT_EQ(orhto_matrix2[2], -75);
	ASSERT_EQ(orhto_matrix2[3], 125);

	ASSERT_EQ(orhto_matrix3[0], -40);
	ASSERT_EQ(orhto_matrix3[1], 60);
	ASSERT_EQ(orhto_matrix3[2], -25);
	ASSERT_EQ(orhto_matrix3[3], 75);

	ASSERT_EQ(orhto_matrix4[0], -25);
	ASSERT_EQ(orhto_matrix4[1],  75);
	ASSERT_EQ(orhto_matrix4[2], -40);
	ASSERT_EQ(orhto_matrix4[3],  60);
}

TEST(ViewportTest, test_viewport) {
	Viewport viewport1 = ViewportUtil::calculate_viewport(100, 100, 0, 0, 20, 20, 2.0);
	Viewport viewport2 = ViewportUtil::calculate_viewport(200, 100, 0, 0, 20, 20, 2.0);
	Viewport viewport3 = ViewportUtil::calculate_viewport(100, 200, 0, 0, 20, 20, 2.0);
	Viewport viewport4 = ViewportUtil::calculate_viewport(200, 1000, 0, 0, 20, 20, 2.0);

	std::array<double, 4> viewport_matrix1 = viewport1.get_viewport_matrix();
	std::array<double, 4> viewport_matrix2 = viewport2.get_viewport_matrix();
	std::array<double, 4> viewport_matrix3 = viewport3.get_viewport_matrix();
	std::array<double, 4> viewport_matrix4 = viewport4.get_viewport_matrix();

	ASSERT_EQ(viewport_matrix1[0], 0);
	ASSERT_EQ(viewport_matrix1[1], 0);
	ASSERT_EQ(viewport_matrix1[2], 100);
	ASSERT_EQ(viewport_matrix1[3], 100);

	ASSERT_EQ(viewport_matrix2[0], 50);
	ASSERT_EQ(viewport_matrix2[1], 0);
	ASSERT_EQ(viewport_matrix2[2], 100);
	ASSERT_EQ(viewport_matrix2[3], 100);

	ASSERT_EQ(viewport_matrix3[0], 0);
	ASSERT_EQ(viewport_matrix3[1], 50);
	ASSERT_EQ(viewport_matrix3[2], 100);
	ASSERT_EQ(viewport_matrix3[3], 100);

	ASSERT_EQ(viewport_matrix4[0], 0);
	ASSERT_EQ(viewport_matrix4[1], 400);
	ASSERT_EQ(viewport_matrix4[2], 200);
	ASSERT_EQ(viewport_matrix4[3], 200);
}