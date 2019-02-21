#pragma once

namespace recipe {
namespace quadrature {

//
// Trapezoidal Rule
//

///@brief Compute $\int_a^b f(x) dx$, the integral of function f on interval [a,
/// b]

/// @param f one-dimensional function
/// @param a lower limit of integration
/// @param b upper limit for integration
/// @param num_of_partition number of partition over [a, b]
///
/// @return integral of f
double TrapezoidalRule(double (*f)(double), const double a, const double b,
                       const int num_of_partition);

}  // namespace quadrature
}  // namespace recipe