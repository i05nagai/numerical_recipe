#include "recipe/linear_algebra/operator_binary.h"
#include <cassert>
#include "recipe/linear_algebra/base.h"
#include "recipe/linear_algebra/operator_unary.h"

namespace recipe {
namespace linear_algebra {
std::unique_ptr<double[]> Multiply(const double* mat, const int row_size,
                                   const int col_size, const double* vec) {
  std::unique_ptr<double[]> data(new double[row_size]);
  for (int row = 0; row < row_size; ++row) {
    data[row] = 0.0;
    for (int col = 0; col < col_size; ++col) {
      data[row] += MATRIX(mat, col_size, row, col) * vec[col];
    }
  }
  return data;
}

std::unique_ptr<double[]> Multiply(
    const double* mat_lhs, const int row_size_lhs, const int col_size_lhs,
    const double* mat_rhs, const int row_size_rhs, const int col_size_rhs) {
  assert(col_size_lhs == row_size_rhs);
  std::unique_ptr<double[]> data(new double[row_size_lhs * col_size_rhs]);
  for (int row = 0; row < row_size_lhs; ++row) {
    for (int col = 0; col < col_size_rhs; ++col) {
      MATRIX(data, col_size_rhs, row, col) = 0.0;
      for (int k = 0; k < col_size_lhs; ++k) {
        MATRIX(data, col_size_rhs, row, col) +=
            MATRIX(mat_lhs, col_size_lhs, row, k) *
            MATRIX(mat_rhs, col_size_rhs, k, col);
      }
    }
  }
  return data;
}

std::unique_ptr<double[]> MultiplyLeftTranspose(
    const double* mat_lhs, const int row_size_lhs, const int col_size_lhs,
    const double* mat_rhs, const int row_size_rhs, const int col_size_rhs) {
  std::unique_ptr<double[]> mat_lhs_transposed =
      Transpose(mat_lhs, row_size_lhs, col_size_lhs);
  const int row_size_lhs_t = col_size_lhs;
  const int col_size_lhs_t = row_size_lhs;
  return Multiply(mat_lhs_transposed.get(), row_size_lhs_t, col_size_lhs_t,
                  mat_rhs, row_size_rhs, col_size_rhs);
}

double InnerProduct(const double* vec_lhs, const double* vec_rhs,
                    const int size) {
  double sum = 0.0;
  for (int i = 0; i < size; ++i) {
    sum += vec_lhs[i] * vec_rhs[i];
  }
  return sum;
}

Vector Multiply(const Matrix& mat, const Vector& vec) {
  assert(mat.NumRow() == vec.Size());
  const int row_size = mat.NumRow();
  const int col_size = mat.NumCol();
  std::unique_ptr<double[]> data =
      Multiply(mat.Get(), row_size, col_size, vec.Get());
  return Vector(row_size, std::move(data));
}

Matrix Multiply(const Matrix& mat_lhs, const Matrix& mat_rhs) {
  std::unique_ptr<double[]> data =
      Multiply(mat_lhs.Get(), mat_lhs.NumRow(), mat_lhs.NumCol(), mat_rhs.Get(),
               mat_rhs.NumRow(), mat_rhs.NumCol());
  return Matrix(mat_lhs.NumRow(), mat_rhs.NumCol(), std::move(data));
}

}  // namespace linear_algebra
}  // namespace recipe
