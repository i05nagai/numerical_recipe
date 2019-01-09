#include "recipe/linear_algebra/qr_decomposition.h"
#include <gtest/gtest.h>
#include "recipe/linear_algebra/operator_binary.h"
#include "recipe/linear_algebra/operator_unary.h"
#include "recipe/linear_algebra/test_util/gtest_assertion.h"
#include "recipe/linear_algebra/test_util/test_data.h"
#include "recipe/linear_algebra/util.h"
#include "recipe/test_util/test_util.h"

namespace recipe {
namespace linear_algebra {

//
// ComputeHouseholderQR
//
TEST(ComputeHouseholderQRTest, Example0) {
  std::unique_ptr<double[]> mat_a = MakeDoubleArray({
      // clang-format off
        1, -1, 4,
        1, 4, -2,
        1, 4, 2,
        1, -1, 0,
      // clang-format on
  });
  const int row_size = 4;
  const int col_size = 3;
  // v1 = (-1, 1, 1, 1) -> (1, -1, -1, -1)
  // beta = 2 / sqrt(4)^{2} = 0.5
  // v2 = (-5, 0, -5) -> (1, 0, 1)
  // beta = 2 / sqrt(2)^{2} = 1.0
  // R =
  // 2, 3, 2
  // 0, 5, -2,
  // 0, 0, 4,
  // 0, 0, 0
  // acutal is householder_vector
  std::unique_ptr<double[]> householder_coeffs =
      ComputeHouseholderQR(mat_a.get(), row_size, col_size);

  const std::unique_ptr<double[]> expect = MakeDoubleArray({
      // clang-format off
        2, 3, 2,
        -1, 5, -2,
        -1, 0, 4,
        -1, 1, 0,
      // clang-format on
  });
  EXPECT_ARRAY_ELEMENT_EQ(expect, mat_a, row_size * col_size);
  const std::unique_ptr<double[]> expect_householder_coeffs = MakeDoubleArray({
      // clang-format off
        0.5, 1.0, 0,
      // clang-format on
  });
  EXPECT_ARRAY_ELEMENT_EQ(expect_householder_coeffs, householder_coeffs,
                          col_size);
}

TEST(ComputeHouseholderQRTest, Assert) {
  std::unique_ptr<double[]> mat_a = MakeDoubleArray({
      // clang-format off
        1, -1, 4,
        1, 4, -2,
        1, 4, 2,
        1, -1, 0,
      // clang-format on
  });
  const int row_size = 3;
  const int col_size = 4;
  // acutal is householder_vector
  EXPECT_ASSERT_FAIL(ComputeHouseholderQR(mat_a.get(), row_size, col_size));
}

TEST(ConvertHouseholderQRToQTest, Example0) {
  std::unique_ptr<double[]> mat_a = MakeDoubleArray({
      // clang-format off
        1, -1, 4,
        1, 4, -2,
        1, 4, 2,
        1, -1, 0,
      // clang-format on
  });
  const int row_size = 4;
  const int col_size = 3;
  std::unique_ptr<double[]> householder_coeffs =
      ComputeHouseholderQR(mat_a.get(), row_size, col_size);
  // acutal is householder_vector
  std::unique_ptr<double[]> mat_q = ConvertHouseholderQRToQ(
      mat_a.get(), householder_coeffs.get(), row_size, col_size);
  std::unique_ptr<double[]> expect = MakeDoubleArray({
      // clang-format off
        0.5, -0.5, 0.5, -0.5,
        0.5, 0.5, -0.5, -0.5,
        0.5, 0.5, 0.5, 0.5,
        0.5, -0.5, -0.5, 0.5,
      // clang-format on
  });
  EXPECT_ARRAY_ELEMENT_EQ(expect, mat_q, row_size * col_size);
}

TEST(ConvertHouseholderQRToRTest, Example0) {
  std::unique_ptr<double[]> mat_a = MakeDoubleArray({
      // clang-format off
        1, -1, 4,
        1, 4, -2,
        1, 4, 2,
        1, -1, 0,
      // clang-format on
  });
  const int row_size = 4;
  const int col_size = 3;
  std::unique_ptr<double[]> householder_coeffs =
      ComputeHouseholderQR(mat_a.get(), row_size, col_size);
  // acutal is householder_vector
  std::unique_ptr<double[]> mat_r = ConvertHouseholderQRToR(
      mat_a.get(), householder_coeffs.get(), row_size, col_size);
  std::unique_ptr<double[]> expect = MakeDoubleArray({
      // clang-format off
        2, 3, 2,
        0, 5, -2,
        0, 0, 4,
        0, 0, 0,
      // clang-format on
  });
  EXPECT_ARRAY_ELEMENT_EQ(expect, mat_r, row_size * col_size);
}

//
// GivensQR
//

}  // namespace linear_algebra
}  // namespace recipe
