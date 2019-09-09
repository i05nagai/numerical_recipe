#pragma once

#include "recipe/quadrature/quadrature.h"

namespace recipe {
namespace quadrature {

Integral ChangeVariableFiniteToMinusOnePlusOne(
    const Integrand integrand, const double left, const double right);

}  // namespace quadrature
}  // namespace recipe

