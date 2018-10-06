#include "recipe/sandbox/sample.h"
#include <gtest/gtest.h>

namespace recipe {
namespace sandbox {
TEST(sample_foo_test, simple) {
  const int actual = Foo();
  EXPECT_EQ(1, actual);
}
}  // namespace sandbox
}  // namespace recipe
