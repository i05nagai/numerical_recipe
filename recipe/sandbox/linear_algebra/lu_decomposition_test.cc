#include "recipe/sandbox/linear_algebra/lu_decomposition.h"
#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>
#include "recipe/sandbox/linear_algebra/matrix.h"
#include "recipe/sandbox/linear_algebra/vector.h"

namespace recipe {
namespace sandbox {
namespace linear_algebra {

void EXPECT_EQ_VECTOR(const Vector& a, const Vector& b) {
  EXPECT_EQ(a.Length(), b.Length());

  for (int i = 0; i < a.Length(); i++) {
    EXPECT_NEAR(a(i), b(i), 1e-6);
  }
}

void EXPECT_NE_VECTOR_ELEM(const Vector& a, const Vector& b) {
  EXPECT_EQ(a.Length(), b.Length());

  bool ne_flg = false;
  for (int i = 0; i < a.Length(); i++) {
    if (abs(a(i) - b(i)) > 1e-6) ne_flg = true;
  }

  EXPECT_TRUE(ne_flg);
}

std::vector<std::tuple<Matrix, Vector, Vector>> TestCases() {
  std::vector<std::tuple<Matrix, Vector, Vector>> vec;

  // sample1
  Matrix a1 = Matrix(3, 3);
  a1(3, 3);
  a1(0, 0) = 2;
  a1(0, 1) = -1;
  a1(0, 2) = 3;

  a1(1, 0) = 4;
  a1(1, 1) = 2;
  a1(1, 2) = 1;

  a1(2, 0) = -6;
  a1(2, 1) = -1;
  a1(2, 2) = 2;

  Vector b1(3);
  b1(0) = 2;
  b1(1) = 1;
  b1(2) = 3;

  Vector expected1(3);
  expected1(0) = -0.25;
  expected1(1) = 0.5;
  expected1(2) = 1;

  std::tuple<Matrix, Vector, Vector> sample1 =
      std::make_tuple(a1, b1, expected1);

  // sample2
  Matrix a2(2, 2);
  a2(0, 0) = 0.001;
  a2(0, 1) = 1.00;
  a2(1, 0) = 1.00;
  a2(1, 1) = 2.00;

  Vector b2(2);
  b2(0) = 1;
  b2(1) = 3;

  Vector expected2(2);
  expected2(0) = 1.00200401;
  expected2(1) = 0.998998;

  std::tuple<Matrix, Vector, Vector> sample2 =
      std::make_tuple(a2, b2, expected2);

  // sample3
  Matrix a3(2, 2);
  a3(0, 0) = -0.001;
  a3(0, 1) = 6;
  a3(1, 0) = 3;
  a3(1, 1) = 5;

  Vector b3(2);
  b3(0) = 6.001;
  b3(1) = 2;

  Vector expected3(2);
  expected3(0) = -1;
  expected3(1) = 1;

  std::tuple<Matrix, Vector, Vector> sample3 =
      std::make_tuple(a3, b3, expected3);

  vec.push_back(sample1);
  vec.push_back(sample2);
  vec.push_back(sample3);

  return vec;
}

TEST(LUDecomposition, NeedPivoting) {
  Matrix m = Matrix(2, 2);
  m(0, 0) = 0;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;

  EXPECT_THROW(OuterProductLU(m), std::runtime_error);
  EXPECT_NO_THROW(OuterProductLUWithPartialPivot(m));
}

TEST(LUDecomposition, Solve) {
  std::vector<std::tuple<Matrix, Vector, Vector>> cases = TestCases();

  for (auto it = cases.begin(); it != cases.end(); it++) {
    auto a = std::get<0>(*it);
    auto b = std::get<1>(*it);
    auto expected = std::get<2>(*it);

    EXPECT_EQ_VECTOR(OuterProductLU(a).Solve(b), expected);
    EXPECT_EQ_VECTOR(CroutLU(a).Solve(b), expected);
    EXPECT_EQ_VECTOR(OuterProductLUWithPartialPivot(a).Solve(b), expected);
  }
}

TEST(LUDecomposition, Stability) {
  Matrix m = Matrix(2, 2);
  m(0, 0) = 1e-20;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;

  Vector b(2);
  b(0) = 1;
  b(1) = 0;

  Vector expected(2);
  expected(0) = -1;
  expected(1) = 1;

  EXPECT_NE_VECTOR_ELEM(OuterProductLU(m).Solve(b), expected);
  EXPECT_NE_VECTOR_ELEM(OuterProductLU(m).Solve(b), expected);
  EXPECT_EQ_VECTOR(OuterProductLUWithPartialPivot(m).Solve(b), expected);
}

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe