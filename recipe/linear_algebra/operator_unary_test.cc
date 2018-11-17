#include "recipe/linear_algebra/operator_unary.h"
#include <gtest/gtest.h>
#include "recipe/linear_algebra/test_util/test_data.h"

namespace recipe {
namespace linear_algebra {
TEST(NormEuclidTest, Example) {
  const int size = 3;
  const std::unique_ptr<double[]> data = TestData::GetRandomDoublePointer(size);
  const double actual = NormEuclid(data.get(), size);
  const double expect =
      std::sqrt(data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
  EXPECT_EQ(expect, actual);
}
}  // namespace linear_algebra
}  // namespace recipe
