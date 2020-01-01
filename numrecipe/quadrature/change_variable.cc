#include "numrecipe/quadrature/change_variable.h"
#include <iostream>
#include "numrecipe/core/core.h"

namespace numrecipe {
namespace quadrature {

Integral ChangeVariableFiniteToMinusOnePlusOne(const Integrand integrand,
                                               const double left,
                                               const double right) {
  const Integrand integnrad_new = [integrand, left, right](const double t) {
    const double factor = (right - left) / 2.0;
    const double x = factor * (t + (right + left) / (right - left));
    const double derivative = factor;
    const double val = integrand(x) * derivative;
    return val;
  };
  double left_new = -1.0;
  double right_new = 1.0;
  return Integral(integnrad_new, left_new, right_new);
}

}  // namespace quadrature
}  // namespace numrecipe
