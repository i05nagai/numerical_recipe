#include "recipe/util/sample.h"
#include <gtest/gtest.h>

namespace recipe {
namespace util {
TEST(hoge_test, simple) {
  const int actual = hoge();
  EXPECT_EQ(1, actual);
}
}  // namespace util
}  // namespace recipe
