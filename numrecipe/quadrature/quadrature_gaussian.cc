#include "numrecipe/quadrature/quadrature_gaussian.h"
#include <array>
#include <iostream>

namespace numrecipe {
namespace quadrature {

double QuadratureGuassianLegendre5(const Integrand integrand, const double left,
                                   const double right) {
  // clang-format off
  std::array<double, 5> points = {
    -0.906179845938664,
    -0.5384693101056831,
    0.0,
    0.5384693101056831,
    0.906179845938664,
  };
  std::array<double, 5> weights = {
    0.236926885056189,
    0.4786286704993664,
    0.5688888888888889,
    0.4786286704993664,
    0.236926885056189,
  };
  // clang-format on
  double result = 0.0;
  for (int i = 0; i < 5; ++i) {
    result += integrand(points[i]) * weights[i];
  }
  return result;
}

double QuadratureGuassianLegendre16(const Integrand integrand,
                                    const double left, const double right) {
  // clang-format off
  std::array<double, 8> points = {
      0.095012509837637,
      0.281603550779259,
      0.458016777657227,
      0.617876244402644,
      0.755404408355003,
      0.865631202387832,
      0.944575023073233,
      0.989400934991650,
  };
  std::array<double, 8> weights = {
    0.189450610455069,
    0.182603415044924,
    0.169156519395003,
    0.149595988816577,
    0.124628971255534,
    0.095158511682493,
    0.062253523938648,
    0.027152459411754,
  };
  // clang-format on

  double result = 0.0;
  for (int i = 0; i < 8; ++i) {
    result += (integrand(points[i]) * weights[i] +
               integrand(-points[i]) * weights[i]);
  }
  return result;
}

double QuadratureGuassianHermite5(const Integrand integrand, const double left,
                                  const double right) {
  // clang-format off
  std::array<double, 3> points = {
    0.0,
    0.9585724646138185,
    2.020182870456086,
  };
  std::array<double, 3> weights = {
    0.9453087204829418,
    0.3936193231522411,
    0.01995324205904586,
  };
  // clang-format on

  double result = integrand(points[0]) * weights[0];
  for (int i = 1; i < 3; ++i) {
    result += (integrand(points[i]) * weights[i] +
               integrand(-points[i]) * weights[i]);
  }
  return result;
}

double QuadratureGaussKronrodHermite15(const Integrand integrand,
                                       const double left, const double right) {
  // clang-format off
  std::array<double, 8> points = {
    0.000000000000000,
    0.207784955007898,
    0.405845151377397,
    0.586087235467691,
    0.741531185599394,
    0.864864423359769,
    0.949107912342759,
    0.991455371120813,
  };
  std::array<double, 8> kronrod_weights = {
    0.209482141084728,
    0.204432940075298,
    0.190350578064785,
    0.169004726639267,
    0.140653259715525,
    0.104790010322250,
    0.063092092629979,
    0.022935322010529,
  };
  // clang-format on

  double result = +integrand(points[0]) * kronrod_weights[0];
  for (int i = 1; i < 8; ++i) {
    result +=
        (integrand(points[i]) + integrand(-points[i])) * kronrod_weights[i];
  }
  return result;
}

}  // namespace quadrature
}  // namespace numrecipe
