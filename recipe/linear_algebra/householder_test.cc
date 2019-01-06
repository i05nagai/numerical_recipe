#include "recipe/linear_algebra/householder.h"
#include <gtest/gtest.h>
#include "recipe/linear_algebra/test_util/test_data.h"
#include "recipe/linear_algebra/test_util/gtest_assertion.h"
#include "recipe/linear_algebra/operator_unary.h"
#include "recipe/linear_algebra/operator_binary.h"
#include "recipe/test_util/test_util.h"

namespace recipe {
namespace linear_algebra {

//
// ComputeHouseholderVector
//
TEST(ComputeHouseholderVectorTest, Size1) {
  const int size = 1;
  const double vec_x[] = {
    3.0,
  };
  std::unique_ptr<double[]> actual_vec(new double[size]);
  double actual_coeff = 0.0;
  ComputeHouseholderVector(
      vec_x, size, actual_vec.get(), &actual_coeff);
  // expect
  double expect_vec[size] = {
    3.0,
  };
  double expect_coeff = 0.0;
  // compare
  EXPECT_ARRAY_ELEMENT_EQ(expect_vec, actual_vec, size);
  EXPECT_DOUBLE_EQ(expect_coeff, actual_coeff);
}

TEST(ComputeHouseholderVectorTest, Example0) {
  const int size = 4;
  const double vec_x[] = {
    3.0, 1.0, 5.0, 1.0,
  };
  std::unique_ptr<double[]> actual_vec(new double[size]);
  double actual_coeff = 0.0;
  ComputeHouseholderVector(
      vec_x, size, actual_vec.get(), &actual_coeff);
  // expect
  const double v1 = vec_x[0] - NormEuclid(vec_x, size);
  double expect_vec[size] = {
    // clang-format off
    1.0,
    1.0 / v1,
    5.0 / v1,
    1.0 / v1,
    // clang-format on
  };
  const double expect_coeff = 2.0 / InnerProduct(expect_vec, expect_vec, size);
  // compare
  EXPECT_ARRAY_ELEMENT_EQ(expect_vec, actual_vec, size);
  EXPECT_DOUBLE_EQ(expect_coeff, actual_coeff);
}

TEST(ComputeHouseholderVectorTest, NormIsDominatedByFirstElement) {
  const int size = 3;
  const double vec_x[] = {
    3.0, 0.0, 0.0,
  };
  std::unique_ptr<double[]> actual_vec(new double[size]);
  double actual_coeff = 0.0;
  ComputeHouseholderVector(
      vec_x, size, actual_vec.get(), &actual_coeff);
  // expect
  double expect_vec[size] = {
    3.0, 0.0, 0.0,
  };
  const double expect_coeff = 0.0;
  // compare
  EXPECT_ARRAY_ELEMENT_EQ(expect_vec, actual_vec, size);
  EXPECT_DOUBLE_EQ(expect_coeff, actual_coeff);
}

//
// ComputeHouseholderMatrix
//

// (I - beta * v * v^{T}) x = norm(x) e1
TEST(ComputeHouseholderMatrixTest, EnsureRelation0) {
  const Vector vec_x = TestData::GetRandomVector(4);
  Vector householder_vec (vec_x.Size());
  double householder_coeff = 0.0;
  ComputeHouseholderVector(vec_x, &householder_vec, &householder_coeff);

  // I - beta * v * v^{T}
  Matrix householder_mat = ComputeHouseholderMatrix(householder_vec, householder_coeff);
  // (I - beta * v * v^{T}) x
  Vector actual = Multiply(householder_mat, vec_x);
  // expect
  const Vector expect = MakeVector({
    NormEuclid(vec_x), 0.0, 0.0, 0.0,
  });
  // compare
  EXPECT_VECTOR_ELEMENT_NEAR(expect, actual, 1e-15);
}

}  // namespace linear_algebra
}  // namespace recipe
