#include "recipe/linear_algebra/operator_unary.h"
#include <gtest/gtest.h>
#include "recipe/linear_algebra/test_util/test_data.h"
#include "recipe/test_util/test_util.h"

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

TEST(TransposeTest, Example) {
  double mat[] = {
      1, 2, 3, 4, 5, 6,
  };
  const int row_size = 2;
  const int col_size = 3;
  const std::unique_ptr<double[]> actual = Transpose(mat, row_size, col_size);
  double expect[] = {
      1, 4, 2, 5, 3, 6,
  };
  EXPECT_ARRAY_ELEMENT_EQ(expect, actual, row_size * col_size);
}
}  // namespace linear_algebra
}  // namespace recipe
