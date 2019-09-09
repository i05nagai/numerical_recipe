#include "recipe/core/core.h"
#include "recipe/quadrature/quadrature.h"
#include "recipe/quadrature/change_variable.h"
#include <cassert>
#include <cmath>
#include <iostream>

namespace recipe {
namespace quadrature {

//
// Double Exponential
//

double QuadratureDoubleExponentialFinite(
    const Integrand& integrand, const int num_partition, const double length) {
  double sum = 0.0;

  for (int i = -num_partition + 1; i < num_partition; i++) {
    const double factor = RECIPE_PI * 0.5 * std::sinh(i * length);
    const double denom = std::cosh(factor) * std::cosh(factor);
    sum += (integrand(std::tanh(factor)) * std::cosh(i * length) / denom);
  }
  sum *= RECIPE_PI * 0.5 * length;
  return sum;
}

double QuadratureDoubleExponentialFinite(
    const Integral& integral, const int num_partition, const double length) {
  return QuadratureDoubleExponentialFinite(integral.GetIntegrand(), num_partition, length);
}

double QuadratureDoubleExponentialHalf(
    const Integrand& integrand, const int num_partition, const double length) {
  double sum = 0.0;

  for (int i = -num_partition + 1; i < num_partition; i++) {
    const double factor = std::exp(RECIPE_PI * 0.5 * std::sinh(i * length));
    sum += integrand(factor) * std::cosh(i * length) * factor;
  }
  sum *= RECIPE_PI * 0.5 * length;
  return sum;
}

double QuadratureDoubleExponentialHalf(
    const Integral& integral, const int num_partition, const double length) {
  return QuadratureDoubleExponentialHalf(integral.GetIntegrand(), num_partition, length);
}

double QuadratureDoubleExponentialInfinite(
    const Integrand& integrand, const int num_partition, const double length) {
  double sum = 0.0;

  for (int i = -num_partition + 1; i < num_partition; i++) {
    const double factor = RECIPE_PI * 0.5 * std::sinh(i * length);
    sum += integrand(std::sinh(factor)) * std::cosh(i * length) * std::cosh(factor);
  }
  sum *= RECIPE_PI * 0.5 * length;
  return sum;
}

double QuadratureDoubleExponentialInfinite(
    const Integral& integral, const int num_partition, const double length) {
  return QuadratureDoubleExponentialInfinite(integral.GetIntegrand(), num_partition, length);
}

//
// Trapezoidal
//

double TrapezoidalRuleStep(
    const Integrand& integrand,
    const double step_size,
    const int num_step,
    const double step_from) {
  double integral = 0.0;
  for (int i = 0; i < num_step; i++) {
    integral += integrand(step_from + step_size * i);
  }

  return step_size * integral;
}

double TrapezoidalRuleOpenDegree2(
    const Integrand& integrand,
    const double left,
    const double right,
    const unsigned int num_of_partition) {
  assert(num_of_partition >= 3);
  assert(left <= right);
  assert(std::isfinite(left) && std::isfinite(right));
  const double h = (right - left) / num_of_partition;
  // calculate endpoints
  double integral = (integrand(right - h) + integrand(left + h)) * 3.0 / 2.0;

  for (size_t i = 2; i <= num_of_partition - 2; i++) {
    integral += integrand(left + i * h);
  }

  return h * integral;
}

double TrapezoidalRuleOpenDegree5(
    const Integrand& integrand,
    const double left,
    const double right,
    const unsigned int num_of_partition) {
  assert(num_of_partition >= 5);
  assert(left <= right);
  assert(std::isfinite(left) && std::isfinite(right));
  const double h = (right - left) / num_of_partition;
  // calculate endpoints
  double integral = (
      integrand(left + h) * 55.0 / 24.0
      - integrand(left + 2.0 * h) / 6.0
      + integrand(left + 3.0 * h) * 11.0 / 8.0
      + integrand(right - 3.0 * h) * 11.0 / 8.0
      - integrand(right - 2.0 * h) * 1.0 / 6.0
      + integrand(right - 1.0 * h) * 55.0 / 24.0);

  for (size_t i = 3; i <= num_of_partition - 4; i++) {
    integral += integrand(left + i * h);
  }

  return h * integral;
}

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
