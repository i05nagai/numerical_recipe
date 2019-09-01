#include "recipe/quadrature/change_variable.h"
#include "recipe/core/core.h"
#include <iostream>

namespace recipe {
namespace quadrature {
// g(t) = 1 / t
// g^{-1}(x) = 1 / x
// dg/dt = - 1 / t^{2}
// int f(g(t)) dg/dt dt from g^{-1}(a) to g^{-1}(b)
Integral ChangeVariableInverse(
    const Integrand& integrand, const double left, const double right) {
  // only one of endpoints is infinity
  // range condition
  assert(left < right && right * left > 0.0);
  double left_new;
  double right_new;
  right_new = 1.0 / left;
  left_new = 1.0 / right;
  const Integrand integnrad_new = [&integrand](const double t) {
    const double x = 1.0 / t;
    const double derivative = 1.0 / (t * t);
    return integrand(x) * derivative;
  };
  return Integral(integnrad_new, left_new, right_new);
}

// g(t) = - log(1 / t - 1)
// g^{-1}(x) = - 1 / (1 + exp(-t))
// dg/dt = - 1 / (t * (1 - t))
// integrate f(g(t)) dg/dt dt from g^{-1}(a) to g^{-1}(b)
Integral ChangeVariableToZeroOne(
    const Integrand& integrand, const double left, const double right)
{
  assert(left < right);
  const double left_new = 1.0 /  (1.0 + std::exp(-left));
  const double right_new = 1.0 / (1.0 + std::exp(-right));
  const Integrand integnrad_new = [&integrand](const double t) {
    // In this transformation, input should be between this range
    assert(0.0 < t && t < 1.0);
    const double x = -std::log(1.0 / t - 1.0);
    const double derivative = 1.0 / (t * (1.0 - t));
    return integrand(x) * derivative;
  };
  return Integral(integnrad_new, left_new, right_new);
}

// g(t) = t^{1/(1-gamma)} + a
// g^{-1}(x) = (x - a)^{(1-gamma)}
// dg/dt = (1/(1-gamma)) * t^{gamma/(1-gamma)}
// int f(g(t)) dg/dt dt from g^{-1}(a) to g^{-1}(b)
Integral ChangeVariablePowerLawLeft(
    const Integrand& integrand,
    const double left, const double right, const double gamma) {
  assert(0.0 <= gamma && gamma < 1.0);
  // endpoints are not infinity
  assert(!std::isinf(left) && !std::isinf(right));
  // range condition
  assert(left <= right);
  const double left_new = 0.0;
  const double right_new = std::pow(right - left, 1.0 - gamma);
  const Integrand integnrad_new = [&integrand, left, gamma](const double t) {
    const double x = std::pow(t, 1.0 / (1.0 - gamma)) + left;
    const double derivative = std::pow(t, gamma / (1.0 - gamma)) / (1.0 - gamma);
    return integrand(x) * derivative;
  };
  return Integral(integnrad_new, left_new, right_new);
}

// g(t) = b - t^{1/(1-gamma)}
// g^{-1}(x) = (b - x)^{(1-gamma)}
// dg/dt = t^{gamma/(1-gamma)} / (1-gamma)
// int f(g(t)) dg/dt dt from g^{-1}(a) to g^{-1}(b)
Integral ChangeVariablePowerLawRight(
    const Integrand& integrand,
    const double left, const double right, const double gamma) {
  assert(0.0 <= gamma && gamma < 1.0);
  // endpoints are not infinity
  assert(!std::isinf(left) && !std::isinf(right));
  // range condition
  assert(left <= right);

  const double left_new = 0.0;
  const double right_new = std::pow(right - left, 1.0 - gamma);
  const Integrand integnrad_new = [&integrand, right, gamma](const double t) {
    const double x = right - std::pow(t, 1.0 / (1.0 - gamma));
    const double derivative = std::pow(t, gamma / (1.0 - gamma)) / (1.0 - gamma);
    return integrand(x) * derivative;
  };
  return Integral(integnrad_new, left_new, right_new);
}

// (-inf, inf) -> (inf, 0)
// g(t) = - log(t)
// g^{-1}(x) = exp(-x)
// dg/dt = - 1 / t
// int f(g(t)) dg/dt dt from g^{-1}(a) to g^{-1}(b)
Integral ChangeVariableExp(
    const Integrand& integrand,
    const double left, const double right) {
  // assert(std::isinf(right));
  // range condition
  assert(left <= right);

  const double left_new = std::exp(-right);
  const double right_new = std::exp(-left);
  const Integrand integnrad_new = [&integrand](const double t) {
    const double x = -std::log(t);
    const double derivative = 1.0 / t;
    const double v = integrand(x) * derivative;
    return v;
  };
  return Integral(integnrad_new, left_new, right_new);
}

// g(t) = (b + a)/2 + (b - a) tanh(t) / 2
// g^{-1}(x) = tanh^{-1}(2(x - (b+a)/2)/(b-a))
// dg/dt = (b-a)sech^{2}(t)/2
// int f(g(t)) dg/dt dt from g^{-1}(a) to g^{-1}(b)
Integral ChangeVariableHyperbolicTangent(
    const Integrand& integrand, const double left, const double right) {
  const Integrand integnrad_new = [&integrand, left, right](const double t) {
    const double x = 0.5 * (right + left) + 0.5 * (right - left) * std::tanh(t);
    const double derivative = 2.0 * (right - x) * (x - left) / (right - left);
    return integrand(x) * derivative;
  };
  
  const double left_new = -RECIPE_DOUBLE_INF;
  const double right_new = RECIPE_DOUBLE_INF;
  return Integral(integnrad_new, left_new, right_new);
}

// g(t) = e^{t}
// g^{-1}(x) = log(x)
// dg/dt = e^{t}
// int f(g(t)) dg/dt dt from g^{-1}(a) to g^{-1}(b)
// a, b must be in (0, infinity)
Integral ChangeVariableHyperbolicTangentZeroInfinity(
    const Integrand& integrand, const double left, const double right) {
  assert(0.0 < left && left < right && right < RECIPE_DOUBLE_INF);
  const Integrand integnrad_new = [&integrand](const double t) {
    const double x = std::exp(t);
    const double derivative = std::exp(t);
    return integrand(x) * derivative;
  };
  
  const double left_new = std::log(left);
  const double right_new = std::log(right);
  return Integral(integnrad_new, left_new, right_new);
}

// g(t) = sinh(t)
// g^{-1}(x) = asinh(x)
// dg/dt = cosh(t)
// int f(g(t)) dg/dt dt from g^{-1}(a) to g^{-1}(b)
// a, b must be in (-infinity, infinity)
Integral ChangeVariableHyperbolicTangentMinusInfinityPlusInfinity(
    const Integrand& integrand, const double left, const double right) {
  assert(-RECIPE_DOUBLE_INF < left && left < right && right < RECIPE_DOUBLE_INF);
  const Integrand integnrad_new = [&integrand](const double t) {
    const double x = std::sinh(t);
    const double derivative = std::cosh(t);
    return integrand(x) * derivative;
  };
  
  const double left_new = std::asinh(left);
  const double right_new = std::asinh(right);
  return Integral(integnrad_new, left_new, right_new);
}

// g(t) = tanh(pi * sinh(t)/2)
// g^{-1}(x) = pi * cosh(t) / cosh(pi sinh(t)/2) / 2
// dg/dt = (b-a)sech^{2}(t)/2
// int f(g(t)) dg/dt dt from g^{-1}(a) to g^{-1}(b)
Integral ChangeVariableDoubleExponential(
    const Integrand& integrand, const double left, const double right) {
  const Integrand integnrad_new = [&integrand](const double t) {
    const double x = std::tanh(0.5 * RECIPE_PI * std::sinh(t));
    const double derivative = RECIPE_PI * std::cosh(t) / std::cosh(RECIPE_PI * std::sinh(t) / 2.0);
    return integrand(x) * derivative;
  };
  const double left_new = -RECIPE_DOUBLE_INF;
  const double right_new = RECIPE_DOUBLE_INF;
  return Integral(integnrad_new, left_new, right_new);
}

// (0, inf) -> (-inf, inf)
// g(t) = exp(2 c sinh(t))
// g^{-1}(x) = asinh(log(x)/2c)
// dg/dt = exp(2 c sinh(t))2c(cosh(t))
// int f(g(t)) dg/dt dt from g^{-1}(a) to g^{-1}(b)
Integral ChangeVariableDoubleExponentialZeroInfinity(
    const Integrand& integrand, const double left, const double right, const double c) {
  const Integrand integnrad_new = [&integrand, c, left, right](const double t) {
    const double x = std::exp(2.0 * c * std::sinh(t));
    const double derivative = std::exp(2.0 * c * std::sinh(t)) * 2.0 * c * std::cosh(t);
    const double val = integrand(x) * derivative;
    return val;
  };
  double left_new = std::asinh(std::log(left) / (2.0 * c));
  double right_new = std::asinh(std::log(right) / (2.0 * c));
  return Integral(integnrad_new, left_new, right_new);
}

// (-inf, inf) -> (-inf, inf)
// g(t) = sinh(2 c sinh(t))
// g^{-1}(x) = asinh(log(x)/2c)
// dg/dt = exp(2 c sinh(t))2c(cosh(t))
// int f(g(t)) dg/dt dt from g^{-1}(a) to g^{-1}(b)
Integral ChangeVariableDoubleExponentialMinusInfinityPlusInfinity(
    const Integrand& integrand, const double left, const double right, const double c) {
  const Integrand integnrad_new = [&integrand, c](const double t) {
    const double x = std::exp(2.0 * c * std::sinh(t));
    const double derivative = std::exp(2.0 * c * std::sinh(t)) * 2.0 * c * std::cosh(t);
    const double val = integrand(x) * derivative;
    return val;
  };
  double left_new = std::asinh(std::log(left) / (2.0 * c));
  double right_new = std::asinh(std::log(right) / (2.0 * c));
  return Integral(integnrad_new, left_new, right_new);
}

// g(t) = e^{t - e^{-t}}
// g^{-1}(x) = 
// dg/dt = x * (1.0 + exp(-t))
// int f(g(t)) dg/dt dt from g^{-1}(a) to g^{-1}(b)
Integral ChangeVariableMixed(
    const Integrand& integrand, const double left, const double right,
    const double left_new, const double right_new) {
  assert(0.0 <= left
         && left < right
         && (right < RECIPE_DOUBLE_INF || std::isinf(right)));
  const Integrand integnrad_new = [&integrand](const double t) {
    const double x = std::exp(t - std::exp(-t));
    const double derivative = x * (1.0 + std::exp(-t));
    return integrand(x) * derivative;
  };
  // TODO: the length of derivative are given as arguments for now.
  // We may think of a better way to decide or give the range.
  // const double left_new = -4.0;
  // const double right_new = 4.0;
  return Integral(integnrad_new, left_new, right_new);
}

}  // namespace quadrature
}  // namespace recipe
