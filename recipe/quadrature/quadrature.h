#pragma once

#include <functional>
#include <cmath>
#include <cassert>
#include <iostream>
#include "recipe/core/core.h"

namespace recipe {
namespace quadrature {

typedef std::function<double (const double)> Integrand;

class Integral {
public:
  Integral()
  : integrand_(), left_(0.0), right_(0.0) {
  }

  Integral(const Integral& other)
  : integrand_(other.integrand_), left_(other.left_), right_(other.right_) {
  }

  Integral(const Integrand& integrand, const double left, const double right)
  : integrand_(integrand), left_(left), right_(right)
  {
  }

  Integral& operator=(const Integral& integral) {
    integrand_ = integral.integrand_;
    left_ = integral.left_;
    right_ = integral.right_;
    return *this;
  }

  const Integrand& GetIntegrand() const {
    return integrand_;
  }

  double Left() const {
    return left_;
  }

  double Right() const {
    return right_;
  }

private:
  Integrand integrand_;
  double left_;
  double right_;
};

//
// Double Exponential
//

double QuadratureDoubleExponentialFinite(
    const Integrand& integrand, const int num_partition, const double length);

double QuadratureDoubleExponentialFinite(
    const Integral& integral, const int num_partition, const double length);

double QuadratureDoubleExponentialHalf(
    const Integrand& integrand, const int num_partition, const double length);

double QuadratureDoubleExponentialHalf(
    const Integral& integral, const int num_partition, const double length);

double QuadratureDoubleExponentialInfinite(
    const Integrand& integrand, const int num_partition, const double length);

double QuadratureDoubleExponentialInfinite(
    const Integral& integral, const int num_partition, const double length);


//
// Trapezoidal Rule
//

double TrapezoidalRuleOpenDegree2(
    const Integrand& integrand,
    const double left,
    const double right,
    const unsigned int num_of_partition);

double TrapezoidalRuleOpenDegree5(
    const Integrand& integrand,
    const double left,
    const double right,
    const unsigned int num_of_partition);

double TrapezoidalRuleStep(
    const Integrand& integrand,
    const double step_size,
    const int num_step,
    const double step_from);

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
