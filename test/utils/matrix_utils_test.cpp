#include <gtest/gtest.h>

#include "utils/matrix_utils.h"



TEST(MatrixUtilsTest, test_scalar) {
	ScalarIndex scalar_index1 { 3 };
	ScalarIndex scalar_index2{ scalar_index1, 4 };
	ScalarIndex scalar_copy2 { scalar_index2 };

	ASSERT_EQ(scalar_index1.index(0), 0);
	ASSERT_EQ(scalar_index1.index(1), 1);
	ASSERT_EQ(scalar_index1.index(2), 2);

	ASSERT_EQ(scalar_index2.index(0), 3);
	ASSERT_EQ(scalar_index2.index(1), 4);
	ASSERT_EQ(scalar_index2.index(2), 5);
	ASSERT_EQ(scalar_index2.index(3), 6);

	ASSERT_EQ(scalar_copy2.index(0), 3);
	ASSERT_EQ(scalar_copy2.index(1), 4);
	ASSERT_EQ(scalar_copy2.index(2), 5);
	ASSERT_EQ(scalar_copy2.index(3), 6);

	ASSERT_EQ(scalar_index1.get_end_offset(), 3);
	ASSERT_EQ(scalar_index2.get_end_offset(), 7);
	ASSERT_EQ(scalar_copy2.get_end_offset(), 7);

	try {
		scalar_index1.index(3);
		FAIL();
	}catch (...) {}

	try {
		scalar_index2.index(4);
		FAIL();
	}catch (...) {}

	try {
		scalar_copy2.index(4);
		FAIL();
	}
	catch (...) {}
}

TEST(MatrixUtilsTest, test_vector) {
	VectorIndex vector_index1{ 3 };
	VectorIndex vector_index2{ vector_index1, 4 };
	VectorIndex vector_copy2{ vector_index2 };

	ASSERT_EQ(vector_index1.x_index(0), 0);
	ASSERT_EQ(vector_index1.y_index(0), 1);
	ASSERT_EQ(vector_index1.x_index(1), 2);
	ASSERT_EQ(vector_index1.y_index(1), 3);
	ASSERT_EQ(vector_index1.x_index(2), 4);
	ASSERT_EQ(vector_index1.y_index(2), 5);

	ASSERT_EQ(vector_index2.x_index(0), 6);
	ASSERT_EQ(vector_index2.y_index(0), 7);
	ASSERT_EQ(vector_index2.x_index(1), 8);
	ASSERT_EQ(vector_index2.y_index(1), 9);
	ASSERT_EQ(vector_index2.x_index(2), 10);
	ASSERT_EQ(vector_index2.y_index(2), 11);
	ASSERT_EQ(vector_index2.x_index(3), 12);
	ASSERT_EQ(vector_index2.y_index(3), 13);

	ASSERT_EQ(vector_copy2.x_index(0), 6);
	ASSERT_EQ(vector_copy2.y_index(0), 7);
	ASSERT_EQ(vector_copy2.x_index(1), 8);
	ASSERT_EQ(vector_copy2.y_index(1), 9);
	ASSERT_EQ(vector_copy2.x_index(2), 10);
	ASSERT_EQ(vector_copy2.y_index(2), 11);
	ASSERT_EQ(vector_copy2.x_index(3), 12);
	ASSERT_EQ(vector_copy2.y_index(3), 13);

	
	ASSERT_EQ(vector_index1.get_end_offset(), 6);
	ASSERT_EQ(vector_index2.get_end_offset(), 14);
	ASSERT_EQ(vector_copy2.get_end_offset(), 14);

	try {
		vector_index1.x_index(3);
		FAIL();
	}
	catch (...) {}

	try {
		vector_index2.x_index(4);
		FAIL();
	}
	catch (...) {}

	try {
		vector_copy2.x_index(4);
		FAIL();
	}
	catch (...) {}
}

TEST(MatrixUtilsTest, test_scalar_vector) {
	ScalarIndex scalar_index1{ 5 };
	VectorIndex vector_index2{ scalar_index1, 2 };
	ScalarIndex scalar_index3{ vector_index2, 2 };

	ASSERT_EQ(scalar_index1.index(0), 0);
	ASSERT_EQ(scalar_index1.index(1), 1);
	ASSERT_EQ(scalar_index1.index(2), 2);
	ASSERT_EQ(scalar_index1.index(3), 3);
	ASSERT_EQ(scalar_index1.index(4), 4);

	ASSERT_EQ(vector_index2.x_index(0), 5);
	ASSERT_EQ(vector_index2.y_index(0), 6);
	ASSERT_EQ(vector_index2.x_index(1), 7);
	ASSERT_EQ(vector_index2.y_index(1), 8);

	ASSERT_EQ(scalar_index3.index(0), 9);
	ASSERT_EQ(scalar_index3.index(1), 10);

	ASSERT_EQ(scalar_index1.get_end_offset(), 5);
	ASSERT_EQ(vector_index2.get_end_offset(), 9);
	ASSERT_EQ(scalar_index3.get_end_offset(), 11);

	try {
		scalar_index1.index(5);
		FAIL();
	}
	catch (...) {}

	try {
		vector_index2.y_index(2);
		FAIL();
	}
	catch (...) {}

	try {
		scalar_index3.index(2);
		FAIL();
	}
	catch (...) {}
}
