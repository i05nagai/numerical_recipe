#pragma once
#include <memory>
#include "recipe/linear_algebra/matrix.h"
#include "recipe/linear_algebra/vector.h"

namespace recipe {
namespace linear_algebra {
/// @brief Compute $Ax$, multiplication of a matrix and a vector.
///   
///
/// @param mat matrix $A$.
/// @param row_size
/// @param col_size
/// @param vec vector $x$.
///
/// @return $Ax$
/// 
std::unique_ptr<double[]> Multiply(const double* mat, const int row_size,
                                   const int col_size, const double* vec);
/// @brief Compute $AB$, multiplication of two matrice.
///
/// @param mat_lhs $A$
/// @param row_size_lhs
/// @param col_size_lhs
/// @param mat_rhs $B$
/// @param row_size_rhs
/// @param col_size_rhs
///
/// @return $AB$.
///
std::unique_ptr<double[]> Multiply(
    const double* mat_lhs, const int row_size_lhs, const int col_size_lhs,
    const double* mat_rhs, const int row_size_rhs, const int col_size_rhs);

/// @brief Compute $A^{\\mathrm{T}}B$, multiplication of two matrice.
///
/// @param mat_lhs matrix $A$
/// @param row_size_lhs
/// @param col_size_lhs
/// @param mat_rhs matrix $B$
/// @param row_size_rhs
/// @param col_size_rhs
///
/// @return matrix $A^{\\mathrm{T}}B$.
///
std::unique_ptr<double[]> MultiplyLeftTranspose(
    const double* mat_lhs, const int row_size_lhs, const int col_size_lhs,
    const double* mat_rhs, const int row_size_rhs, const int col_size_rhs);

double InnerProduct(const double* vec_lhs, const double* vec_rhs, const int size);

Vector Multiply(const Matrix& mat, const Vector& vec);
Matrix Multiply(const Matrix& mat_lhs, const Matrix& mat_rhs);
}  // namespace linear_algebra
}  // namespace recipe
