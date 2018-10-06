#include "recipe/integrate/sample.h"
#include <gtest/gtest.h>

namespace recipe {
namespace integrate {
TEST(sample_Foobar_test, simple) {
  const int actual = Foobar(1);
  EXPECT_EQ(1, actual);
}
}  // namespace integrate
}  // namespace recipe
