#include "numrecipe/linear_algebra/util.h"
#include <gtest/gtest.h>
#include <limits>

namespace numrecipe {
namespace linear_algebra {

TEST(MakeDoubleArrayTest, Example) {
  std::unique_ptr<double[]> data = MakeDoubleArray({
      // clang-format off
    1, 2, 3,
    4, 5, 6,
    7, 8, 9,
      // clang-format on
  });
  for (int i = 0; i < 9; ++i) {
    EXPECT_NEAR(i + 1, data[i], std::numeric_limits<double>::epsilon());
  }
}

TEST(GetIndentityMatrixTest, Example) {
  const int size = 3;
  std::unique_ptr<double[]> actual = GetIndentityMatrix(size);
  std::unique_ptr<double[]> expect = MakeDoubleArray({
      // clang-format off
    1, 0, 0,
    0, 1, 0,
    0, 0, 1,
      // clang-format on
  });
  for (int i = 0; i < size; ++i) {
    EXPECT_NEAR(expect[i], actual[i], std::numeric_limits<double>::epsilon());
  }
}

TEST(CopyDoubleArrayTest, Example) {
  std::unique_ptr<double[]> data = MakeDoubleArray({1, 2, 3, 4, 5, 6, 7, 8, 9});
  const int size = 9;
  std::unique_ptr<double[]> actual = CopyDoubleArray(data.get(), size);
  for (int i = 0; i < size; ++i) {
    EXPECT_NEAR(i + 1.0, data[i], std::numeric_limits<double>::epsilon());
  }
}
}  // namespace linear_algebra
}  // namespace numrecipe
