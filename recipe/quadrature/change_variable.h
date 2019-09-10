#pragma once

#include "recipe/quadrature/quadrature.h"

namespace recipe {
namespace quadrature {

///@brief Change the interval of the integral to (-1, 1).
///
/// $$
///    \\int_{a}^{b} f(x) \\ dx
///    =
///    \\int_{-1}^{1}
///        f
///        \\left(
///            \\frac{b - a }{ 2 }
///            \\left( t + \\frac{ b + a }{ b - a } \\right)
///        \\right)
///    \\ dt
/// $$
///@param integrand
///@param left left point in interval.
///@param right right point in interval.
///
///@return Integral whose interval is (-1, 1)
Integral ChangeVariableFiniteToMinusOnePlusOne(
    const Integrand integrand, const double left, const double right);

}  // namespace quadrature
}  // namespace recipe

