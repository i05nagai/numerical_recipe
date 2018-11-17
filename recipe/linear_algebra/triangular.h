#pragma once

namespace recipe {
namespace linear_algebra {
///
/// @brief Solve the equation $Ux = b$ where $U$ is a upper triangular matrix.
///   The solution will be written to the arugment `vector`.
///
/// @param matrix U.
///   The memory layout of the matrix should be row major layout.
/// @param row_size
/// @param col_size
/// @param vector b. The values are overwritten by the solution.
/// @param vector_size
///
void SolveLinearEquationUpperTriangular(const double* matrix,
                                        const int row_size, const int col_size,
                                        double* vector, const int vector_size);

/// @brief Solve the equation $Lx = b$ where $L$ is a lower triangular matrix.
///   The solution will be written to the arugment `vector`.
///
/// @param matrix L.
///   The memory layout of the matrix should be row major layout.
/// @param row_size
/// @param col_size
/// @param vector b. The values are overwritten by the solution.
/// @param vector_size
void SolveLinearEquationLowerTriangular(const double* matrix,
                                        const int row_size, const int col_size,
                                        double* vector, const int vector_size);
}  // namespace linear_algebra
}  // namespace recipe
