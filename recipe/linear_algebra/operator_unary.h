#pragma once
#include "recipe/linear_algebra/vector.h"

namespace recipe {
namespace linear_algebra {
double NormEuclid(const double* vec, const int size);
double NormEuclid(const Vector vec);
}  // namespace linear_algebra
}  // namespace recipe
