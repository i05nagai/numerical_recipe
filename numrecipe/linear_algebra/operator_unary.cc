#include "numrecipe/linear_algebra/operator_unary.h"
#include <cmath>
#include "numrecipe/linear_algebra/base.h"

namespace numrecipe {
namespace linear_algebra {
double NormEuclid(const double* vec, const int size) {
  double sum = 0.0;
  for (int i = 0; i < size; ++i) {
    sum += vec[i] * vec[i];
  }
  return std::sqrt(sum);
}

double NormEuclid(const Vector vec) {
  return NormEuclid(vec.Get(), vec.Size());
}

std::unique_ptr<double[]> Transpose(const double* mat, const int row_size,
                                    const int col_size) {
  std::unique_ptr<double[]> data(new double[row_size * col_size]);
  for (int row = 0; row < row_size; ++row) {
    for (int col = 0; col < col_size; ++col) {
      MATRIX(data, row_size, col, row) = MATRIX(mat, col_size, row, col);
    }
  }
  return data;
}
}  // namespace linear_algebra
}  // namespace numrecipe
