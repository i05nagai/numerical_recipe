#pragma once

#include "recipe/quadrature/quadrature.h"

namespace recipe {
namespace quadrature {

  ///@brief 
  ///
  ///@param integrand
  ///@param left
  ///@param right
  ///
  ///@return 
  ///
Integral ChangeVariableInverse(
    const Integrand& integrand, const double left, const double right);

Integral ChangeVariableToZeroOne(
    const Integrand& integrand,
    const double left, const double right);

bool IsChangeVariablePowerLaw(
    const Integrand& integrand,
    const double left, const double right);

Integral ChangeVariablePowerLawLeft(
    const Integrand& integrand,
    const double left, const double right, const double gamma=0.5);

Integral ChangeVariablePowerLawRight(
    const Integrand& integrand,
    const double left, const double right, const double gamma=0.5);

Integral ChangeVariableExp(
    const Integrand& integrand,
    const double left, const double right);

Integral ChangeVariableHyperbolicTangent(
    const Integrand& integrand, const double left, const double right);

Integral ChangeVariableHyperbolicTangentZeroInfinity(
    const Integrand& integrand, const double left, const double right);

Integral ChangeVariableHyperbolicTangentMinusInfinityPlusInfinity(
    const Integrand& integrand, const double left, const double right);

Integral ChangeVariableDoubleExponential(
    const Integrand& integrand, const double left, const double right);

Integral ChangeVariableDoubleExponentialZeroInfinity(
    const Integrand& integrand, const double left, const double right,
    const double c=1.0);

Integral ChangeVariableMixed(
    const Integrand& integrand, const double left, const double right,
    const double left_new=-4.0, const double right_new=4.0);

}  // namespace quadrature
}  // namespace recipe

