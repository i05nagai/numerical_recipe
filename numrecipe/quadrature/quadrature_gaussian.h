#pragma once

#include "numrecipe/quadrature/quadrature.h"
#include "numrecipe/quadrature/quadrature_gaussian.h"

namespace numrecipe {
namespace quadrature {
///@brief Gauss-Legendre quadrature with 5 points.
/// Weights and abscissas are taken from
/// Lowan, A. N., Davids, N., & Levenson, A. (1942). Table of the zeros of the
/// legendre polynomials of order 1-16 and the weight coefficients for gauss’
/// mechanical quadrature formula. Bulletin of the American Mathematical
/// Society, 48(10), 739–743.
///
///@param integrand
///@param left must be -1.
///@param right must be +1.
///
///@return integrated value
///
double QuadratureGuassianLegendre5(const Integrand integrand, const double left,
                                   const double right);
///@brief Gauss-Legendre quadrature with 16 points.
/// Weights and abscissas are taken from
/// Lowan, A. N., Davids, N., & Levenson, A. (1942). Table of the zeros of the
/// legendre polynomials of order 1-16 and the weight coefficients for gauss’
/// mechanical quadrature formula. Bulletin of the American Mathematical
/// Society, 48(10), 739–743.
///
///@param integrand
///@param left must be -1.
///@param right must be +1.
///
///@return integrated value.
///
///
double QuadratureGuassianLegendre16(const Integrand integrand,
                                    const double left, const double right);

///@brief Gauss-Hermite quadrature with 5 points. Calculate the following
/// integral given $f$.
///
/// $$
///   \\int_{-\\infty}^{\\infty}
///      e^{-x^{2}}
///      f(x)
///   \\ dx
/// $$
///
///@param integrand
///@param left must be $-\\infity$.
///@param right must be $+\\infity$.
///
///@return integrated value.
double QuadratureGuassianHermite5(const Integrand integrand, const double left,
                                  const double right);

double QuadratureGaussKronrodHermite15(const Integrand integrand,
                                       const double left, const double right);

}  // namespace quadrature
}  // namespace numrecipe
