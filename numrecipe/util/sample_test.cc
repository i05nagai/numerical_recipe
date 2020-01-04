#include "numrecipe/util/sample.h"
#include <gtest/gtest.h>

namespace numrecipe {
namespace util {
TEST(sample_bar_test, simple) {
  const int actual = Bar();
  EXPECT_EQ(1, actual);
}
}  // namespace util
}  // namespace numrecipe
