#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include "recipe/linear_algebra/base.h"
#include "recipe/linear_algebra/operation.h"
#include "recipe/linear_algebra/operator_unary.h"
#include "recipe/linear_algebra/util.h"

namespace recipe {
namespace linear_algebra {
/// @brief
///
/// $$
///   \left(
///       \begin{array}{ccccc}
///           u_{1}^{1}   &           & \cdots & u_{n}^{1}   & u_{n}^{1}
///           \\
///           l_{1}^{2}   & u_{2}^{2} &        & \cdots      & \vdots
///           \\
///           \vdots      &           &        & \ddots      &
///           \\
///           l_{1}^{n-1} & \vdots    & \ddots & \ddots      & u_{n}^{n-1}
///           \\
///           l_{1}^{n}   & \cdots    &        & l_{n-1}^{n} & u_{n}^{n}
///       \end{array}
///   \right)
/// $$
///
/// @param mat squared matrix. The result of LU decomposition stored in `mat`.
/// @param mat_size the number of rows and cols.
/// @param upper_band
/// @param lower_band
///
void GaussianEliminationOuterProductBandDiagonal(double* mat,
                                                 const int mat_size,
                                                 const int upper_band,
                                                 const int lower_band);

/// @brief LU decomposition for a band diagonal matrix
/// whose upper band and lower band has the same size
void GaussianEliminationOuterProductBandDiagonal(double* mat,
                                                 const int mat_size,
                                                 const int band_size);

/// Solve $Ax=b$ where $A$ is a squared matrix whose length of rows is
/// `mat_size`
void SolveLinearEquationBandDiagonal(double* mat, const int mat_size,
                                     const int upper_band, const int lower_band,
                                     double* vec_b);
}  // namespace linear_algebra
}  // namespace recipe
