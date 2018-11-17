#include "recipe/linear_algebra/operator_binary.h"
#include <gtest/gtest.h>
#include "recipe/linear_algebra/test_util/gtest_assertion.h"
#include "recipe/linear_algebra/test_util/test_data.h"
#include "recipe/linear_algebra/util.h"

namespace recipe {
namespace linear_algebra {
TEST(MultiplyTest, VectorArrayTimesVectorArray) {
  const int row_size = 2;
  const int col_size = 2;
  const int size = row_size * col_size;
  std::unique_ptr<double[]> vec = TestData::GetRandomDoublePointer(size);
  std::unique_ptr<double[]> mat = TestData::GetRandomDoublePointer(size);
  std::unique_ptr<double[]> actual =
      Multiply(mat.get(), row_size, col_size, vec.get());
  // manually solve
  std::unique_ptr<double[]> expect = MakeDoubleArray({
      // clang-format off
    mat[0] * vec[0] + mat[1] * vec[1],
    mat[2] * vec[0] + mat[3] * vec[1],
      // clang-format on
  });
  EXPECT_ARRAY_ELEMENT_EQ(expect, actual, row_size);
}

TEST(MultiplyTest, MatrixArrayTimesMatrixArray) {
  const int row_size = 2;
  const int col_size = 2;
  std::unique_ptr<double[]> mat_lhs = MakeDoubleArray({
      // clang-format off
                                                 1, 2,
                                                 3, 4,
      // clang-format on
  });
  std::unique_ptr<double[]> mat_rhs = MakeDoubleArray({
      // clang-format off
                                                 2, -1,
                                                 1, -2,
      // clang-format on
  });
  std::unique_ptr<double[]> actual = Multiply(
      mat_lhs.get(), row_size, col_size, mat_rhs.get(), row_size, col_size);
  // manually solve
  std::unique_ptr<double[]> expect = MakeDoubleArray({
      // clang-format off
    2 + 2, -1 - 4,
    6 + 4, -3,- 4,
      // clang-format on
  });
  EXPECT_ARRAY_ELEMENT_EQ(expect, actual, row_size);
}
}  // namespace linear_algebra
}  // namespace recipe
