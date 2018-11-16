#include "recipe/linear_algebra/matrix.h"
#include <gtest/gtest.h>

namespace recipe {
namespace linear_algebra {

TEST(MatrixTest, CopyConstructor) {
  Matrix m(2, 3);
  Matrix mm(m);
  EXPECT_EQ(m, mm);
}

TEST(MatrixTest, Shape) {
  Matrix m(2, 3);
  EXPECT_EQ(2, m.NumRow());
  EXPECT_EQ(3, m.NumCol());
}

TEST(MatrixTest, AssignmentOperator) {
  Matrix m(2, 3);
  m(0, 0) = 1.0;
  EXPECT_EQ(1.0, m(0, 0));
  Matrix mm = m;
  EXPECT_EQ(m, mm);
}

TEST(MatrixTest, MakeMatrixTest) {
  Matrix actual = MakeMatrix(
      // clang-format off
      {
      {1, 2, 3,},
      {4, 5, 6,},
      {7, 8, 9,},
          // clang-format on
      });
  Matrix expect(3, 3);
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      expect(row, col) = row * 3 + col + 1;
    }
  }
  EXPECT_EQ(expect, actual);
}

TEST(MatrixTest, MakeIdentityMatrixTest) {
  Matrix expect = MakeMatrix(
      // clang-format off
      {
      {1.0, 0.0, 0.0,},
      {0.0, 1.0, 0.0,},
      {0.0, 0.0, 1.0,},
          // clang-format on
      });
  Matrix actual = MakeIdentityMatrix(3);
  EXPECT_EQ(expect, actual);
}

#ifndef NDEBUG
TEST(MatrixTest, AssertIndexOutOfRange) {
  Matrix m(2, 3);
  EXPECT_DEATH(m(-1, 0), "Assertion *");
  EXPECT_DEATH(m(0, 3), "Assertion *");
}
#endif

}  // namespace linear_algebra
}  // namespace recipe
