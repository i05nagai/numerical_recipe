#include "recipe/quadrature/quadrature.h"
#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include "recipe/test_util/test_util.h"

namespace recipe {
namespace quadrature {

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

TEST(SimpsonRuleTest, AssertInterval) {
  const int lower_limit = 1;
  const int upper_limit = 0;
  const int n = 100;

  EXPECT_ASSERT_FAIL(SimpsonRule(TestFunction1, lower_limit, upper_limit, n));
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

TEST(TrapezoidalRuleTest, AssertInterval) {
  const int lower_limit = 1;
  const int upper_limit = 0;
  const int n = 100;

  EXPECT_ASSERT_FAIL(
      TrapezoidalRule(TestFunction1, lower_limit, upper_limit, n));
}

TEST(AccuracyTest, SimpsonRuleReturnsExactSolution) {
  const int n = 100;

  double res4 = SimpsonRule(TestFunction4, 0, 1, n);
  EXPECT_EQ(res4, 0.25);
}

}  // namespace quadrature
}  // namespace recipe