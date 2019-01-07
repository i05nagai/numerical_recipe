#include "recipe/linear_algebra/givens_rotation.h"
#include "recipe/test_util/test_util.h"
#include <gtest/gtest.h>
#include <cmath>

namespace recipe {
namespace linear_algebra {
TEST(ComputeGivensRotationParametersTest, Example)
{
  const double val1 = 1.0;
  const double val2 = 1.0;
  const std::pair<double, double> actual
    = ComputeGivensRotationParameters(val1, val2);
  
  EXPECT_DOUBLE_EQ(1.0 / std::sqrt(2.0), actual.first);
  EXPECT_DOUBLE_EQ(-1.0 / std::sqrt(2.0), actual.second);
}

TEST(MultiplyGivensRotationTest, MultiplyFromLeftExample)
{
  double mat_a[] = {
    1.0, -1.0, 4.0,
    1.0, 4.0, -2.0,
    1.0, 4.0, 2.0,
    1.0, -1.0, 0.0,
  };
  const int row_size = 4;
  const int col_size = 3;
  const int givens_index1 = 2;
  const int givens_index2 = 3;
  std::pair<double, double> givens_params 
    = std::make_pair(1.0 / std::sqrt(2.0), -1.0 / std::sqrt(2.0));
  MultiplyGivensRotation(
      givens_index1, givens_index2, givens_params, mat_a, row_size, col_size);

  double expect[] = {
    1.0, -1.0, 4.0,
    1.0, 4.0, -2.0,
    2.0 / std::sqrt(2.0), 3.0 / std::sqrt(2.0), 2.0 / std::sqrt(2.0),
    0.0, -5.0 / std::sqrt(2.0), -2.0 / std::sqrt(2.0),
  };
  EXPECT_ARRAY_ELEMENT_EQ(expect, mat_a, row_size * col_size);
}

TEST(MultiplyGivensRotationTest, MultiplyFromRightExample)
{
  double mat_a[] = {
    1.0, -1.0, 4.0,
    1.0, 4.0, -2.0,
    1.0, 4.0, 2.0,
    1.0, -1.0, 0.0,
  };
  const int row_size = 4;
  const int col_size = 3;
  const int givens_index1 = 1;
  const int givens_index2 = 2;
  std::pair<double, double> givens_params 
    = std::make_pair(-1.0 / std::sqrt(17.0), -4.0 / std::sqrt(17.0));
  MultiplyGivensRotation(
      mat_a, row_size, col_size, givens_index1, givens_index2, givens_params);

  double expect[] = {
    1.0, (1.0 + 16.0) / std::sqrt(17.0), 0.0,
    1.0, (-4.0 - 8.0) / std::sqrt(17.0), (-16.0 + 2.0) / std::sqrt(17.0),
    1.0, (-4.0 + 8.0) / std::sqrt(17.0), (-16.0 - 2.0) / std::sqrt(17.0),
    1.0, (1.0 - 0.0) / std::sqrt(17.0), (4.0 + 0.0) / std::sqrt(17.0),
  };
  EXPECT_ARRAY_ELEMENT_EQ(expect, mat_a, row_size * col_size);
}
}  // namespace linear_algebra
}  // namespace recipe
