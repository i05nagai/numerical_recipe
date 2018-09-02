#include <gtest/gtest.h>
#include "recipe/sandbox/sample.h"

namespace recipe {
namespace sandbox {
TEST(hoge_test, simple) {
  const int actual = hoge();
  EXPECT_EQ(1, actual);
}
} // namespace sandbox
} // namespace recipe
