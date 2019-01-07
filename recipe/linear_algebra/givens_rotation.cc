#include "recipe/linear_algebra/givens_rotation.h"
#include "recipe/linear_algebra/base.h"
#include <cassert>
#include <cmath>

namespace recipe {
namespace linear_algebra {

std::pair<double, double>
ComputeGivensRotationParameters(const double val1, const double val2)
{
  if (val2 == 0.0) {
    // already rotated
    return std::make_pair(1.0, 0.0);
  } else {
    if (val2 > val1) {
      const double factor = - val1 / val2;
      const double sin_term = 1.0 / std::sqrt(1.0 + factor * factor);
      const double cos_term = sin_term * factor;
      return std::make_pair(cos_term, sin_term);
    } else {
      const double factor = - val2 / val1;
      const double cos_term = 1.0 / std::sqrt(1.0 + factor * factor);
      const double sin_term = cos_term * factor;
      return std::make_pair(cos_term, sin_term);
    }
  }
}

void MultiplyGivensRotation(
    const int givens_index1,
    const int givens_index2,
    const std::pair<double, double>& givens_params,
    double* mat_a,
    const int row_size,
    const int col_size)
{
  assert(0 <= givens_index1 && givens_index1 < givens_index2);
  assert(givens_index2 < row_size);
  for (int col = 0; col < col_size; ++col) {
    const double elem1 = MATRIX(mat_a, col_size, givens_index1, col);
    const double elem2 = MATRIX(mat_a, col_size, givens_index2, col);
    MATRIX(mat_a, col_size, givens_index1, col)
      = givens_params.first * elem1 - givens_params.second * elem2;
    MATRIX(mat_a, col_size, givens_index2, col)
      = givens_params.second * elem1 + givens_params.first * elem2;
  }
}

void MultiplyGivensRotation(
    double* mat_a,
    const int row_size,
    const int col_size,
    const int givens_index1,
    const int givens_index2,
    const std::pair<double, double>& givens_params)
{
  assert(0 <= givens_index1 && givens_index1 < givens_index2);
  assert(givens_index2 < col_size);
  for (int row = 0; row < row_size; ++row) {
    const double elem1 = MATRIX(mat_a, col_size, row, givens_index1);
    const double elem2 = MATRIX(mat_a, col_size, row, givens_index2);
    MATRIX(mat_a, col_size, row, givens_index1)
      = givens_params.first * elem1 - givens_params.second * elem2;
    MATRIX(mat_a, col_size, row, givens_index2)
      = givens_params.second * elem1 + givens_params.first * elem2;
  }
}

}  // namespace linear_algebra
}  // namespace recipe


