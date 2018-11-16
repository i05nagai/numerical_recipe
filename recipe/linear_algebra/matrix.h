#pragma once

#include <iostream>
#include <memory>

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
  double operator()(const int row, const int col) const;
  double& operator()(const int row, const int col);
  Matrix& operator=(const Matrix& other);
  bool operator==(const Matrix& other) const;
  double* Get() { return data_.get(); };
  inline int NumRow() const { return num_row_; }
  inline int NumCol() const { return num_col_; }
};

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

std::ostream& operator<<(std::ostream& os, const Matrix& target);
}  // namespace linear_algebra
}  // namespace recipe
