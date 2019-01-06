#include "recipe/linear_algebra/householder.h"
#include <cassert>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include "recipe/linear_algebra/operator_binary.h"
#include "recipe/linear_algebra/base.h"

namespace recipe {
namespace linear_algebra {

void ComputeHouseholderVector(
    const double* vec_x,
    const int size_vec,
    double* householder_vec,
    double* householder_coeff)
{
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
      householder_vec[0] = - sum0 / (vec_x[0] + norm);
    }
    // update coeff
    *householder_coeff = 2.0 * householder_vec[0] * householder_vec[0]
      / (sum0 + householder_vec[0] * householder_vec[0]);
    for (int i = size_vec - 1; i >= 0; --i) {
      householder_vec[i] /= householder_vec[0];
    }
  }
}

std::unique_ptr<double[]> ComputeHouseholderMatrix(
    const double* householder_vec,
    const double householder_coeff,
    const int size)
{
  std::unique_ptr<double[]> mat_data(new double[size * size]);
  for (int row = 0; row < size; ++row) {
    for (int col = 0; col < size; ++col) {
      if (row == col) {
        MATRIX(mat_data, size, row, col) 
          = 1.0 - householder_coeff * householder_vec[row] * householder_vec[col];
      } else {
        MATRIX(mat_data, size, row, col) 
          = - householder_coeff * householder_vec[row] * householder_vec[col];
      }
    }
  }
  return mat_data;
}

void ComputeHouseholderVector(
    const Vector vec_x,
    Vector* householder_vec,
    double* householder_coeff)
{
  const int size = vec_x.Size();
  ComputeHouseholderVector(
      vec_x.Get(), size, householder_vec->Get(), householder_coeff);
}

Matrix ComputeHouseholderMatrix(
    const Vector householder_vec,
    const double householder_coeff)
{
  const int size = householder_vec.Size();
  std::unique_ptr<double[]> data = ComputeHouseholderMatrix(
      householder_vec.Get(), householder_coeff, size);
  return Matrix(size, size, std::move(data));
}

}  // namespace linear_algebra
}  // namespace recipe

