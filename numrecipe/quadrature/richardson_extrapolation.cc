#include "numrecipe/quadrature/richardson_extrapolation.h"
#include <cassert>
#include <cmath>
#include "numrecipe/quadrature/quadrature.h"

namespace numrecipe {
namespace quadrature {

double RichardsonExtrapolation(QuadratureRule quadrature_rule,
                               double (*integrand)(double),
                               double left_endpoint, double right_endpoint,
                               unsigned int num_of_partition) {
  assert(left_endpoint < right_endpoint);

  double approximator_of_half_step_size =
      0;  // richardson extrapolation uses the approximation value of a half
          // step size.
  double approximator_of_normal_step_size =
      0;  // the approximation value of a normal step size.
  unsigned int approx_order = 0;

  switch (quadrature_rule) {
    case Trapezoidal: {
      approx_order = 2;
      approximator_of_normal_step_size = numrecipe::quadrature::TrapezoidalRule(
          integrand, left_endpoint, right_endpoint, num_of_partition);
      approximator_of_half_step_size = numrecipe::quadrature::TrapezoidalRule(
          integrand, left_endpoint, right_endpoint, 2 * num_of_partition);
      break;
    }
    case Simpson: {
      approx_order = 4;
      approximator_of_normal_step_size = numrecipe::quadrature::SimpsonRule(
          integrand, left_endpoint, right_endpoint, num_of_partition);
      approximator_of_half_step_size = numrecipe::quadrature::SimpsonRule(
          integrand, left_endpoint, right_endpoint, 2 * num_of_partition);
      break;
    }
    default: { assert("An undefined quadrature rule was specified."); }
  }
  return (std::pow(2.0, approx_order) * approximator_of_half_step_size -
          approximator_of_normal_step_size) /
         (pow(2.0, approx_order) - 1.0);
};
}  // namespace quadrature
}  // namespace numrecipe
