#pragma once

#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include "recipe/core/core.h"

namespace recipe {
namespace quadrature {

typedef std::function<double(const double)> Integrand;

class Integral {
 public:
  Integral() : integrand_(), left_(0.0), right_(0.0) {}

  Integral(const Integral& other)
      : integrand_(other.integrand_),
        left_(other.left_),
        right_(other.right_) {}

  Integral(const Integrand& integrand, const double left, const double right)
      : integrand_(integrand), left_(left), right_(right) {}

  Integral& operator=(const Integral& integral) {
    integrand_ = integral.integrand_;
    left_ = integral.left_;
    right_ = integral.right_;
    return *this;
  }

  const Integrand& GetIntegrand() const { return integrand_; }

  double Left() const { return left_; }

  double Right() const { return right_; }

 private:
  Integrand integrand_;
  double left_;
  double right_;
};

//
// Double Exponential
//

/// @brief Compute the numerical integration with double exponential formula
///  for $(-1, 1)$.
///
///  $$
///    \\frac{\\pi}{2} h
///    \\sum_{i=-n}^{n}
///        \\frac{
///            f(\\tanh(\\pi \\sinh(hi)\\frac{1}{2}))
///            \\cosh(i h)
///        }{
///            \\cosh^{2}(\\pi h \\frac{1}{2} \\sinh(hi))
///        }
///  $$
///
/// @param integrand
/// @param num_partition
/// @param length
///
/// @return
double QuadratureDoubleExponentialFinite(const Integrand& integrand,
                                         const int num_partition,
                                         const double length);

///@brief Overloaded function.
///
///@param integral
///@param num_partition
///@param length
///
///@return
double QuadratureDoubleExponentialFinite(const Integral& integral,
                                         const int num_partition,
                                         const double length);

/// @brief Compute the numerical integration with double exponential formula
/// for $(0, \\infty)$.
///
/// $$
///    \\frac{\\pi}{2} h
///    \\sum_{i=-n}^{n}
///        f\\left( \\exp(\\pi \\sinh(hi)\\frac{1}{2}) \\right)
///        \\cosh(i h)
///        \\exp(\\pi \\sinh(hi) / 2)
/// $$
///@param integrand
///@param num_partition
///@param length
///
///@return
double QuadratureDoubleExponentialHalf(const Integrand& integrand,
                                       const int num_partition,
                                       const double length);

///@brief Overloaded function
///
///@param integral
///@param num_partition
///@param length
///
///@return
double QuadratureDoubleExponentialHalf(const Integral& integral,
                                       const int num_partition,
                                       const double length);

///@brief Compute numerical integration with Double exponetial formula
/// for $(-\\infty, \\infty)$.
/// $$
///    \\frac{\\pi}{2} h
///    \\sum_{i=-n}^{n}
///        f(\\sinh(\\pi \\sinh(hi) / 2))
///        \\cosh(i h)
///        \\cosh(\\pi \\sinh(hi) / 2)
/// $$
///
///@param integrand
///@param num_partition
///@param length
///
///@return
double QuadratureDoubleExponentialInfinite(const Integrand& integrand,
                                           const int num_partition,
                                           const double length);

///@brief Overloaded function.
///
///@param integral
///@param num_partition
///@param length
///
///@return
double QuadratureDoubleExponentialInfinite(const Integral& integral,
                                           const int num_partition,
                                           const double length);

//
// Trapezoidal Rule
//

double TrapezoidalRuleOpenDegree2(const Integrand& integrand, const double left,
                                  const double right,
                                  const unsigned int num_of_partition);

double TrapezoidalRuleOpenDegree5(const Integrand& integrand, const double left,
                                  const double right,
                                  const unsigned int num_of_partition);

double TrapezoidalRuleStep(const Integrand& integrand, const double step_size,
                           const int num_step, const double step_from);

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

//
// Simpson Rule
//

///@brief Compute $\int_a^b f(x) dx$, the integral of function f on interval [a,
/// b]

/// @param f one-dimensional function
/// @param a lower limit of integration
/// @param b upper limit for integration
/// @param num_of_partition number of partition over [a, b]
///
/// @return integral of f
double SimpsonRule(double (*f)(double), const double a, const double b,
                   const int num_of_partition);

}  // namespace quadrature
}  // namespace recipe
