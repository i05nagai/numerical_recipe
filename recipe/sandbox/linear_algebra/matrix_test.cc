#include "recipe/sandbox/linear_algebra/matrix.h"
#include <gtest/gtest.h>

namespace recipe {
namespace sandbox {
namespace linear_algebra {

TEST(Matrix, CopyConstructor) {
  Matrix m(2, 3);
  Matrix mm(m);

  EXPECT_EQ(m, mm);
}

TEST(Matrix, Shape) {
  Matrix m(2, 3);

  EXPECT_EQ(2, m.nrow());
  EXPECT_EQ(3, m.ncol());
}

TEST(Matrix, AssignmentOperator) {
  Matrix m(2, 3);
  m(0, 0) = 1.0;

  EXPECT_EQ(1.0, m(0, 0));

  Matrix mm = m;
  EXPECT_EQ(m, mm);
}

/*
TEST(Vector, AssertIndexOutOfRange) {
  Matrix m(2, 3);

  EXPECT_DEATH(m(-1, 0), "Assertion failed*");
  EXPECT_DEATH(m(0, 3), "Assertion failed*");
}*/

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe