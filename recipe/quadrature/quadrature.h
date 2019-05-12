#pragma once

#include <functional>
#include <cmath>
#include <cassert>

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

  double operator()() const {
    return 0.0;
  }

  const Integrand& Integrand() const {
    return integrand_;
  }

  double Left() const {
    return left_;
  }

  double Right() const {
    return right_;
  }

private:
  std::function<double (const double)> integrand_;
  double left_;
  double right_;
};

double QuadratureImproper(
    const Integrand& integrand, const double left, const double right,
    const unsigned int num_partition);


//
// Trapezoidal Rule
//

double TrapezoidalRuleOpenOrder2(
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
