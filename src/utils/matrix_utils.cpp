#include "utils/matrix_utils.h"

MatrixIndex::~MatrixIndex() {

}

ScalarIndex::ScalarIndex(int n) {
	this->start = 0;
	this->n = n;
}

ScalarIndex::ScalarIndex(const MatrixIndex& matrix_index, int n) {
	this->start = matrix_index.get_end_offset();
	this->n = n;
}

ScalarIndex::ScalarIndex(const ScalarIndex& scalar_index) {
	this->start = scalar_index.start;
	this->n = scalar_index.n;
}

int ScalarIndex::get_end_offset() const {
	return this->start + this->n;
}

int ScalarIndex::index(int i) {
	if (i < 0 || i >= this->n) {
		throw "Index out of bound";
	}

	return this->start + i;
}

VectorIndex::VectorIndex(const VectorIndex& vector_index)
	: scalar_index(vector_index.scalar_index)
{
	
}

VectorIndex::VectorIndex(int n)
	: scalar_index(2*n)
{}

VectorIndex::VectorIndex(const MatrixIndex& matrix_index, int n)
	: scalar_index(matrix_index, 2*n)
{}

int VectorIndex::x_index(int i) {
	return this->scalar_index.index(2 * i);
}

int VectorIndex::y_index(int i) {
	return this->scalar_index.index(2 * i + 1);
}

int VectorIndex::get_end_offset() const {
	return this->scalar_index.get_end_offset();
}

const ScalarIndex& VectorIndex::to_scalar_index() const {
	return this->scalar_index;
}
