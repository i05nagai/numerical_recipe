#include "recipe/linear_algebra/householder.h"
#include <gtest/gtest.h>
#include "recipe/linear_algebra/operator_binary.h"
#include "recipe/linear_algebra/operator_unary.h"
#include "recipe/linear_algebra/test_util/gtest_assertion.h"
#include "recipe/linear_algebra/test_util/test_data.h"
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
  ComputeHouseholderVector(vec_x, size, actual_vec.get(), &actual_coeff);
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
      3.0,
      1.0,
      5.0,
      1.0,
  };
  std::unique_ptr<double[]> actual_vec(new double[size]);
  double actual_coeff = 0.0;
  ComputeHouseholderVector(vec_x, size, actual_vec.get(), &actual_coeff);
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
      3.0,
      0.0,
      0.0,
  };
  std::unique_ptr<double[]> actual_vec(new double[size]);
  double actual_coeff = 0.0;
  ComputeHouseholderVector(vec_x, size, actual_vec.get(), &actual_coeff);
  // expect
  double expect_vec[size] = {
      3.0,
      0.0,
      0.0,
  };
  const double expect_coeff = 0.0;
  // compare
  EXPECT_ARRAY_ELEMENT_EQ(expect_vec, actual_vec, size);
  EXPECT_DOUBLE_EQ(expect_coeff, actual_coeff);
}

//
// ComputeHouseholderMatrix
//
TEST(ComputeHouseholderMatrixTest, Example0) {
  Vector householder_vec = MakeVector({1.0, -0.336584, -0.589022, -0.841461});
  double householder_coeff = 0.922385;
  // I - beta * v * v^{T}
  Matrix actual = ComputeHouseholderMatrix(householder_vec, householder_coeff);
  // expect
  const Matrix expect = MakeMatrix(
      {{0.07761499999999999, 0.31046003284, 0.54330505747, 0.7761510044850001},
       {0.31046003284, 0.8955041203065814, -0.1828677894634825,
        -0.2612400096935792},
       {0.54330505747, -0.1828677894634825, 0.6799813684389056,
        -0.4571700169637637},
       {0.7761510044850001, -0.2612400096935792, -0.4571700169637637,
        0.3468991996150474}});
  // compare
  EXPECT_MATRIX_ELEMENT_NEAR(expect, actual, 1e-15);
}

// (I - beta * v * v^{T}) x = norm(x) e1
TEST(ComputeHouseholderMatrixTest, EnsureRelation0) {
  const Vector vec_x = TestData::GetRandomVector(4);
  Vector householder_vec(vec_x.Size());
  double householder_coeff = 0.0;
  ComputeHouseholderVector(vec_x, &householder_vec, &householder_coeff);

  // I - beta * v * v^{T}
  Matrix householder_mat =
      ComputeHouseholderMatrix(householder_vec, householder_coeff);
  // (I - beta * v * v^{T}) x
  Vector actual = Multiply(householder_mat, vec_x);
  // expect
  const Vector expect = MakeVector({
      NormEuclid(vec_x),
      0.0,
      0.0,
      0.0,
  });
  // compare
  EXPECT_VECTOR_ELEMENT_NEAR(expect, actual, 1e-15);
}

//
// MultiplyHouseholderMatrixFromLeft
//
TEST(MultiplyHouseholderMatrixFromLeftTest, EnsureRelation0) {
  Matrix mat_a = MakeMatrix({
      // clang-format off
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
    {10, 11, 12},
      // clang-format on
  });
  Vector vec_col = MakeVector({
      1.0,
      4.0,
      7.0,
      10.0,
  });
  Vector householder_vec(4);
  double householder_coeff = 0.0;
  ComputeHouseholderVector(vec_col, &householder_vec, &householder_coeff);
  MultiplyHouseholderMatrixFromLeft(mat_a.Get(), mat_a.NumRow(), mat_a.NumCol(),
                                    householder_vec.Get(), householder_coeff,
                                    vec_col.Size());

  // expect
  const Matrix expect = MakeMatrix({
      // clang-format off
    {12.884098726725128, 14.591629883279058, 16.299161039832992},
    {0.0, 0.76185618351930184, 1.5237123670386037},
    {0.0, 0.58324832115877534, 1.1664966423175533},
    {0.0, 0.40464045879825239, 0.80928091759650655},
      // clang-format on
  });
  EXPECT_MATRIX_ELEMENT_NEAR(expect, mat_a, 1e-8);
}

//
// ComputeHouseholderBidiagonalization
//

// (I - beta * v * v^{T}) x
TEST(ComputeHouseholderBidiagonalizationTest, Example0) {
  Matrix mat_a = MakeMatrix({
      // clang-format off
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
    {10, 11, 12},
      // clang-format on
  });
  ComputeHouseholderBidiagonalization(mat_a.Get(), mat_a.NumRow(),
                                      mat_a.NumCol());

  // expect
  const Matrix expect = MakeMatrix({
      // clang-format off
    {12.884098726725128, 21.876432827428971, -2.237419620653168},
    {-0.33658421155697277, 2.246235240294709, -0.61328133205414748},
    {-0.58902237022470239, -2.087062084628617, 0.0},
    {-0.84146052889243195, -1.4479420322834726, -3.1623721622453869},
      // clang-format on
  });
  // compare
  EXPECT_MATRIX_ELEMENT_NEAR(expect, mat_a, 1e-14);
}

TEST(ComputeHouseholderBidiagonalizationTest, AlreadyBidiagonal) {
  Matrix mat_a = MakeMatrix({
      // clang-format off
    {1, 1, 0, 0},
    {0, 2, 1, 0},
    {0, 0, 3, 1},
    {0, 0, 0, 4},
      // clang-format on
  });
  // FIXME
  /*
  ComputeHouseholderBidiagonalization(mat_a.Get(), mat_a.NumRow(),
  mat_a.NumCol());

  // expect
  const Matrix expect = MakeMatrix({
    // clang-format off
    // clang-format on
  });
  // compare
  EXPECT_MATRIX_ELEMENT_NEAR(expect, mat_a, 1e-14);
  */
}

// (I - beta * v * v^{T}) x
TEST(ConvertHouseholderBidiagonalizationToBTest, Example0) {
  Matrix mat_a = MakeMatrix({
      // clang-format off
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
    {10, 11, 12},
      // clang-format on
  });
  ComputeHouseholderBidiagonalization(mat_a.Get(), mat_a.NumRow(),
                                      mat_a.NumCol());
  std::unique_ptr<double[]> actual = ConvertHouseholderBidiagonalizationToB(
      mat_a.Get(), mat_a.NumRow(), mat_a.NumCol());

  // expect
  const Matrix expect = MakeMatrix({
      // clang-format off
    {12.884098726725128, 21.876432827428971, 0.0},
    {0.0, 2.246235240294709, -0.61328133205414748},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0},
      // clang-format on
  });
  // compare
  const int size = mat_a.NumRow() * mat_a.NumCol();
  EXPECT_ARRAY_ELEMENT_NEAR(expect.Get(), actual, size, 1e-14);
}

}  // namespace linear_algebra
}  // namespace recipe
