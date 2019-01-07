#pragma once
#include <utility>

namespace recipe {
namespace linear_algebra {

/// @brief Compute $c$ and $s$ which satisfy
///
/// $$
/// \\left(
///     \\begin{array}{cc}
///         c & s \\\\\
///         -s & c
///     \\end{array}
/// \\right)^{\\mathrm{T}}
/// \\left(
///     \\begin{array}{c}
///         a \\\\\
///         b
///     \\end{array}
///  \\right)
///  =
///  \\left(
///      \\begin{array}{c}
///          r \\\\\
///          0
///      \\end{array}
///  \\right)
///  .
///  $$
///
/// @param val1 value $a$
/// @param val2 value $b$
///
/// @return values $c$ and $s$.
/// 
std::pair<double, double>
ComputeGivensRotationParameters(const double val1, const double val2);

/// @brief Multiply Givens rotations from left to $A$. Compute $G(i, j, c, s)^{\\mathrm{T}}A$.
///
/// @param givens_index1 Givens rotation position $i$.
/// @param givens_index2 Givens rotation position $j$. Must be $i < j$.
/// @param givens_params Givens rotation parameter $(c, s)$.
/// @param mat_a matrix $A$. Overwritten by $G(i, j, c, s)A$.
/// @param row_size
/// @param col_size
/// 
void MultiplyGivensRotation(
    const int givens_index1,
    const int givens_index2,
    const std::pair<double, double>& givens_params,
    double* mat_a,
    const int row_size,
    const int col_size);

/// @brief Multiply Givens rotations from right to $A$. Compute $AG(i, j, c, s)$.
///
/// @param mat_a matrix $A$. Overwritten by $AG(i, j, c, s)$.
/// @param row_size
/// @param col_size
/// @param givens_index1 Givens rotation position $i$.
/// @param givens_index2 Givens rotation position $j$. Must be $i < j$.
/// @param givens_params Givens rotation parameter $(c, s)$.
/// 
void MultiplyGivensRotation(
    double* mat_a,
    const int row_size,
    const int col_size,
    const int givens_index1,
    const int givens_index2,
    const std::pair<double, double>& givens_params);
}  // namespace linear_algebra
}  // namespace recipe
