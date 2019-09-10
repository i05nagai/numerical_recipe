#include "recipe/quadrature/quadrature.h"
#include <gtest/gtest.h>
#include <cmath>
#include <exception>
#include <limits>
#include "recipe/core/core.h"
#include "recipe/quadrature/change_variable.h"
#include "recipe/test_util/test_util.h"

namespace recipe {
namespace quadrature {

namespace {

Integrand GetTestFunction(const int id) {
  if (id == 0) {
    // integrate log(x)log(1-x) from 0 to 1 = 2 - pi^2 / 6
    return [](const double x) {
      assert(0.0 <= x && x <= 1.0);
      return std::log(x) * std::log(1.0 - x);
    };
  } else if (id == 1) {
    // integrate 1.0 / (x^1/2 * (1 +x)) from 0 to inf equals pi
    return [](const double x) {
      assert(0.0 <= x && x <= RECIPE_DOUBLE_INF);
      return 1.0 / (std::sqrt(x) * (1.0 + x));
    };
  } else if (id == 2) {
    // integrate x^{-3/2}sin(x/2) e^{-x} from 0 to inf equals sqrt(pi(sqrt(5) -
    // 2))
    return [](const double x) {
      assert(0.0 <= x && x <= RECIPE_DOUBLE_INF);
      return std::pow(x, -3.0 / 2.0) * std::sin(x / 2.0) * std::exp(-x);
    };
  } else if (id == 3) {
    // integrate x^{-2/7} e^{-x^{2}} from 0 to inf equals 0.5 * gamma(5/14)
    return [](const double x) {
      assert(0.0 <= x && x <= RECIPE_DOUBLE_INF);
      return std::pow(x, -2.0 / 7.0) * std::exp(-x * x);
    };
  } else if (id == 4) {
    // integrate (x - 2)(1-x)^{1/4}(1 + x)^{3/4} from -1 to 1 equals -1.9490...
    return [](const double x) {
      assert(-1.0 <= x && x <= 1.0);
      return 1.0 / (x - 2.0) / std::pow(1.0 - x, 1.0 / 4.0) /
             std::pow(1.0 + x, 3.0 / 4.0);
    };
  } else if (id == 5) {
    // integrate cos(pi*x) / (1 - x)^{1/2} from -1 to 1 equals -0.69049...
    return [](const double x) {
      assert(-1.0 <= x && x <= 1.0);
      return std::cos(RECIPE_PI * x) / std::sqrt(1.0 - x);
    };
  } else if (id == 6) {
    // integrate exp(-1-x) / (1 + x) from 0 to inf equals 0.21938...
    return [](const double x) { return std::exp(-1.0 - x) / (1.0 + x); };
  } else if (id == 7) {
    // integrate 1.0 / (1 + x^{2})^{5/4} from -inf to inf equals 2.3962...
    return
        [](const double x) { return 1.0 / std::pow(1.0 + x * x, 5.0 / 4.0); };
  } else if (id == 8) {
    // integrate 1.0 / (1 + x^{4}) from -inf to inf equals 2.2214...
    return [](const double x) { return 1.0 / (1.0 + std::pow(x, 4.0)); };
  } else {
    throw std::out_of_range("id must be less than 9");
  }
}

Integral GetIntegral(const int id) {
  if (id == 0) {
    return ChangeVariableFiniteToMinusOnePlusOne(GetTestFunction(id), 0.0, 1.0);
  } else if (id == 1) {
    return Integral(GetTestFunction(id), 0.0, RECIPE_DOUBLE_INF);
  } else if (id == 2) {
    return Integral(GetTestFunction(id), 0.0, RECIPE_DOUBLE_INF);
  } else if (id == 3) {
    return Integral(GetTestFunction(id), 0.0, RECIPE_DOUBLE_INF);
  } else if (id == 4) {
    return Integral(GetTestFunction(id), -1.0, 1.0);
  } else if (id == 5) {
    return Integral(GetTestFunction(id), -1.0, 1.0);
  } else if (id == 6) {
    return Integral(GetTestFunction(id), 0.0, RECIPE_DOUBLE_INF);
  } else if (id == 7) {
    return Integral(GetTestFunction(id), -RECIPE_DOUBLE_INF, RECIPE_DOUBLE_INF);
  } else if (id == 8) {
    return Integral(GetTestFunction(id), -RECIPE_DOUBLE_INF, RECIPE_DOUBLE_INF);
  } else {
    throw std::out_of_range("id must be less than 9");
  }
}

double GetIntegralExpected(const int id) {
  if (id == 0) {
    return 2.0 - RECIPE_PI * RECIPE_PI / 6.0;
  } else if (id == 1) {
    return RECIPE_PI;
  } else if (id == 2) {
    return std::sqrt(RECIPE_PI * (std::sqrt(5.0) - 2.0));
  } else if (id == 3) {
    return 0.5 * std::tgamma(5.0 / 14.0);
  } else if (id == 4) {
    return -1.9490;
  } else if (id == 5) {
    return -0.69049;
  } else if (id == 6) {
    return 0.2193839343955202;
  } else if (id == 7) {
    return 4.0 * std::sqrt(RECIPE_PI) * std::tgamma(3.0 / 4.0) /
           std::tgamma(1.0 / 4.0);
  } else if (id == 8) {
    return RECIPE_PI / std::sqrt(2.0);
  } else {
    throw std::out_of_range("id must be less than 6");
  }
}
}  // namespace

//
// Double Exponential
//

TEST(IntegrateTest, QuadratureDoubleExponentialFiniteExample4) {
  Integrand integrand = GetTestFunction(4);
  const int num_partition = 30;
  const double actual =
      QuadratureDoubleExponentialFinite(integrand, num_partition, 0.1);
  const double expect = GetIntegralExpected(4);
  EXPECT_NEAR(expect, actual, 1e-3);
}

TEST(IntegrateTest, QuadratureDoubleExponentialFiniteExample5) {
  Integrand integrand = GetTestFunction(5);
  const int num_partition = 30;
  const double actual =
      QuadratureDoubleExponentialFinite(integrand, num_partition, 0.1);
  const double expect = GetIntegralExpected(5);
  EXPECT_NEAR(expect, actual, 1e-5);
}

TEST(IntegrateTest, QuadratureDoubleExponentialHalfExample1) {
  Integrand integrand = GetTestFunction(1);
  const int num_partition = 50;
  const double actual =
      QuadratureDoubleExponentialHalf(integrand, num_partition, 0.1);
  const double expect = GetIntegralExpected(1);
  EXPECT_NEAR(expect, actual, 1e-16);
}

TEST(IntegrateTest, QuadratureDoubleExponentialHalfExample2) {
  Integrand integrand = GetTestFunction(2);
  const int num_partition = 50;
  const double actual =
      QuadratureDoubleExponentialHalf(integrand, num_partition, 0.1);
  const double expect = GetIntegralExpected(2);
  EXPECT_NEAR(expect, actual, 1e-10);
}

TEST(IntegrateTest, QuadratureDoubleExponentialHalfExample3) {
  Integrand integrand = GetTestFunction(3);
  const int num_partition = 50;
  const double actual =
      QuadratureDoubleExponentialHalf(integrand, num_partition, 0.1);
  const double expect = GetIntegralExpected(3);
  EXPECT_NEAR(expect, actual, 1e-10);
}

TEST(IntegrateTest, QuadratureDoubleExponentialHalfExample6) {
  Integrand integrand = GetTestFunction(6);
  const int num_partition = 40;
  const double actual =
      QuadratureDoubleExponentialHalf(integrand, num_partition, 0.1);
  const double expect = GetIntegralExpected(6);
  EXPECT_NEAR(expect, actual, 1e-10);
}

TEST(IntegrateTest, QuadratureDoubleExponentialInfiniteExample7) {
  Integrand integrand = GetTestFunction(7);
  const int num_partition = 50;
  const double actual =
      QuadratureDoubleExponentialInfinite(integrand, num_partition, 0.1);
  const double expect = GetIntegralExpected(7);
  EXPECT_NEAR(expect, actual, 1e-10);
}

TEST(IntegrateTest, QuadratureDoubleExponentialInfiniteExample8) {
  Integrand integrand = GetTestFunction(8);
  const int num_partition = 60;
  const double actual =
      QuadratureDoubleExponentialInfinite(integrand, num_partition, 0.05);
  const double expect = GetIntegralExpected(8);
  EXPECT_NEAR(expect, actual, 1e-10);
}

//
// integrate log(x)log(1-x) from 0 to 1 = 2 - pi^2 / 6
//
TEST(IntegrateTest, Example01TrapezoidalRuleOpenDegree2) {
  Integrand integrand = GetTestFunction(0);
  const double left = 0.0;
  const double right = 1.0;
  const int num_partition = 50;

  // (0, 1)
  const double actual =
      TrapezoidalRuleOpenDegree2(integrand, left, right, num_partition);

  const double expect = 2.0 - RECIPE_PI * RECIPE_PI / 6.0;
  EXPECT_NEAR(expect, actual, 4e-3);
}

TEST(IntegrateTest, Example01TrapezoidalRuleOpenDegree5) {
  Integrand integrand = GetTestFunction(0);
  const double left = 0.0;
  const double right = 1.0;
  const int num_partition = 50;

  // (0, 1)
  const double actual =
      TrapezoidalRuleOpenDegree5(integrand, left, right, num_partition);

  const double expect = 2.0 - RECIPE_PI * RECIPE_PI / 6.0;
  EXPECT_NEAR(expect, actual, 4e-3);
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
  std::function<double(double)> integrand = [](double x) { return x; };

  // 0.5 * x^{2}
  // partitions: 4/8, 5/8, 6/8, 7/8, 8/8
  // x^{2}
  std::vector<double> p = {
      (6.0 + 5.0 * 3.0) / 8.0 / 8.0 / 2.0,
      (7.0 * 3.0 + 6.0) / 8.0 / 8.0 / 2.0,
  };
  const double expect = std::accumulate(p.begin(), p.end(), 0.0);
  const double actual =
      TrapezoidalRuleOpenDegree2(integrand, left, right, num_of_partition);
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
