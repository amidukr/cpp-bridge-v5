#ifndef __MATRIX_UTILS_H
#define __MATRIX_UTILS_H

class MatrixIndex {
public:
	virtual int get_end_offset() = 0;
};

class ScalarIndex : public MatrixIndex {
	int start;
	int n;

public:
	ScalarIndex(int n);
	ScalarIndex(MatrixIndex& matrix_index, int n);
	ScalarIndex(ScalarIndex& scalar_index);

	int get_end_offset() override;

	int index(int i);
};

class VectorIndex : public MatrixIndex {
	ScalarIndex scalar_index;

public:
	VectorIndex(int n);
	VectorIndex(MatrixIndex&, int n);
	VectorIndex(VectorIndex&);

	int get_end_offset() override;

	int x_index(int i);
	int y_index(int i);
};

#endif __MATRIX_UTILS_H