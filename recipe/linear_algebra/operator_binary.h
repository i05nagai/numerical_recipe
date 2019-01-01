#pragma once
#include <memory>
#include "recipe/linear_algebra/matrix.h"
#include "recipe/linear_algebra/vector.h"

namespace recipe {
namespace linear_algebra {
std::unique_ptr<double[]> Multiply(const double* mat, const int row_size,
                                   const int col_size, const double* vec);
std::unique_ptr<double[]> Multiply(
    const double* mat_lhs, const int row_size_lhs, const int col_size_lhs,
    const double* mat_rhs, const int row_size_rhs, const int col_size_rhs);

double InnerProduct(const double* vec_lhs, const double* vec_rhs, const int size);

Vector Multiply(const Matrix& mat, const Vector& vec);
Matrix Multiply(const Matrix& mat_lhs, const Matrix& mat_rhs);
}  // namespace linear_algebra
}  // namespace recipe
