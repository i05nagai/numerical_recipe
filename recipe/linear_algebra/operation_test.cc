#include "recipe/linear_algebra/operation.h"
#include <gtest/gtest.h>
#include "recipe/linear_algebra/matrix.h"
#include "recipe/linear_algebra/test_util/test_data.h"
#include "recipe/linear_algebra/util.h"

namespace recipe {
namespace linear_algebra {
TEST(MatrixTimesVectorPlusVectorTest, Example) {
  const int col_size = 2;
  const int row_size = 2;
  const int size = row_size * col_size;
  std::unique_ptr<double[]> mat = TestData::GetRandomDoublePointer(size);

  std::unique_ptr<double[]> vec_x = TestData::GetRandomDoublePointer(col_size);
  std::unique_ptr<double[]> vec_y = TestData::GetRandomDoublePointer(row_size);

  std::unique_ptr<double[]> actual = MatrixTimesVectorPlusVector(
      mat.get(), row_size, col_size, vec_x.get(), vec_y.get());

  // manually calculate
  const double expect0 = mat[0] * vec_x[0] + mat[1] * vec_x[1] + vec_y[0];
  const double expect1 = mat[2] * vec_x[0] + mat[3] * vec_x[1] + vec_y[1];
  EXPECT_EQ(expect0, actual[0]);
  EXPECT_EQ(expect1, actual[1]);
}

TEST(MatrixTimesVectorMinusVectorTest, Example) {
  const int col_size = 2;
  const int row_size = 2;
  const int size = row_size * col_size;
  std::unique_ptr<double[]> mat = TestData::GetRandomDoublePointer(size);

  std::unique_ptr<double[]> vec_x = TestData::GetRandomDoublePointer(col_size);
  std::unique_ptr<double[]> vec_y = TestData::GetRandomDoublePointer(row_size);

  std::unique_ptr<double[]> actual = MatrixTimesVectorMinusVector(
      mat.get(), row_size, col_size, vec_x.get(), vec_y.get());

  // manually calculate
  const double expect0 = mat[0] * vec_x[0] + mat[1] * vec_x[1] - vec_y[0];
  const double expect1 = mat[2] * vec_x[0] + mat[3] * vec_x[1] - vec_y[1];
  EXPECT_EQ(expect0, actual[0]);
  EXPECT_EQ(expect1, actual[1]);
}

TEST(MinusMatrixTimesVectorPlusVectorTest, Example) {
  const int col_size = 2;
  const int row_size = 2;
  const int size = row_size * col_size;
  std::unique_ptr<double[]> mat = TestData::GetRandomDoublePointer(size);

  std::unique_ptr<double[]> vec_x = TestData::GetRandomDoublePointer(col_size);
  std::unique_ptr<double[]> vec_y = TestData::GetRandomDoublePointer(row_size);

  std::unique_ptr<double[]> actual = MinusMatrixTimesVectorPlusVector(
      mat.get(), row_size, col_size, vec_x.get(), vec_y.get());

  // manually calculate
  const double expect0 = -mat[0] * vec_x[0] - mat[1] * vec_x[1] + vec_y[0];
  const double expect1 = -mat[2] * vec_x[0] - mat[3] * vec_x[1] + vec_y[1];
  EXPECT_EQ(expect0, actual[0]);
  EXPECT_EQ(expect1, actual[1]);
}
}  // namespace linear_algebra
}  // namespace recipe
