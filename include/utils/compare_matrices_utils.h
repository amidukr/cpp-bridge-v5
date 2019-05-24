#ifndef __COMPARE_MATRICES_UTILS_H
#define __COMPARE_MATRICES_UTILS_H

#include <iostream>

template <class M> bool compare_matrices(const M& actual, const M& expected) {

	bool approx = actual.rows() == expected.rows() && actual.cols() == expected.cols();
	approx = approx && actual.isApprox(expected, 0.00001);

	if (!approx) {
		std::cout << actual << std::endl << "doesn't equal to expected" << std::endl << expected << std::endl;

		if (actual.rows() == expected.rows() && actual.cols() == expected.cols()) {
			std::cout << "difference is following: " << std::endl << (expected - actual) << std::endl;
		}
		else {
			std::cout << "difference in matrix sizes" << std::endl;
		}

	}

	return approx;
}

#endif /*__COMPARE_MATRICES_UTILS_H*/