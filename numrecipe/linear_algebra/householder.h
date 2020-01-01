#pragma once
#include <vector>
#include "numrecipe/linear_algebra/matrix.h"
#include "numrecipe/linear_algebra/util.h"
#include "numrecipe/linear_algebra/vector.h"

namespace numrecipe {
namespace linear_algebra {

/// @brief Compute Householder Vector of vec_x.
/// Calcualte $v$ and $\\beta$ which satisfy
///
/// $$
///   (I - \\beta vv^{\mathrm{T}})x
///   =
///   \\|x\\|_{2} e_{1}
/// $$
///
/// where $(e_{i})$ is a standard basis of euclid space
/// and $v = (1, v^{2}, \\ldots, v^{2})$.
///
/// @param vec_x vector $x$.
/// @param size_vec size of vector $x$ and $v$.
/// @param householder_vec Householder vector $v$.
/// @param householder_coeff Householder coefficient $\\beta$.
///
void ComputeHouseholderVector(const double* vec_x, const int size_vec,
                              double* householder_vec,
                              double* householder_coeff);

/// @brief Compute Householder matrix
///
/// $$
///   (I - \\beta vv^{\\mathrm{T}})
/// $$
///
/// where $\\beta := 2 / \\|v\\|_{2}^{2}$ and $v$ is a householder vectror.
///
/// @param householder_vec Householder vector $v$
/// @param householder_coeff coefficient of Householder transformation $\\beta$.
/// @param size the size of vector $v$.
///
/// @return array of matrix $M$ whose values are stored in row majored order.
///
std::unique_ptr<double[]> ComputeHouseholderMatrix(
    const double* householder_vec, const double householder_coeff,
    const int size);

void ComputeHouseholderVector(const Vector vec_x, Vector* householder_vec,
                              double* householder_coeff);

Matrix ComputeHouseholderMatrix(const Vector householder_vec,
                                const double householder_coeff);

/// @brief
///
///
/// @param mat_a
/// @param row_size
/// @param col_size
/// @param householder_vec
/// @param householder_coeff
/// @param vec_size
///
void MultiplyHouseholderMatrixFromLeft(double* mat_a, const int row_size,
                                       const int col_size,
                                       const double* householder_vec,
                                       const double householder_coeff,
                                       const int vec_size);

/// @brief
///
/// @param mat_a
/// @param row_size
/// @param col_size
///
void ComputeHouseholderBidiagonalization(double* mat_a, const int row_size,
                                         const int col_size);

// TODO(i05naga): not implemented yet
std::unique_ptr<double[]> ConvertHouseholderBidiagonalizationToU(
    const double* mat_a, const int row_size, const int col_size);
// TODO(i05naga): not implemented yet
std::unique_ptr<double[]> ConvertHouseholderBidiagonalizationToV(
    const double* mat_a, const int row_size, const int col_size);
/// @brief Extract the bidiagonal matrix $B$ from the result of
/// `ComputeHouseholderBidiagonalization`.
///
/// @param mat_a
/// @param row_size
/// @param col_size
///
std::unique_ptr<double[]> ConvertHouseholderBidiagonalizationToB(
    const double* mat_a, const int row_size, const int col_size);

}  // namespace linear_algebra
}  // namespace numrecipe
