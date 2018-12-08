#include "recipe/linear_algebra/band_diagonal.h"
#include <memory>
#include "recipe/linear_algebra/lu_decomposition.h"

namespace recipe {
namespace linear_algebra {

//
// GaussianEliminationOuterProductBandDiagonal
//

void GaussianEliminationOuterProductBandDiagonal(double* mat,
                                                 const int mat_size,
                                                 const int upper_band,
                                                 const int lower_band) {
  // matrix should be band diagonal matrix
  for (int k = 0; k < mat_size - 1; ++k) {
    // elimiate k-th row
    for (int row = k + 1; row < std::min(k + lower_band + 1, mat_size); ++row) {
      MATRIX(mat, mat_size, row, k) /= MATRIX(mat, mat_size, k, k);
    }

    for (int row = k + 1; row < std::min(k + lower_band + 1, mat_size); ++row) {
      for (int col = k + 1; col < std::min(k + upper_band + 1, mat_size);
           ++col) {
        MATRIX(mat, mat_size, row, col) -=
            MATRIX(mat, mat_size, row, k) * MATRIX(mat, mat_size, k, col);
      }
    }
  }
}

void GaussianEliminationOuterProductBandDiagonal(double* mat,
                                                 const int mat_size,
                                                 const int band_size) {
  GaussianEliminationOuterProductBandDiagonal(mat, mat_size, band_size,
                                              band_size);
}

//
// Solve Linear Equations
//

// void SolveLinearEquationWithLU(const double* mat_lu, const int mat_size,
//                                double* vec_b) {
//   // Solve Ly=b with respect to y
//   for (int row = 0; row < mat_size; ++row) {
//     double sum = 0.0;
//     for (int col = 0; col < row; ++col) {
//       sum += MATRIX(mat_lu, mat_size, row, col) * vec_b[col];
//     }
//     vec_b[row] = (vec_b[row] - sum);
//   }
//
//   // Solve Ux=y w.r.t. x
//   SolveLinearEquationUpperTriangular(mat_lu, mat_size, mat_size, vec_b,
//                                      mat_size);
// }

void SolveLinearEquationBandDiagonal(double* mat, const int mat_size,
                                     const int upper_band, const int lower_band,
                                     double* vec_b) {
  // the size of vector must be matrix_size
  GaussianEliminationOuterProductBandDiagonal(mat, mat_size, upper_band,
                                              lower_band);
  // LU
  SolveLinearEquationWithLU(mat, mat_size, vec_b);
}

}  // namespace linear_algebra
}  // namespace recipe
