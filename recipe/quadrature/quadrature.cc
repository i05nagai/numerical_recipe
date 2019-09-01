#include "recipe/core/core.h"
#include "recipe/quadrature/quadrature.h"
#include "recipe/quadrature/change_variable.h"
#include <cassert>
#include <cmath>
#include <iostream>

namespace recipe {
namespace quadrature {

// double QuadratureImproper(
//     const Integrand& integrand, const double left, const double right,
//     const unsigned int num_partition) {
//   assert(left <= right);
// 
//   Integral integral;
//   // TODO: Criteria for choosing appropriate variable transformation
//   if (std::isinf(left) && right * left > 0) {
//     integral = ChangeVariableInverse(integrand, left, right);
//   } else if (std::isinf(right) && right * left > 0) {
//     integral = ChangeVariableInverse(integrand, left, right);
//   } else if (IsChangeVariablePowerLaw(integrand, left, right)) {
//     integral = ChangeVariablePowerLawLeft(integrand, left, right);
//   } else if (0 <= left && right < RECIPE_DOUBLE_INF) {
//     // if left point is singularity
//     double left_new = left;
//     if (std::isnan(integrand(left)) && std::isfinite(left) && std::isfinite(right)) {
//       left_new += (right - left) / num_partition;
//     }
//   } else if (-RECIPE_DOUBLE_INF < left && right < RECIPE_DOUBLE_INF) {
//     integral = ChangeVariableDoubleExponential(integrand, left, right);
//   } else {
//     integral = ChangeVariableMixed(integrand, left, right);
//   }
//   return TrapezoidalRuleOpenOrder2(
//       integral.Integrand(), integral.Left(), integral.Right(), num_partition);
// }

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
