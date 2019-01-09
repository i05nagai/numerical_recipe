#pragma once
#include <vector>
#include "recipe/linear_algebra/matrix.h"
#include "recipe/linear_algebra/vector.h"

namespace recipe {
namespace linear_algebra {

/// @brief
///
/// `col_index` is 0 and `row_offset` is 2.
///
/// $$
/// \left(
///     \begin{array}{ccccc}
///         a_{0}^{0}   & a_{1}^{0} & \cdots &        & a_{0}^{n-1}
///         \\
///         a_{0}^{1}   &           &        & \cdots & \vdots
///         \\
///         \vdots      &           &        & \ddots &
///         \\
///                     & \vdots    & \ddots & \ddots &
///         \\
///         a_{m-1}^{0} & \cdots    &        &        & a_{m-1}^{n-1}
///     \end{array}
/// \right)
/// $$
///
/// $$
/// v
/// =
/// \left(
///     \begin{array}{c}
///         a_{c_{0}}^{r_{0}}
///         \\
///         \vdots
///         \\
///         a_{c_{0}}^{r_{0} + }
///     \end{array}
/// \right)
/// $$
///
/// @param mat_a
/// @param row_size
/// @param col_size
///
/// @return
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
