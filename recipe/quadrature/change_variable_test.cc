#include "recipe/quadrature/change_variable.h"
#include <gtest/gtest.h>
#include "recipe/core/core.h"
#include "recipe/test_util/test_util.h"

namespace recipe {
namespace quadrature {

TEST(ChangeVariableFiniteToMinusOnePlusOneTest, Example) {
  Integrand integrand = [](const double x) { return x; };
  const std::vector<double> data =
      test_util::TestData::GetRandomNumbersSorted(3);
  const double left = data[0];
  const double right = data[1];
  const double t = data[2];
  const Integral actual =
      ChangeVariableFiniteToMinusOnePlusOne(integrand, left, right);

  const double expect =
      ((right - left) / 2.0 * (t + (right + left) / (right - left)) *
       (right - left) / 2.0);
  const double expect_left = -1.0;
  const double expect_right = 1.0;
  EXPECT_DOUBLE_EQ(expect, actual.GetIntegrand()(t));
  EXPECT_DOUBLE_EQ(expect_left, actual.Left());
  EXPECT_DOUBLE_EQ(expect_right, actual.Right());
}

}  // namespace quadrature
}  // namespace recipe
