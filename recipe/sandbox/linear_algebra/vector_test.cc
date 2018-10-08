#include "recipe/sandbox/linear_algebra/vector.h"
#include <gtest/gtest.h>

namespace recipe {
namespace sandbox {
namespace linear_algebra {

TEST(Vector, CopyConstructor) {
  Vector v(3);
  Vector vv(v);

  EXPECT_EQ(v, vv);
}

TEST(Vector, Size) {
  Vector v(4);
  EXPECT_EQ(4, v.size());
}

TEST(Vector, Operator) {
  Vector v(3);
  v(0) = 1.0;

  EXPECT_EQ(1.0, v(0));

  Vector vv = v;
  EXPECT_EQ(v, vv);

  EXPECT_DEATH(v(-1), "Assertion failed*");
  EXPECT_DEATH(v(3), "Assertion failed*");
}

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe