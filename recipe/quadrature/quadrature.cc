#include "recipe/quadrature/quadrature.h"
#include <cassert>

namespace recipe {
namespace quadrature {

double TrapezoidalRule(double (*f)(double), const double a, const double b,
                       const int num_of_partition) {
  assert(a < b);
  const double h = (b - a) / num_of_partition;
  // calculate endpoints
  double integral = (f(b) + f(a)) / 2.0;

  for (int i = 1; i < num_of_partition; i++) {
    integral += f(a + i * h);
  }

  return h * integral;
}

}  // namespace quadrature
}  // namespace recipe
