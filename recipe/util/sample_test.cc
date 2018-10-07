#include "recipe/util/sample.h"
#include <gtest/gtest.h>

namespace recipe {
namespace util {
TEST(sample_bar_test, simple) {
  const int actual = Bar();
  EXPECT_EQ(1, actual);
}
}  // namespace util
}  // namespace recipe
