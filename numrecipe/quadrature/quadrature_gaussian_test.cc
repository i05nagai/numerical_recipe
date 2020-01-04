#include "numrecipe/quadrature/quadrature_gaussian.h"
#include <gtest/gtest.h>
#include "numrecipe/core/core.h"
#include "numrecipe/test_util/test_util.h"

namespace numrecipe {
namespace quadrature {

TEST(QuadratureGuassianLegendre5Test, Example) {
  Integrand integrand = [](const double x) {
    return 7.0 * x * x * x - 8.0 * x * x - 3.0 * x + 3.0;
  };
  const double left = -1;
  const double right = 1;
  const double actual = QuadratureGuassianLegendre5(integrand, left, right);

  const double expect = 2.0 / 3.0;
  EXPECT_NEAR(expect, actual, 1e-15);
}

TEST(QuadratureGuassianLegendre16Test, Example) {
  Integrand integrand = [](const double x) {
    return 7.0 * x * x * x - 8.0 * x * x - 3.0 * x + 3.0;
  };
  const double left = -1;
  const double right = 1;
  const double actual = QuadratureGuassianLegendre16(integrand, left, right);

  const double expect = 2.0 / 3.0;
  EXPECT_NEAR(expect, actual, 1e-12);
}

// Expectation of
TEST(QuadratureGuassianHermite5Test, Example) {
  Integrand h = [](const double x) { return x; };
  Integrand integrand = [h](const double x) {
    const double variance = 1.0;
    const double mean = 1.0;
    return h(std::sqrt(2.0 * variance) * x + mean) / std::sqrt(RECIPE_PI);
  };
  const double left = -RECIPE_DOUBLE_INF;
  const double right = RECIPE_DOUBLE_INF;
  const double actual = QuadratureGuassianHermite5(integrand, left, right);

  const double expect = 1.0;
  EXPECT_NEAR(expect, actual, 1e-15);
}

}  // namespace quadrature
}  // namespace numrecipe
