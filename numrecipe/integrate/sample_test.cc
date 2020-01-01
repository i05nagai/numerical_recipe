#include "numrecipe/integrate/sample.h"
#include <gtest/gtest.h>

namespace numrecipe {
namespace integrate {
TEST(sample_Foobar_test, simple) {
  const int actual = Foobar(1);
  EXPECT_EQ(1, actual);
}
}  // namespace integrate
}  // namespace numrecipe
