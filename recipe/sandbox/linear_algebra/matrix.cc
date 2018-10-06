#include "recipe/sandbox/linear_algebra/matrix.h"
#include <iostream>

namespace recipe {
namespace sandbox {
namespace linear_algebra {

Matrix::Matrix(const int nrows, const int ncols) {
  nrow = nrows;
  ncol = ncols;
  data = new double[nrow * ncol];

  for (int i = 0; i < nrow * ncol; i++) data[i] = 0;
}

Matrix::Matrix(const Matrix& m)
    : nrow(m.nrow), ncol(m.ncol), data(new double[m.nrow * m.ncol]) {
  for (int i = 0; i < m.nrow * m.ncol; i++) data[i] = m.data[i];
}

Matrix::~Matrix() { delete[] data; }

double Matrix::operator()(int i, int j) const { return data[i * ncol + j]; }

double& Matrix::operator()(int i, int j) { return data[i * ncol + j]; }

Matrix& Matrix::operator=(const Matrix& m) {
  nrow = m.nrow;
  ncol = m.ncol;
  data = new double[nrow * ncol];

  for (int i = 0; i < nrow; i++) {
    for (int j = 0; j < ncol; j++) {
      data[i * ncol + j] = m.data[i * ncol + j];
    }
  }

  return *this;
}

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe
