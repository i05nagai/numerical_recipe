#include "numrecipe/quadrature/adaptive_quadrature.h"
#include <gtest/gtest.h>

namespace numrecipe {
namespace quadrature {

TEST(AdaptiveSimpsonTest, Example01) {
  Integrand integrand = [](const double x) { return std::sqrt(x); };
  const double left = 0.0;
  const double right = 1.0;
  const double tol = 1e-8;
  const double actual = AdaptiveSimpson(integrand, left, right, tol);

  const double expect = 0.6666666539870345;
  EXPECT_NEAR(expect, actual, 1e-15);
}

TEST(AdaptiveSimpsonTest, Example02) {
  Integrand integrand = [](const double x) {
    if (x < 1) {
      return x + 1;
    } else if ((1 <= x) && (x <= 3)) {
      return 3.0 - x;
    } else {
      return 2.0;
    }
  };
  const double left = 0.0;
  const double right = 5.0;
  const double tol = 1e-6;
  const double actual = AdaptiveSimpson(integrand, left, right, tol);

  // actual value is 7.5;
  const double expect = 7.49996609147638;
  EXPECT_NEAR(expect, actual, 1e-15);
}

}  // namespace quadrature
}  // namespace numrecipe
