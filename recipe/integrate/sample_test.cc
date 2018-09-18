#include "recipe/integrate/sample.h"
#include <gtest/gtest.h>

namespace recipe {
namespace integrate {
TEST(hoge_test, simple) {
  const int actual = hoge();
  EXPECT_EQ(1, actual);
}
}  // namespace integrate
}  // namespace recipe
