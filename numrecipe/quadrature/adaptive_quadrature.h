#pragma once

#include <iostream>
#include <limits>
#include "numrecipe/quadrature/quadrature.h"

namespace numrecipe {
namespace quadrature {

double AdaptiveSimpsonStep(const Integrand& func, const double left,
                           const double right, const double f_left,
                           const double f_middle, const double f_right,
                           const double is, const double to);

double AdaptiveSimpson(const Integrand& func, const double left,
                       const double right, const double tol);

}  // namespace quadrature
}  // namespace numrecipe
