#include "recipe/linear_algebra/lu_decomposition.h"
#include <cassert>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include "recipe/linear_algebra/triangular.h"

namespace recipe {
namespace linear_algebra {

//
// Solve Linear Equations
//

void SolveLinearEquationWithLU(const double* mat_lu, const int mat_size,
                               double* vec_b) {
  // Solve Ly=b with respect to y
  for (int row = 0; row < mat_size; ++row) {
    double sum = 0.0;
    for (int col = 0; col < row; ++col) {
      sum += MATRIX(mat_lu, mat_size, row, col) * vec_b[col];
    }
    vec_b[row] = (vec_b[row] - sum);
  }

  // Solve Ux=y w.r.t. x
  SolveLinearEquationUpperTriangular(mat_lu, mat_size, mat_size, vec_b,
                                     mat_size);
}

}  // namespace linear_algebra
}  // namespace recipe
