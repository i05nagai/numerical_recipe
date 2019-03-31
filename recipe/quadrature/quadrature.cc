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

double SimpsonRule(double (*f)(double), const double a, const double b,
                   const int num_of_partition) {
  assert(a < b);
  // step size h is divided by 2 because Simpson's rule is Newton-Cotes method
  // of degree two.
  const double h = (b - a) / (2.0 * num_of_partition);
  // calculate endpoints
  double integral = (f(b) + f(a));

  for (int i = 1; i < num_of_partition; i++) {
    integral += (4.0 * f(a + (2.0 * i - 1.0) * h) + 2.0 * f(a + 2.0 * i * h));
  }
  integral += 4.0 * f(a + (2.0 * num_of_partition - 1.0) * h);

  return integral * h / 3.0;
}

}  // namespace quadrature
}  // namespace recipe
