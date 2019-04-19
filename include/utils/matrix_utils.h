#ifndef __MATRIX_UTILS_H
#define __MATRIX_UTILS_H

class MatrixIndex {
public:
	virtual int get_end_offset() const = 0;
	virtual ~MatrixIndex();
};

class ScalarIndex : public MatrixIndex {
	int start;
	int n;

public:
	ScalarIndex(int n);
	ScalarIndex(const MatrixIndex& matrix_index, int n);
	ScalarIndex(const ScalarIndex& scalar_index);

	int get_end_offset() const override;

	int index(int i);
};

class VectorIndex : public MatrixIndex {
	ScalarIndex scalar_index;

public:
	VectorIndex(int n);
	VectorIndex(const MatrixIndex&, int n);
	VectorIndex(const VectorIndex&);

	int get_end_offset() const override;

	int x_index(int i);
	int y_index(int i);

	const ScalarIndex& to_scalar_index() const;
};

#endif /*__MATRIX_UTILS_H*/
