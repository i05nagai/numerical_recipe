#include "recipe/linear_algebra/operator_unary.h"
#include <cmath>

namespace recipe {
namespace linear_algebra {
double NormEuclid(const double* vec, const int size) {
  double sum = 0.0;
  for (int i = 0; i < size; ++i) {
    sum += vec[i] * vec[i];
  }
  return std::sqrt(sum);
  ;
}
}  // namespace linear_algebra
}  // namespace recipe
