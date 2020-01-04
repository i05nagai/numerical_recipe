#pragma once
#include "numrecipe/linear_algebra/vector.h"

namespace numrecipe {
namespace linear_algebra {
double NormEuclid(const double* vec, const int size);
double NormEuclid(const Vector vec);
std::unique_ptr<double[]> Transpose(const double* mat, const int row_size,
                                    const int col_size);
}  // namespace linear_algebra
}  // namespace numrecipe
