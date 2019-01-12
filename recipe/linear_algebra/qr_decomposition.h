#pragma once
#include <vector>
#include "recipe/linear_algebra/matrix.h"
#include "recipe/linear_algebra/vector.h"

namespace recipe {
namespace linear_algebra {

/// @brief Compute Householder QR decomposition.
///  Matrix $A$ is overwritten by the algorithm.
///  If you need matrix $Q$ and $R$, use
///  @ref ConvertHouseholderQRToQ(
///  const double*, const double*, const int, const int)
/// "ConvertHouseholderQRToQ" and
///  @ref ConvertHouseholderQRToR(
///  const double*, const double*, const int, const int)
/// "ConvertHouseholderQRToR".
///
/// @param mat_a matrix $A$. $A$ is overwritten.
/// @param row_size
/// @param col_size
///
/// @return A lit of Householder vectors used to compute $Q$.
///
std::unique_ptr<double[]> ComputeHouseholderQR(double* mat_a,
                                               const int row_size,
                                               const int col_size);

/// @brief Extract a orthonomal $Q$ and a upper triangular matrix $R$ from
/// the resutl of
/// @ref ComputeHouseholderQR(double*, const int, const int)
/// "ComputeHouseholderQR".
/// TODO: Currently, the function support `row_size >= col_size`.
///
/// @param mat_qr the results of decomposing function. See
/// `ComputeHouseholderQR`.
/// @param householder_coeffs
/// @param row_size num of rows of `mat_qr`.
/// @param col_size num of rows of `mat_qr`.
///
/// @return
///
std::unique_ptr<double[]> ConvertHouseholderQRToQ(
    const double* mat_qr, const double* householder_coeffs, const int row_size,
    const int col_size);

std::unique_ptr<double[]> ConvertHouseholderQRToR(
    const double* mat_qr, const double* householder_coeffs, const int row_size,
    const int col_size);

/// @brief Extract a orthonomal $Q$ and a upper triangular matrix $R$ from
/// the resutl of
/// @ref ComputeHouseholderQR(double*, const int, const int)
/// "ComputeHouseholderQR".
/// TODO: Currently, the function support `row_size >= col_size`.
///
/// @param mat_qr the results of decomposing function. See
/// `ComputeHouseholderQR`.
/// @param householder_coeffs
/// @param row_size num of rows of `mat_qr`.
/// @param col_size num of rows of `mat_qr`.
///
/// @return the first of the pair is $Q$. the second is `R`.
///
std::pair<std::unique_ptr<double[]>, std::unique_ptr<double[]>>
ConvertHouseholderQRToQR(const double* mat_qr, const double* householder_coeffs,
                         const int row_size, const int col_size);

}  // namespace linear_algebra
}  // namespace recipe
