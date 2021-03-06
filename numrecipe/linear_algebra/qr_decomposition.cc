#include "numrecipe/linear_algebra/qr_decomposition.h"
#include <cassert>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include "numrecipe/linear_algebra/base.h"
#include "numrecipe/linear_algebra/householder.h"
#include "numrecipe/linear_algebra/operator_binary.h"
#include "numrecipe/linear_algebra/util.h"

namespace numrecipe {
namespace linear_algebra {

//
// HouseholderQR
//

std::unique_ptr<double[]> ComputeHouseholderQR(double* mat_a,
                                               const int row_size,
                                               const int col_size) {
  assert(row_size >= col_size);
  // to compute Q explicitly, coeffscients and householder vectors are necessary
  std::unique_ptr<double[]> householder_coeffs(new double[col_size]);
  double householder_vec[row_size];
  double vec_col[row_size];

  for (int j = 0; j < col_size; ++j) {
    const int vec_size = row_size - j;
    householder_coeffs[j] = 0.0;
    // compute householder vector
    GetColumnVector(mat_a, vec_col, j, j, vec_size, row_size, col_size);
    ComputeHouseholderVector(vec_col, vec_size, householder_vec,
                             &householder_coeffs[j]);
    // compute householder matrix
    std::unique_ptr<double[]> householder_mat = ComputeHouseholderMatrix(
        householder_vec, householder_coeffs[j], vec_size);

    // (I - beta vv^{T}) A[j:(row_size-1), j:(col_size-1)]
    double mat_temp[row_size * col_size];
    for (int row = j; row < row_size; ++row) {
      for (int col = j; col < col_size; ++col) {
        double sum = 0.0;
        for (int k = 0; k < vec_size; ++k) {
          sum += (MATRIX(householder_mat, vec_size, row - j, k) *
                  MATRIX(mat_a, col_size, j + k, col));
        }
        MATRIX(mat_temp, col_size, row, col) = sum;
      }
    }
    for (int row = j; row < row_size; ++row) {
      for (int col = j; col < col_size; ++col) {
        MATRIX(mat_a, col_size, row, col) =
            MATRIX(mat_temp, col_size, row, col);
      }
    }

    // store householder vector to mat_a
    if (j < col_size - 1) {
      for (int row = j + 1; row < row_size; ++row) {
        MATRIX(mat_a, col_size, row, j) = householder_vec[row - j];
      }
    }
  }

  return householder_coeffs;
}

std::unique_ptr<double[]> ConvertHouseholderQRToR(
    const double* mat_qr, const double* householder_coeffs, const int row_size,
    const int col_size) {
  std::unique_ptr<double[]> mat_r(new double[row_size * col_size]);
  std::fill(mat_r.get(), mat_r.get() + row_size * col_size, 0.0);

  // R
  for (int row = 0; row < row_size; ++row) {
    for (int col = row; col < col_size; ++col) {
      MATRIX(mat_r, col_size, row, col) = MATRIX(mat_qr, col_size, row, col);
    }
  }
  return mat_r;
}

std::unique_ptr<double[]> ConvertHouseholderQRToQ(
    const double* mat_qr, const double* householder_coeffs, const int row_size,
    const int col_size) {
  // TODO(i05nagai): Support row_size < col_size
  assert(row_size >= col_size);
  // Q^{factor}
  const int q_col_size = row_size;
  std::unique_ptr<double[]> mat_q(new double[row_size * q_col_size]);
  for (int row = 0; row < row_size; ++row) {
    for (int col = 0; col < row_size; ++col) {
      if (row == col) {
        MATRIX(mat_q, q_col_size, row, col) = 1.0;
      } else {
        MATRIX(mat_q, q_col_size, row, col) = 0.0;
      }
    }
  }
  double householder_vec[row_size];
  const int factor = col_size;
  for (int j = factor - 1; j >= 0; --j) {
    const int vec_size = row_size - j;
    // extract householder vector
    householder_vec[0] = 1.0;
    for (int row = 1; row < vec_size; ++row) {
      householder_vec[row] = MATRIX(mat_qr, col_size, row + j, j);
    }
    // (I - beta vv^{T}) Q(j:n, j:n)
    std::unique_ptr<double[]> householder_mat = ComputeHouseholderMatrix(
        householder_vec, householder_coeffs[j], vec_size);

    double mat_q_temp[vec_size * vec_size];
    for (int row = 0; row < vec_size; ++row) {
      for (int col = 0; col < vec_size; ++col) {
        double sum = 0.0;
        for (int k = 0; k < vec_size; ++k) {
          sum += (MATRIX(householder_mat, vec_size, row, k) *
                  MATRIX(mat_q, q_col_size, j + k, col + j));
        }
        MATRIX(mat_q_temp, vec_size, row, col) = sum;
      }
    }
    for (int row = 0; row < vec_size; ++row) {
      for (int col = 0; col < vec_size; ++col) {
        MATRIX(mat_q, q_col_size, row + j, col + j) =
            MATRIX(mat_q_temp, vec_size, row, col);
      }
    }
  }
  return mat_q;
}

std::pair<std::unique_ptr<double[]>, std::unique_ptr<double[]>>
ConvertHouseholderQRToQR(const double* mat_qr, const double* householder_coeffs,
                         const int row_size, const int col_size) {
  std::unique_ptr<double[]> mat_r =
      ConvertHouseholderQRToR(mat_qr, householder_coeffs, row_size, col_size);
  std::unique_ptr<double[]> mat_q =
      ConvertHouseholderQRToQ(mat_qr, householder_coeffs, row_size, col_size);
  return std::make_pair(std::move(mat_q), std::move(mat_r));
}

//
// GivensQR
//

}  // namespace linear_algebra
}  // namespace numrecipe
