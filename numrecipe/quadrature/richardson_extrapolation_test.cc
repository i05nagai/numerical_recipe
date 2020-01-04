#include "numrecipe/quadrature/richardson_extrapolation.h"
#include <gtest/gtest.h>
#include "numrecipe/test_util/test_util.h"

namespace numrecipe {
namespace quadrature {

double MonomOf6thDegree(double argument) {
  return argument * argument * argument * argument * argument * argument;
}  // f(x)=x^6
double MonomOf8thDegree(double argument) {
  return argument * argument * argument * argument * argument * argument *
         argument * argument;
}  // f(x)=x^8

#ifndef NDEBUG
TEST(RichardsonExtrapolation, AssertIntervalForSimpson) {
  double left_endpoint = 1.0;
  double right_endpoint = 0;
  unsigned int num_of_partition = 100;

  EXPECT_ASSERT_FAIL(numrecipe::quadrature::RichardsonExtrapolation(
      numrecipe::quadrature::QuadratureRule::Simpson, &MonomOf6thDegree,
      left_endpoint, right_endpoint, num_of_partition));
}
#endif

#ifndef NDEBUG
TEST(RichardsonExtrapolation, AssertIntervalForTrapezoidal) {
  double left_endpoint = 1.0;
  double right_endpoint = 0;
  unsigned int num_of_partition = 100;

  EXPECT_ASSERT_FAIL(numrecipe::quadrature::RichardsonExtrapolation(
      numrecipe::quadrature::QuadratureRule::Trapezoidal, &MonomOf6thDegree,
      left_endpoint, right_endpoint, num_of_partition));
}
#endif

// test for extrapolation with trapezoidal rule on the integrations of the
// monomial of 6th degrees from 0 to 1.
TEST(RichardsonExtrTest, TrapezoidalWithMonomOf6thDegreeAsIntegrand) {
  unsigned int num_of_partition =
      100;                      // denoted by N in the following comments.
  double left_endpoint = 0;     // integraton from zero makes it easy to compute
                                // the closed form for polynomial integrands.
  double right_endpoint = 1.0;  // denoted by a.

  double approximator = numrecipe::quadrature::RichardsonExtrapolation(
      numrecipe::quadrature::QuadratureRule::Trapezoidal, &MonomOf6thDegree,
      left_endpoint, right_endpoint, num_of_partition);

  // error turns out to be bounded by a^7/(24N^4).
  double error_boundary = 1.0 / (24.0 * num_of_partition * num_of_partition *
                                 num_of_partition * num_of_partition);

  EXPECT_NEAR(approximator, 1.0 / 7.0, error_boundary);
}

// test for extrapolation with Simpson rule on the integrations of the monomial
// of 8th degrees from 0 to 1.
TEST(RichardsonExtrTest, SimpsonWithMonomOf8thDegreeAsIntegrand) {
  unsigned int num_of_partition =
      100;                      // denoted by N in the following comments.
  double left_endpoint = 0;     // integraton from zero makes it easy to compute
                                // the closed form for polynomial integrands.
  double right_endpoint = 1.0;  // denoted by a.

  double approximator = numrecipe::quadrature::RichardsonExtrapolation(
      numrecipe::quadrature::QuadratureRule::Simpson, &MonomOf8thDegree,
      left_endpoint, right_endpoint, num_of_partition);

  // error turns out to be bounded by 5a^9/(95N^6).
  double error_boundary =
      5.0 / (95.0 * num_of_partition * num_of_partition * num_of_partition *
             num_of_partition * num_of_partition * num_of_partition);

  EXPECT_NEAR(approximator, 1.0 / 9.0, error_boundary);
}

}  // namespace quadrature
}  // namespace numrecipe
