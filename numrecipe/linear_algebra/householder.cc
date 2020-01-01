#include "numrecipe/linear_algebra/householder.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include "numrecipe/linear_algebra/base.h"
#include "numrecipe/linear_algebra/operator_binary.h"

namespace numrecipe {
namespace linear_algebra {

void ComputeHouseholderVector(const double* vec_x, const int size_vec,
                              double* householder_vec,
                              double* householder_coeff) {
  assert(size_vec > 0);
  const double sum0 = InnerProduct(vec_x + 1, vec_x + 1, size_vec - 1);
  for (int i = 0; i < size_vec; ++i) {
    householder_vec[i] = vec_x[i];
  }

  if (sum0 == 0.0) {
    // x is in span(e1)
    *householder_coeff = 0.0;
  } else {
    const double norm = std::sqrt(vec_x[0] * vec_x[0] + sum0);
    // calculate v1 = x1 - norm(x)
    if (vec_x[0] <= 0.0) {
      householder_vec[0] = vec_x[0] - norm;
    } else {
      householder_vec[0] = -sum0 / (vec_x[0] + norm);
    }
    // update coeff
    *householder_coeff = 2.0 * householder_vec[0] * householder_vec[0] /
                         (sum0 + householder_vec[0] * householder_vec[0]);
    for (int i = size_vec - 1; i >= 0; --i) {
      householder_vec[i] /= householder_vec[0];
    }
  }
}

std::unique_ptr<double[]> ComputeHouseholderMatrix(
    const double* householder_vec, const double householder_coeff,
    const int size) {
  std::unique_ptr<double[]> mat_data(new double[size * size]);
  for (int row = 0; row < size; ++row) {
    for (int col = 0; col < size; ++col) {
      if (row == col) {
        MATRIX(mat_data, size, row, col) = 1.0 - householder_coeff *
                                                     householder_vec[row] *
                                                     householder_vec[col];
      } else {
        MATRIX(mat_data, size, row, col) =
            -householder_coeff * householder_vec[row] * householder_vec[col];
      }
    }
  }
  return mat_data;
}

void ComputeHouseholderVector(const Vector vec_x, Vector* householder_vec,
                              double* householder_coeff) {
  const int size = vec_x.Size();
  ComputeHouseholderVector(vec_x.Get(), size, householder_vec->Get(),
                           householder_coeff);
}

Matrix ComputeHouseholderMatrix(const Vector householder_vec,
                                const double householder_coeff) {
  const int size = householder_vec.Size();
  std::unique_ptr<double[]> data =
      ComputeHouseholderMatrix(householder_vec.Get(), householder_coeff, size);
  return Matrix(size, size, std::move(data));
}

void MultiplyHouseholderMatrixFromLeft(double* mat_a, const int row_size,
                                       const int col_size,
                                       const double* householder_vec,
                                       const double householder_coeff,
                                       const int vec_size) {
  // TODO: Support row_size < col_size
  assert(row_size >= col_size);
  std::unique_ptr<double[]> householder_mat =
      ComputeHouseholderMatrix(householder_vec, householder_coeff, vec_size);
  const int offset = row_size - vec_size;
  // (I - beta vv^{T})
  // A[row_size-vec_size:(row_size-1), col_size-vec_size:(col_size-1)]
  double mat_temp[row_size * col_size];
  for (int row = offset; row < row_size; ++row) {
    for (int col = offset; col < col_size; ++col) {
      double sum = 0.0;
      for (int k = 0; k < vec_size; ++k) {
        sum += (MATRIX(householder_mat, vec_size, row - offset, k) *
                MATRIX(mat_a, col_size, offset + k, col));
      }
      MATRIX(mat_temp, col_size, row, col) = sum;
    }
  }
  for (int row = offset; row < row_size; ++row) {
    for (int col = offset; col < col_size; ++col) {
      MATRIX(mat_a, col_size, row, col) = MATRIX(mat_temp, col_size, row, col);
    }
  }
}

void ComputeHouseholderBidiagonalization(double* mat_a, const int row_size,
                                         const int col_size) {
  // TODO: support row_size < col_size
  assert(row_size >= col_size);
  double vec_col[row_size];
  double vec_row[col_size];
  double householder_vec[row_size];
  double householder_coeff;
  for (int j = 0; j < col_size; ++j) {
    const int vec_col_size = row_size - j;

    GetColumnVector(mat_a, vec_col, j, j, vec_col_size, row_size, col_size);
    ComputeHouseholderVector(vec_col, vec_col_size, householder_vec,
                             &householder_coeff);

    MultiplyHouseholderMatrixFromLeft(mat_a, row_size, col_size,
                                      householder_vec, householder_coeff,
                                      vec_col_size);
    // assign householder vector to A
    for (int row = j + 1; row < row_size; ++row) {
      MATRIX(mat_a, col_size, row, j) = householder_vec[row - j];
    }

    if (j < col_size - 2) {
      const int vec_row_size = col_size - (j + 1);
      GetRowVector(mat_a, vec_row, j, j + 1, vec_row_size, row_size, col_size);
      ComputeHouseholderVector(vec_row, vec_row_size, householder_vec,
                               &householder_coeff);

      //   (I - beta vv^{T})
      std::unique_ptr<double[]> householder_mat = ComputeHouseholderMatrix(
          householder_vec, householder_coeff, vec_row_size);

      // A[row_size-vec_size:(row_size-1), col_size-vec_size:(col_size-1)]
      // * (I - beta vv^{T})
      double mat_temp[row_size * vec_row_size];
      for (int row = 0; row < row_size - j; ++row) {
        for (int col = 0; col < vec_row_size; ++col) {
          double sum = 0.0;
          for (int k = 0; k < vec_row_size; ++k) {
            sum += (MATRIX(mat_a, col_size, row + j,
                           (col_size - vec_row_size) + k) *
                    MATRIX(householder_mat, vec_row_size, k, col));
          }
          MATRIX(mat_temp, vec_row_size, row, col) = sum;
        }
      }
      for (int row = 0; row < row_size - j; ++row) {
        for (int col = 0; col < vec_row_size; ++col) {
          MATRIX(mat_a, col_size + j, row + j, col + col_size - vec_row_size) =
              MATRIX(mat_temp, vec_row_size, row, col);
        }
      }

      // assign householder vector to A
      for (int col = j + 2; col < col_size; ++col) {
        MATRIX(mat_a, col_size, j, col) = householder_vec[col - (j + 1)];
      }
    }
  }
}

std::unique_ptr<double[]> ConvertHouseholderBidiagonalizationToB(
    const double* mat_a, const int row_size, const int col_size) {
  // TODO(i05nagai): Support row_size < col_size
  assert(row_size >= col_size);
  std::unique_ptr<double[]> data(new double[row_size * col_size]);
  std::fill(data.get(), data.get() + row_size * col_size, 0.0);
  // because row_size >= col_size
  for (int col = 0; col < col_size; ++col) {
    MATRIX(data, col_size, col, col) = MATRIX(mat_a, col_size, col, col);
    if (col < col_size - 1) {
      MATRIX(data, col_size, col, col + 1) =
          MATRIX(mat_a, col_size, col, col + 1);
    }
  }
  return data;
}

}  // namespace linear_algebra
}  // namespace numrecipe
