#pragma once

#include <iostream>
#include <memory>
#include "recipe/linear_algebra/vector.h"

namespace recipe {
namespace linear_algebra {

/// @brief Matrix class for row majored array.
///
class Matrix {
 private:
  int num_row_;
  int num_col_;
  /// @brief Row majored data.
  std::unique_ptr<double[]> data_;

 public:
  Matrix();
  /// @brief Create matrix without initialization.
  ///
  /// @param num_row
  /// @param num_col
  ///
  Matrix(const int num_row, const int num_col);
  /// @brief
  ///
  /// @param num_row
  /// @param num_col
  /// @param data Row majored matirx data.
  ///
  Matrix(const int num_row, const int num_col, std::unique_ptr<double[]> data);
  Matrix(const Matrix& other);
  Matrix Slice(const int row_from, const int row_to, const int col_from,
               const int col_to) const;
  double operator()(const int row, const int col) const;
  double& operator()(const int row, const int col);
  Matrix& operator=(const Matrix& other);
  bool operator==(const Matrix& other) const;
  double* Get() { return data_.get(); };
  const double* Get() const { return data_.get(); };
  inline int NumRow() const { return num_row_; }
  inline int NumCol() const { return num_col_; }
};

/// @brief assigner must be smalelr than assignee.
///
/// @param assignee
/// @param assigner
/// @param row_offset
/// @param col_offset
///
void AssignMatrix(Matrix* assignee, const Matrix& assigner,
                  const int row_offset, const int col_offset);

/// @brief assigner must be smalelr than assignee.
///
/// @param assignee
/// @param assigner
/// @param row_offset
/// @param col_offset
///
void AssignVector(Matrix* assignee, const Vector& assigner,
                  const int row_offset, const int col_offset);

/// @brief Create matrix from initalizer_list.
///
///
/// Example:
///
/// ```
///   Matrix mat = MakeMatrix({
///     {1, 2, 3},
///     {4, 5, 6},
///     {7, 8, 9},
///   });
/// ```
///
/// @param list
///
/// @return
///
Matrix MakeMatrix(std::initializer_list<std::initializer_list<double>> list);

/// @brief
///
/// @param size row or column size
///
/// @return (size x size) squared matrix
Matrix MakeIdentityMatrix(const int size);

/// @brief
///
/// @param mat matrix $A$.
/// @param vec obtained column vector $v$.
/// @param col_index takes a value from 0 to col_size - 1.
/// @param row_offset takes a value from 0 to row_size - 1.
/// @param row_size matrix row size $m$.
/// @param col_size matrix col size $n$.
///
void GetColumnVector(const double* mat, double* vec, const int col_index,
                     const int row_offset, const int vec_size,
                     const size_t row_size, const size_t col_size);

/// @brief
///
/// @param mat matrix $A$.
/// @param vec obtained column vector $v$.
/// @param row_index takes a value from 0 to col_size - 1.
/// @param col_offset takes a value from 0 to row_size - 1.
/// @param row_size matrix row size $m$.
/// @param col_size matrix col size $n$.
///
void GetRowVector(const double* mat, double* vec, const int row_index,
                  const int col_offset, const int vec_size,
                  const size_t row_size, const size_t col_size);

std::ostream& operator<<(std::ostream& os, const Matrix& target);
}  // namespace linear_algebra
}  // namespace recipe
