#include "recipe/core/core.h"
#include "recipe/quadrature/change_variable.h"
#include "recipe/test_util/test_util.h"
#include <gtest/gtest.h>

namespace recipe {
namespace quadrature {

TEST(ChangeVariableInverseTest, Example)
{
  Integrand integrand = [](const double x) { 
    return x;
  };
  const std::vector<double> data = test_util::TestData::GetRandomNumbersSorted(3);
  const double left = data[0];
  const double right = data[1];
  const double t = data[2];
  const Integral actual = ChangeVariableInverse(integrand, left, right);

  const double expect = 1.0 / (t * t * t);
  const double expect_left = 1.0 / right;
  const double expect_right = 1.0 / left;
  EXPECT_DOUBLE_EQ(expect, actual.GetIntegrand()(t));
  EXPECT_DOUBLE_EQ(expect_left, actual.Left());
  EXPECT_DOUBLE_EQ(expect_right, actual.Right());
}

TEST(ChangeVariablePowerLawLeftTest, Example)
{
  Integrand integrand = [](const double x) {
    return x;
  };
  const std::vector<double> data = test_util::TestData::GetRandomNumbersSorted(3);
  const double left = data[0];
  const double right = data[1];
  const double t = data[2];
  const double gamma = 0.5;
  const Integral actual = ChangeVariablePowerLawLeft(integrand, left, right, gamma);

  const double expect = std::pow(t, gamma / (1.0 - gamma)) / (1.0 - gamma)
    * (std::pow(t, 1.0 / (1.0 - gamma)) + left);
  const double expect_left = 0.0;
  const double expect_right = std::pow(right - left, 1.0 - gamma);
  EXPECT_DOUBLE_EQ(expect, actual.GetIntegrand()(t));
  EXPECT_DOUBLE_EQ(expect_left, actual.Left());
  EXPECT_DOUBLE_EQ(expect_right, actual.Right());
}

TEST(ChangeVariablePowerLawRightTest, Example)
{
  Integrand integrand = [](const double x) {
    return x;
  };
  const std::vector<double> data = test_util::TestData::GetRandomNumbersSorted(3);
  const double left = data[0];
  const double right = data[1];
  const double t = data[2];
  const double gamma = 0.5;
  const Integral actual = ChangeVariablePowerLawRight(integrand, left, right, gamma);

  const double expect = std::pow(t, gamma / (1.0 - gamma)) / (1.0 - gamma)
    * (right - std::pow(t, 1.0 / (1.0 - gamma)));
  const double expect_left = 0.0;
  const double expect_right = std::pow(right - left, 1.0 - gamma);
  EXPECT_DOUBLE_EQ(expect, actual.GetIntegrand()(t));
  EXPECT_DOUBLE_EQ(expect_left, actual.Left());
  EXPECT_DOUBLE_EQ(expect_right, actual.Right());
}

TEST(ChangeVariableExpTest, Example)
{
  Integrand integrand = [](const double x) { 
    return x;
  };
  const std::vector<double> data = test_util::TestData::GetRandomNumbersSorted(3);
  const double left = data[0];
  const double right = data[1];
  const double t = data[2];
  const Integral actual = ChangeVariableExp(integrand, left, right);

  const double expect = -std::log(t) * 1.0 / t;
  const double expect_left = std::exp(-right);
  const double expect_right = std::exp(-left);
  EXPECT_DOUBLE_EQ(expect, actual.GetIntegrand()(t));
  EXPECT_DOUBLE_EQ(expect_left, actual.Left());
  EXPECT_DOUBLE_EQ(expect_right, actual.Right());
}

//
// tanh rule
//

TEST(ChangeVariableHyperbolicTangentTest, Example)
{
  Integrand integrand = [](const double x) { 
    return x;
  };
  const std::vector<double> data = test_util::TestData::GetRandomNumbersSorted(3);
  const double left = data[0];
  const double right = data[1];
  const double t = data[2];
  const Integral actual = ChangeVariableHyperbolicTangent(integrand, left, right);

  const double expect = ((0.5 * (right + left) + 0.5 * (right - left) * std::tanh(t))
    * 0.5 * (right - left) / (std::cosh(t) * std::cosh(t)));
  const double expect_left = -RECIPE_DOUBLE_INF;
  const double expect_right = RECIPE_DOUBLE_INF;
  EXPECT_DOUBLE_EQ(expect, actual.GetIntegrand()(t));
  EXPECT_DOUBLE_EQ(expect_left, actual.Left());
  EXPECT_DOUBLE_EQ(expect_right, actual.Right());
}

TEST(ChangeVariableHyperbolicTangentZeroInfinityTest, Example)
{
  Integrand integrand = [](const double x) { 
    return x;
  };
  const std::vector<double> data = test_util::TestData::GetRandomNumbersSorted(3);
  const double left = data[0];
  const double right = data[1];
  const double t = data[2];
  const Integral actual = ChangeVariableHyperbolicTangentZeroInfinity(integrand, left, right);

  const double expect = std::exp(t) * std::exp(t);
  const double expect_left = std::log(left);
  const double expect_right = std::log(right);
  EXPECT_DOUBLE_EQ(expect, actual.GetIntegrand()(t));
  EXPECT_DOUBLE_EQ(expect_left, actual.Left());
  EXPECT_DOUBLE_EQ(expect_right, actual.Right());
}

TEST(ChangeVariableHyperbolicTangentMinusInfinityPlusInfinityTest, Example)
{
  Integrand integrand = [](const double x) { 
    return x;
  };
  const std::vector<double> data = test_util::TestData::GetRandomNumbersSorted(3);
  const double left = data[0];
  const double right = data[1];
  const double t = data[2];
  const Integral actual = ChangeVariableHyperbolicTangentMinusInfinityPlusInfinity(integrand, left, right);

  const double expect = std::sinh(t) * std::cosh(t);
  const double expect_left = std::asinh(left);
  const double expect_right = std::asinh(right);
  EXPECT_DOUBLE_EQ(expect, actual.GetIntegrand()(t));
  EXPECT_DOUBLE_EQ(expect_left, actual.Left());
  EXPECT_DOUBLE_EQ(expect_right, actual.Right());
}

//
// Double exponential
//

TEST(ChangeVariableDoubleExponentialTest, Example)
{
  Integrand integrand = [](const double x) { 
    return x;
  };
  const std::vector<double> data = test_util::TestData::GetRandomNumbersSorted(3);
  const double left = data[0];
  const double right = data[1];
  const double t = data[2];
  const Integral actual = ChangeVariableDoubleExponential(integrand, left, right);

  const double expect = std::tanh(0.5 * RECIPE_PI * std::sinh(t))
    * (RECIPE_PI * std::cosh(t) / std::cosh(RECIPE_PI * std::sinh(t) / 2.0));
  const double expect_left = -RECIPE_DOUBLE_INF;
  const double expect_right = RECIPE_DOUBLE_INF;
  EXPECT_DOUBLE_EQ(expect, actual.GetIntegrand()(t));
  EXPECT_DOUBLE_EQ(expect_left, actual.Left());
  EXPECT_DOUBLE_EQ(expect_right, actual.Right());
}

TEST(ChangeVariableDoubleExponentialZeroInfinityTest, Example)
{
  Integrand integrand = [](const double x) { 
    return x;
  };
  const std::vector<double> data = test_util::TestData::GetRandomNumbersSorted(3);
  const double left = data[0];
  const double right = data[1];
  const double t = data[2];
  const Integral actual = ChangeVariableDoubleExponentialZeroInfinity(integrand, left, right);

  const double expect = std::exp(2.0 * std::sinh(t))
     * std::exp(2.0 * std::sinh(t)) * 2.0 * std::cosh(t);
  const double expect_left = std::asinh(std::log(left) / 2.0);
  const double expect_right = std::asinh(std::log(right) / 2.0);
  EXPECT_DOUBLE_EQ(expect, actual.GetIntegrand()(t));
  EXPECT_DOUBLE_EQ(expect_left, actual.Left());
  EXPECT_DOUBLE_EQ(expect_right, actual.Right());
}

//
// Mixed rule
//

TEST(ChangeVariableMixedTest, Example)
{
  Integrand integrand = [](const double x) { 
    return x;
  };
  const std::vector<double> data = test_util::TestData::GetRandomNumbersSorted(3);
  const double left = data[0];
  const double right = data[1];
  const double t = data[2];
  const Integral actual = ChangeVariableMixed(integrand, left, right);

  const double expect = std::exp(t - std::exp(-t))
    * std::exp(t - std::exp(-t)) * (1.0 + std::exp(-t));
  const double expect_left = -4.0;
  const double expect_right = 4.0;
  EXPECT_DOUBLE_EQ(expect, actual.GetIntegrand()(t));
  EXPECT_DOUBLE_EQ(expect_left, actual.Left());
  EXPECT_DOUBLE_EQ(expect_right, actual.Right());
}

}  // namespace quadrature
}  // namespace recipe

