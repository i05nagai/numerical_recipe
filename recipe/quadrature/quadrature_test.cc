#include "recipe/core/core.h"
#include "recipe/quadrature/quadrature.h"
#include "recipe/quadrature/change_variable.h"
#include "recipe/test_util/test_util.h"
#include <cmath>
#include <gtest/gtest.h>
#include <limits>

namespace recipe {
namespace quadrature {
//
// integrate log(x)log(1-x) from 0 to 1 = 2 - pi^2 / 6
//

TEST(IntegrateTest, Example01TrapezoidalRuleOpenDegree2)
{
  Integrand integrand = [](const double x) { 
    return std::log(x) * std::log(1.0 - x);
  };
  const double left = 0.0;
  const double right = 1.0;
  const int num_partition = 50;

  // (0, 1)
  const double actual = TrapezoidalRuleOpenDegree2(
      integrand, left, right, num_partition);

  const double expect = 2.0 - RECIPE_PI * RECIPE_PI / 6.0;
  EXPECT_NEAR(expect, actual, 4e-3);
}

TEST(IntegrateTest, Example01TrapezoidalRuleOpenDegree5)
{
  Integrand integrand = [](const double x) { 
    return std::log(x) * std::log(1.0 - x);
  };
  const double left = 0.0;
  const double right = 1.0;
  const int num_partition = 50;

  // (0, 1)
  const double actual = TrapezoidalRuleOpenDegree5(
      integrand, left, right, num_partition);

  const double expect = 2.0 - RECIPE_PI * RECIPE_PI / 6.0;
  EXPECT_NEAR(expect, actual, 4e-3);
}

TEST(IntegrateTest, Example01DoubleExponentialZeroInfinityAndToZeroOne)
{
  Integrand integrand = [](const double x) { 
    assert(0.0 <= x && x <= 1.0);
    return std::log(x) * std::log(1.0 - x);
  };
  const double left = 0.0;
  const double right = 1.0;
  const int num_partition = 50;

  // (0, 1) -> (-inf, 0)
  const auto integral = ChangeVariableDoubleExponentialZeroInfinity(integrand, left, right);
  // (-inf, 0) -> (0, 0.5)
  const auto integral2 = ChangeVariableToZeroOne(integral.GetIntegrand(), integral.Left(), integral.Right());
  const double actual = TrapezoidalRuleOpenDegree2(
      integral2.GetIntegrand(), integral2.Left(), integral2.Right(), num_partition);

  const double expect = 2.0 - RECIPE_PI * RECIPE_PI / 6.0;
  EXPECT_NEAR(expect, actual, 1e-2);
}

TEST(IntegrateTest, Example01DoubleExponentialZeroInfinityAndToZeroOneDegree5)
{
  Integrand integrand = [](const double x) { 
    assert(0.0 <= x && x <= 1.0);
    return std::log(x) * std::log(1.0 - x);
  };
  const double left = 0.0;
  const double right = 1.0;
  const int num_partition = 50;

  // (0, 1) -> (-inf, 0)
  const auto integral = ChangeVariableDoubleExponentialZeroInfinity(integrand, left, right);
  // (-inf, 0) -> (0, 0.5)
  const auto integral2 = ChangeVariableToZeroOne(integral.GetIntegrand(), integral.Left(), integral.Right());
  const double actual = TrapezoidalRuleOpenDegree5(
      integral2.GetIntegrand(), integral2.Left(), integral2.Right(), num_partition);

  const double expect = 2.0 - RECIPE_PI * RECIPE_PI / 6.0;
  EXPECT_NEAR(expect, actual, 1e-5);
}
//
// integrate 1.0 / (x^1/2 * (1 +x)) from 0 to inf equals pi
//

TEST(IntegrateTest, Example02ToZeroOne)
{
  Integrand integrand = [](const double x) { 
    return 1.0 / (std::sqrt(x) * (1.0 + x));
  };
  const double left = 0.0;
  const double right = RECIPE_DOUBLE_INF;
  const int num_partition = 50;
  // (0, inf) -> (0.5, 1.0)
  const auto integral = ChangeVariableToZeroOne(integrand, left, right);
  const double actual = TrapezoidalRuleOpenDegree2(
      integral.GetIntegrand(), integral.Left(), integral.Right(), num_partition);

  const double expect = RECIPE_PI;
  EXPECT_NEAR(expect, actual, 1);
}

TEST(IntegrateTest, Example02DoubleExponentialZeroInfinityAndToZeroOne)
{
  Integrand integrand = [](const double x) { 
    return 1.0 / (std::sqrt(x) * (1.0 + x));
  };
  const double left = 0.0;
  const double right = RECIPE_DOUBLE_INF;
  const int num_partition = 50;
  // (0, inf) -> (0, inf)
  const auto integral = ChangeVariableDoubleExponentialZeroInfinity(integrand, left, right);
  // (0, inf) -> (0.5, 1.0)
  const auto integral2 = ChangeVariableToZeroOne(integral.GetIntegrand(), integral.Left(), integral.Right());
  const double actual = TrapezoidalRuleOpenDegree2(
      integral2.GetIntegrand(), integral2.Left(), integral2.Right(), num_partition);

  const double expect = RECIPE_PI;
  EXPECT_NEAR(expect, actual, 1e-5);
}

//
// integrate x^{-3/2}sin(x/2) e^{-x} from 0 to inf equals sqrt(pi(sqrt(5) - 2))
//

TEST(IntegrateTest, Example03ToZeroOne)
{
  Integrand integrand = [](const double t) { 
    return std::pow(t, -3.0 / 2.0) * std::sin(t / 2.0) * std::exp(-t);
  };
  const double left = 0.0;
  const double right = RECIPE_DOUBLE_INF;
  const int num_partition = 50;
  // (0, inf) -> (0.5, 1.0)
  const auto integral = ChangeVariableToZeroOne(integrand, left, right);
  const double actual = TrapezoidalRuleOpenDegree2(
      integral.GetIntegrand(), integral.Left(), integral.Right(), num_partition);

  const double expect = std::sqrt(RECIPE_PI * (std::sqrt(5.0) - 2.0));
  EXPECT_NEAR(expect, actual, 1e-1);
}

TEST(IntegrateTest, Example03DoubleExponentialZeroInfinityToZeroOne)
{
  Integrand integrand = [](const double t) { 
    return std::pow(t, -3.0 / 2.0) * std::sin(t / 2.0) * std::exp(-t);
  };
  const double left = 0.0;
  const double right = RECIPE_DOUBLE_INF;
  const int num_partition = 50;
  // (0, inf) -> (0, inf)
  const auto integral = ChangeVariableDoubleExponentialZeroInfinity(integrand, left, right);
  // (0, inf) -> (0.5, 1.0)
  const auto integral2 = ChangeVariableToZeroOne(integral.GetIntegrand(), integral.Left(), integral.Right());
  const double actual = TrapezoidalRuleOpenDegree2(
      integral2.GetIntegrand(), integral2.Left(), integral2.Right(), num_partition);

  const double expect = std::sqrt(RECIPE_PI * (std::sqrt(5.0) - 2.0));
  EXPECT_NEAR(expect, actual, 1e-6);
}

//
// integrate x^{-2/7} e^{-x^{2}} from 0 to inf equals 0.5 * gamma(5/14)
//

TEST(IntegrateTest, Example04DoubleExponentialZeroInfinity)
{
  Integrand integrand = [](const double x) { 
    return std::pow(x, - 2.0 / 7.0) * std::exp(-x * x);
  };
  const double left = 0.0;
  const double right = RECIPE_DOUBLE_INF;
  const int num_partition = 50;

  // (0, inf) -> (0.5, 1.0)
  const auto integral = ChangeVariableToZeroOne(integrand, left, right);
  const double actual = TrapezoidalRuleOpenDegree2(
      integral.GetIntegrand(), integral.Left(), integral.Right(), num_partition);

  const double expect = 0.5 * std::tgamma(5.0 / 14.0);
  EXPECT_NEAR(expect, actual, 5e-2);
}

TEST(IntegrateTest, Example04DoubleExponentialZeroInfinityAndToZeroOne)
{
  Integrand integrand = [](const double x) {
    return std::pow(x, - 2.0 / 7.0) * std::exp(-x * x);
  };
  const double left = 0.0;
  const double right = RECIPE_DOUBLE_INF;
  const int num_partition = 50;

  // (0, inf) -> (0, inf)
  const auto integral = ChangeVariableDoubleExponentialZeroInfinity(integrand, left, right);
  // (0, inf) -> (0.5, 1.0)
  const auto integral2 = ChangeVariableToZeroOne(integral.GetIntegrand(), integral.Left(), integral.Right());
  const double actual = TrapezoidalRuleOpenDegree2(
      integral2.GetIntegrand(), integral2.Left(), integral2.Right(), num_partition);

  const double expect = 0.5 * std::tgamma(5.0 / 14.0);
  EXPECT_NEAR(expect, actual, 1e-7);
}

//
// SimpsonRule
// 

double TestFunction1(double x) { return x; }

double TestFunction2(double x) { return x * x / 2; }

double TestFunction3(double x) { return 1.0 / x; }

double TestFunction4(double x) { return x * x * x; }

TEST(SimpsonRuleTest, Example) {
  const int n = 100;

  double res1 = SimpsonRule(TestFunction1, 0, 1, n);
  EXPECT_NEAR(res1, 0.5, 1e-5);

  double res2 = SimpsonRule(TestFunction2, 0, 1, n);
  EXPECT_NEAR(res2, 1.0 / 6.0, 1e-5);

  double res3 = SimpsonRule(TestFunction3, 1, 2, n);
  EXPECT_NEAR(res3, 0.6931471805, 1e-5);
}

#ifndef NDEBUG
TEST(SimpsonRuleTest, AssertInterval) {
  const int lower_limit = 1;
  const int upper_limit = 0;
  const int n = 100;

  EXPECT_ASSERT_FAIL(SimpsonRule(TestFunction1, lower_limit, upper_limit, n));
}
#endif


//
// TrapezoidalRule
// 

TEST(TrapezoidalRuleOpenDegree2Test, Example) {
  const int num_of_partition = 4;
  const double left = 0.5;
  const double right = 1.0;
  std::function<double (double)> integrand = [](double x) { 
    return x;
  };

  // 0.5 * x^{2}
  // partitions: 4/8, 5/8, 6/8, 7/8, 8/8
  // x^{2}
  std::vector<double> p = {
    (6.0 + 5.0 * 3.0) / 8.0 / 8.0 / 2.0,
    (7.0 * 3.0 + 6.0) / 8.0 / 8.0 / 2.0,
  };
  const double expect = std::accumulate(p.begin(), p.end(), 0.0);
  const double actual = TrapezoidalRuleOpenDegree2(integrand, left, right, num_of_partition);
  EXPECT_NEAR(expect, actual, 1e-16);
}

TEST(TrapezoidalRuleTest, Example) {
  const int n = 100;

  double res1 = TrapezoidalRule(TestFunction1, 0, 1, n);
  EXPECT_NEAR(res1, 0.5, 1e-5);

  double res2 = TrapezoidalRule(TestFunction2, 0, 1, n);
  EXPECT_NEAR(res2, 1.0 / 6.0, 1e-5);

  double res3 = TrapezoidalRule(TestFunction3, 1, 2, n);
  EXPECT_NEAR(res3, 0.6931471805, 1e-5);
}

#ifndef NDEBUG
TEST(TrapezoidalRuleTest, AssertInterval) {
  const int lower_limit = 1;
  const int upper_limit = 0;
  const int n = 100;

  EXPECT_ASSERT_FAIL(
      TrapezoidalRule(TestFunction1, lower_limit, upper_limit, n));
}
#endif

TEST(AccuracyTest, SimpsonRuleReturnsExactSolution) {
  const int n = 100;

  double res4 = SimpsonRule(TestFunction4, 0, 1, n);
  EXPECT_EQ(res4, 0.25);
}

}  // namespace quadrature
}  // namespace recipe
