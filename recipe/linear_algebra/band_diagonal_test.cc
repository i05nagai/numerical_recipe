#include "recipe/linear_algebra/band_diagonal.h"
#include <gtest/gtest.h>
#include <cmath>
#include "recipe/linear_algebra/matrix.h"
#include "recipe/linear_algebra/test_util/gtest_assertion.h"
#include "recipe/linear_algebra/test_util/test_data.h"
#include "recipe/linear_algebra/util.h"
#include "recipe/linear_algebra/vector.h"

namespace recipe {
namespace linear_algebra {

TEST(GaussianEliminationOuterProductBandDiagonalTest, Example) {
  std::unique_ptr<double[]> mat = MakeDoubleArray({
      // clang-format off
    1, 2, 0,
    4, 5, 6,
    0, 8, 9,
      // clang-format on
  });
  const int row_size = 3;
  const int col_size = 3;
  const int size = row_size * col_size;
  const int upper_band = 1;
  const int lower_band = 1;
  GaussianEliminationOuterProductBandDiagonal(mat.get(), row_size, upper_band,
                                              lower_band);

  std::unique_ptr<double[]> expect = MakeDoubleArray({
      // clang-format off
    1.0, 2.0, 0.0,
    4.0, -3.0, 6.0,
    0.0, -8.0/3.0, 25.0,
      // clang-format on
  });
  EXPECT_ARRAY_ELEMENT_EQ(expect, mat, size);
}

TEST(SolveLinearEquationBandDiagonalTest, Example) {
  std::unique_ptr<double[]> mat = MakeDoubleArray({
      // clang-format off
    1.0, 2.0, 0.0,
    4.0, 5.0, 6.0,
    0.0, 8.0, 9.0,
      // clang-format on
  });
  const int row_size = 3;
  const int upper_band = 1;
  const int lower_band = 1;
  const int vec_size = 3;
  std::unique_ptr<double[]> vec = MakeDoubleArray({10.0, 11.0, 12.0});
  SolveLinearEquationBandDiagonal(mat.get(), row_size, upper_band, lower_band,
                                  vec.get());

  // Solution of Ax=b
  std::unique_ptr<double[]> expect =
      MakeDoubleArray({28.0 / 25.0, 111.0 / 25.0, -196.0 / 75.0});
  EXPECT_ARRAY_ELEMENT_EQ(expect, vec, vec_size);
}
}  // namespace linear_algebra
}  // namespace recipe
