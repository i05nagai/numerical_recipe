#include "recipe/linear_algebra/lu_decomposition.h"
#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>
#include "recipe/linear_algebra/test_util/gtest_assertion.h"
#include "recipe/linear_algebra/util.h"
#include "recipe/linear_algebra/vector.h"

namespace recipe {
namespace linear_algebra {
TEST(SolveLinearEquationWithLUTest, Example) {
  // A = {
  // 1, 2, 3,
  // 4, 5, 6,
  // 7, 8, 0
  // }
  // mat_lu is LU decomposition of A
  std::unique_ptr<double[]> mat_lu = MakeDoubleArray({
      // clang-format off
      1.0, 2.0, 3.0,
      4.0, -3.0, -6.0,
      7.0, 2.0, -9.0,
      // clang-format on
  });
  const int mat_size = 3;
  std::unique_ptr<double[]> vec_b = MakeDoubleArray({
      // clang-format off
        10.0, 11.0, 12.0,
      // clang-format on
  });
  SolveLinearEquationWithLU(mat_lu.get(), mat_size, vec_b.get());

  std::unique_ptr<double[]> expect = MakeDoubleArray({
      // clang-format off
        -28.0/3.0, 29.0/3.0, 0.0,
      // clang-format on
  });

  EXPECT_ARRAY_ELEMENT_EQ(expect, vec_b, mat_size);
}
}  // namespace linear_algebra
}  // namespace recipe
