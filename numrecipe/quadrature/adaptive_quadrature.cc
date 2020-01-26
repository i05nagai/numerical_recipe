#include "numrecipe/quadrature/adaptive_quadrature.h"
#include <glog/logging.h>
#include <cmath>
#include <iomanip>
#include <limits>

namespace numrecipe {
namespace quadrature {

double AdaptiveSimpsonStep(const Integrand& func, const double left,
                           const double right, const double f_left,
                           const double f_middle, const double f_right,
                           const double is, double& termination2,
                           const double tol) {
  const double middle = (left + right) / 2.0;
  const double h = (right - left) / 4.0;
  const double left_new = (left + h);
  const double right_new = (right - h);

  const double f_left_new = func(left_new);
  const double f_right_new = func(right_new);
  // S(h)
  const double integral1 = (f_left + 4.0 * f_middle + f_right) * h / 1.5;
  // S(h/2)
  const double integral2 =
      (f_left + 4.0 * (f_left_new + f_right_new) + 2.0 * f_middle + f_right) *
      h / 3.0;
  // romberg extrapolation
  const double integral1_ext = (16.0 * integral2 - integral1) / 15.0;
  if ((is + (integral1_ext - integral2) == is)
      || (middle <= left) || (right <= middle)) {
        if (((middle <= left) || (right <= middle)) && (termination2 == 0)) {
          termination2 = 1.0;
        }
        return integral1_ext;
      }
      else {
        return (AdaptiveSimpsonStep(func, left, middle, f_left, f_left_new,
                                    f_middle, is, termination2, tol) +
                AdaptiveSimpsonStep(func, middle, right, f_middle, f_right_new,
                                    f_right, is, termination2, tol));
      }
}

double AdaptiveSimpson(const Integrand& func, const double left,
                       const double right, const double tol) {
  double termination2 = 0.0;
  constexpr double EPS = std::numeric_limits<double>::epsilon();

  const double middle = (left + right) / 2.0;
  const double f_left = func(left);
  const double f_middle = func(middle);
  const double f_right = func(right);

  // monte-carlo estimation
  double sum = (func(left + 0.9501 * (right - left)) +
                func(left + 0.2311 * (right - left)) +
                func(left + 0.6068 * (right - left)) +
                func(left + 0.4860 * (right - left)) +
                func(left + 0.8913 * (right - left)));
  double is = (right - left) * (f_left + f_middle + f_right + sum) / 8.0;
  if (is == 0.0) {
    is = right - left;
  }
  is = is * tol / EPS;
  return AdaptiveSimpsonStep(func, left, right, f_left, f_middle, f_right, is,
                             termination2, tol);
}

}  // namespace quadrature
}  // namespace numrecipe
