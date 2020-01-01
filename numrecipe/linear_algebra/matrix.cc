#include "numrecipe/linear_algebra/matrix.h"
#include <algorithm>
#include <cassert>
#include <iostream>

namespace numrecipe {
namespace linear_algebra {

Matrix::Matrix() : num_row_(0), num_col_(0), data_(nullptr) {}

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

Matrix Matrix::Slice(const int row_from, const int row_to, const int col_from,
                     const int col_to) const {
  assert(0 <= row_from && row_from <= row_to && row_to < num_row_);
  assert(0 <= col_from && col_from <= col_to && col_to < num_col_);

  const int row_size = (row_to - row_from + 1);
  const int col_size = (col_to - col_from + 1);
  Matrix sliced(row_size, col_size);
  for (int row = row_from; row <= row_to; ++row) {
    for (int col = col_from; col <= col_to; ++col) {
      sliced(row - row_from, col - col_from) = this->operator()(row, col);
    }
  }
  return sliced;
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

//
// Free functions
//

void AssignMatrix(Matrix* assignee, const Matrix& assigner,
                  const int row_offset, const int col_offset) {
  assert(0 <= row_offset && row_offset < assignee->NumRow());
  assert(0 <= col_offset && col_offset < assignee->NumCol());

  assert(assigner.NumRow() + row_offset <= assignee->NumRow());
  assert(assigner.NumCol() + col_offset <= assignee->NumCol());
  for (int row = 0; row < assigner.NumRow(); ++row) {
    for (int col = 0; col < assigner.NumCol(); ++col) {
      (*assignee)(row + row_offset, col + col_offset) = assigner(row, col);
    }
  }
}

void AssignVector(Matrix* assignee, const Vector& assigner,
                  const int row_offset, const int col_offset) {
  assert(0 <= row_offset && row_offset < assignee->NumRow());
  assert(0 <= col_offset && col_offset < assignee->NumCol());

  assert(assigner.Size() + row_offset <= assignee->NumCol());
  for (int row = 0; row < assigner.Size(); ++row) {
    (*assignee)(row + row_offset, col_offset) = assigner(row);
  }
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

void GetColumnVector(const double* mat, double* vec, const int col_index,
                     const int row_offset, const int vec_size,
                     const size_t row_size, const size_t col_size) {
  // row_size(mat) - row_offset >= vec_size
  // col_index in [0, col_size(mat))
  // row_offset in [0, row_size(mat))
  assert(0 <= row_offset && row_offset < row_size);
  assert(0 <= col_index && col_index < col_size);
  assert(vec_size <= (row_size - row_offset));
  for (int row = 0; row < vec_size; ++row) {
    vec[row] = mat[(row_offset + row) * col_size + col_index];
  }
}

void GetRowVector(const double* mat, double* vec, const int row_index,
                  const int col_offset, const int vec_size,
                  const size_t row_size, const size_t col_size) {
  // col_size(mat) - col_offset >= vec_size
  // row_index in [0, row_size(mat))
  // col_offset in [0, col_size(mat))
  assert(0 <= col_offset && col_offset < col_size);
  assert(0 <= row_index && row_index < row_size);
  assert(vec_size <= (col_size - col_offset));
  for (int col = 0; col < vec_size; ++col) {
    vec[col] = mat[row_index * col_size + col + col_offset];
  }
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
}  // namespace numrecipe
