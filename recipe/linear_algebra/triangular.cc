#include "recipe/linear_algebra/triangular.h"
#include "recipe/linear_algebra/base.h"

namespace recipe {
namespace linear_algebra {

void SolveLinearEquationUpperTriangular(const double* matrix,
                                        const int row_size, const int col_size,
                                        double* vector, const int vector_size) {
  // Solve Ux=vector with respect to x
  for (int row = row_size - 1; row >= 0; --row) {
    double sum = 0.0;
    for (int col = col_size - 1; col > row; --col) {
      sum += MATRIX(matrix, col_size, row, col) * vector[col];
    }
    vector[row] = (vector[row] - sum) / MATRIX(matrix, col_size, row, row);
  }
}

void SolveLinearEquationLowerTriangular(const double* matrix,
                                        const int row_size, const int col_size,
                                        double* vector, const int vector_size) {
  // Solve Lx=vector with respect to x
  for (int row = 0; row < row_size; ++row) {
    double sum = 0.0;
    for (int col = 0; col < row; ++col) {
      sum += MATRIX(matrix, col_size, row, col) * vector[col];
    }
    vector[row] = (vector[row] - sum) / MATRIX(matrix, col_size, row, row);
  }
}
}  // namespace linear_algebra
}  // namespace recipe
