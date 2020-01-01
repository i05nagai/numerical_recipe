#pragma once
#include <vector>
#include "numrecipe/linear_algebra/matrix.h"
#include "numrecipe/linear_algebra/operation.h"
#include "numrecipe/linear_algebra/vector.h"

namespace numrecipe {
namespace linear_algebra {

/// @brief Solve $LUx=b$ with respect to $x$. The solution will be overwritten
///
/// @param mat_lu $LU$ matrix obtained
///   as a result of `GaussianEliminationOuterProductBandDiagonal`
///   or other LU decomposition algorithms.
///   `mat_lu` must be squared matrix.
/// @param mat_size row or column length of `mat_lu`.
/// @param vec_b $b$.
///
void SolveLinearEquationWithLU(const double* mat_lu, const int mat_size,
                               double* vec_b);
}  // namespace linear_algebra
}  // namespace numrecipe
