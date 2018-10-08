#include "recipe/sandbox/linear_algebra/matrix.h"
#include <cassert>
#include <iostream>

namespace recipe {
namespace sandbox {
namespace linear_algebra {

Matrix::Matrix(const int nrow, const int ncol)
    : nrow_(nrow), ncol_(ncol), data_(new double[nrow * ncol]) {
  for (int i = 0; i < nrow_ * ncol_; i++) data_[i] = 0;
}

Matrix::Matrix(const Matrix& m)
    : nrow_(m.nrow_), ncol_(m.ncol_), data_(new double[m.nrow_ * m.ncol_]) {
  for (int i = 0; i < m.nrow_ * m.ncol_; i++) data_[i] = m.data_[i];
}

Matrix::~Matrix() { delete[] data_; }

double Matrix::operator()(int i, int j) const {
  assert(0 <= i && i < nrow_ && 0 <= j && j < ncol_);
  return data_[i * ncol_ + j];
}

double& Matrix::operator()(int i, int j) {
  assert(0 <= i && i < nrow_ && 0 <= j && j < ncol_);
  return data_[i * ncol_ + j];
}

Matrix& Matrix::operator=(const Matrix& m) {
  nrow_ = m.nrow_;
  ncol_ = m.ncol_;
  data_ = new double[nrow_ * ncol_];

  for (int i = 0; i < nrow_; i++) {
    for (int j = 0; j < ncol_; j++) {
      data_[i * ncol_ + j] = m.data_[i * ncol_ + j];
    }
  }

  return *this;
}

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe
