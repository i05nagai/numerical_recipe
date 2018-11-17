#include "recipe/linear_algebra/matrix.h"
#include <algorithm>
#include <cassert>
#include <iostream>

namespace recipe {
namespace linear_algebra {

Matrix::Matrix(const int num_row, const int num_col,
               std::unique_ptr<double[]> data)
    : num_row_(num_row), num_col_(num_col), data_(std::move(data)) {}

Matrix::Matrix(const int num_row, const int num_col)
    : num_row_(num_row),
      num_col_(num_col),
      data_(new double[num_row * num_col]) {}

Matrix::Matrix(const Matrix& other)
    : num_row_(other.num_row_),
      num_col_(other.num_col_),
      data_(new double[other.num_row_ * other.num_col_]) {
  std::copy(other.data_.get(), other.data_.get() + num_row_ * num_col_,
            data_.get());
}

double Matrix::operator()(const int row, const int col) const {
  assert(0 <= row && row < num_row_ && 0 <= col && col < num_col_);
  return data_[row * num_col_ + col];
}

double& Matrix::operator()(const int row, const int col) {
  assert(0 <= row && row < num_row_ && 0 <= col && col < num_col_);
  return data_[row * num_col_ + col];
}

Matrix& Matrix::operator=(const Matrix& other) {
  num_row_ = other.num_row_;
  num_col_ = other.num_col_;
  data_ = std::unique_ptr<double[]>(new double[num_row_ * num_col_]);
  std::copy(other.data_.get(), other.data_.get() + num_row_ * num_col_,
            data_.get());
  return *this;
}

bool Matrix::operator==(const Matrix& other) const {
  if ((num_row_ != other.num_row_) || (num_col_ != other.num_col_)) {
    return false;
  }
  return std::equal(data_.get(), data_.get() + num_row_ * num_col_,
                    other.data_.get());
}

Matrix MakeMatrix(std::initializer_list<std::initializer_list<double>> list) {
  const int size_row = list.size();
  if (size_row == 0) {
    return Matrix(0, 0);
  }
  const int size_col = list.begin()->size();
  std::unique_ptr<double[]> data(new double[size_col * size_row]);
  int index = 0;
  for (auto&& row : list) {
    for (auto&& col : row) {
      data[index++] = col;
    }
  }
  return Matrix(size_row, size_col, std::move(data));
}

Matrix MakeIdentityMatrix(const int size) {
  std::unique_ptr<double[]> data(new double[size * size]);
  std::fill(data.get(), data.get() + size * size, 0.0);
  for (int i = 0; i < size; i++) {
    data[i * size + i] = 1.0;
  }
  return Matrix(size, size, std::move(data));
}

std::ostream& operator<<(std::ostream& os, const Matrix& target) {
  for (int row = 0; row < target.NumRow(); ++row) {
    for (int col = 0; col < target.NumCol(); ++col) {
      os << target(row, col) << ", ";
    }
    os << std::endl;
  }
  return os;
}

}  // namespace linear_algebra
}  // namespace recipe
