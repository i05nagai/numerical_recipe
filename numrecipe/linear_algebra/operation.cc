#include "numrecipe/linear_algebra/operation.h"
#include <memory>
#include "numrecipe/linear_algebra/base.h"

namespace numrecipe {
namespace linear_algebra {
// Calculate Ax + y
std::unique_ptr<double[]> MatrixTimesVectorPlusVector(const double* mat_a,
                                                      const int row_size,
                                                      const int col_size,
                                                      const double* vec_x,
                                                      const double* vec_y) {
  std::unique_ptr<double[]> data(new double[row_size]);
  // The size of x is col_size
  // The size of y is row_size
  for (int row = 0; row < row_size; ++row) {
    data[row] = vec_y[row];
    for (int col = 0; col < col_size; ++col) {
      data[row] += MATRIX(mat_a, col_size, row, col) * vec_x[col];
    }
  }
  return data;
}

// Calculate Ax - y
std::unique_ptr<double[]> MatrixTimesVectorMinusVector(const double* mat_a,
                                                       const int row_size,
                                                       const int col_size,
                                                       const double* vec_x,
                                                       const double* vec_y) {
  std::unique_ptr<double[]> data(new double[row_size]);
  // The size of x is col_size
  // The size of y is row_size
  for (int row = 0; row < row_size; ++row) {
    data[row] = -vec_y[row];
    for (int col = 0; col < col_size; ++col) {
      data[row] += MATRIX(mat_a, col_size, row, col) * vec_x[col];
    }
  }
  return data;
}

// Calculate -Ax + y
std::unique_ptr<double[]> MinusMatrixTimesVectorPlusVector(
    const double* mat_a, const int row_size, const int col_size,
    const double* vec_x, const double* vec_y) {
  std::unique_ptr<double[]> data(new double[row_size]);
  // The size of x is col_size
  // The size of y is row_size
  for (int row = 0; row < row_size; ++row) {
    data[row] = vec_y[row];
    for (int col = 0; col < col_size; ++col) {
      data[row] -= MATRIX(mat_a, col_size, row, col) * vec_x[col];
    }
  }
  return data;
}

Vector MinusMatrixTimesVectorPlusVector(Matrix* mat_a, Vector* vec_x,
                                        Vector* vec_y) {
  const int row_size = mat_a->NumRow();
  const int col_size = mat_a->NumCol();
  std::unique_ptr<double[]> data = MinusMatrixTimesVectorPlusVector(
      mat_a->Get(), row_size, col_size, vec_x->Get(), vec_y->Get());
  return Vector(row_size, std::move(data));
}
}  // namespace linear_algebra
}  // namespace numrecipe
