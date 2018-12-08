#pragma once

#include <memory>
#include "recipe/linear_algebra/base.h"
#include "recipe/linear_algebra/matrix.h"
#include "recipe/linear_algebra/vector.h"

namespace recipe {
namespace linear_algebra {
// Calculate Ax + y
std::unique_ptr<double[]> MatrixTimesVectorPlusVector(const double* mat_a,
                                                      const int row_size,
                                                      const int col_size,
                                                      const double* vec_x,
                                                      const double* vec_y);

// Calculate Ax - y
std::unique_ptr<double[]> MatrixTimesVectorMinusVector(const double* mat_a,
                                                       const int row_size,
                                                       const int col_size,
                                                       const double* vec_x,
                                                       const double* vec_y);

// Calculate -Ax + y
std::unique_ptr<double[]> MinusMatrixTimesVectorPlusVector(const double* mat_a,
                                                           const int row_size,
                                                           const int col_size,
                                                           const double* vec_x,
                                                           const double* vec_y);

Vector MinusMatrixTimesVectorPlusVector(Matrix* mat_a, Vector* vec_x,
                                        Vector* vec_y);
}  // namespace linear_algebra
}  // namespace recipe
