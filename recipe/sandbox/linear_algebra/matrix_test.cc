#include "recipe/sandbox/linear_algebra/matrix.h"
#include <gtest/gtest.h>

namespace recipe {
namespace sandbox {
namespace linear_algebra {

TEST(Matrix, CopyConstructor) {
  Matrix m(2, 3);
  Matrix b(m);

  EXPECT_EQ(m(0, 0), b(0, 0));
}

TEST(Matrix, Shape) {
  Matrix m(2, 3);

  EXPECT_EQ(2, m.nrow());
  EXPECT_EQ(3, m.ncol());
}

TEST(Matrix, Operator) {
  Matrix m(2, 3);
  m(0, 0) = 1.0;

  EXPECT_EQ(1.0, m(0, 0));

  Matrix mm = m;
  EXPECT_EQ(m(0, 0), mm(0, 0));

  EXPECT_DEATH(m(-1, 0), "Assertion failed*");
  EXPECT_DEATH(m(0, 3), "Assertion failed*");
}

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe