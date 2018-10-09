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
  EXPECT_EQ(a.size(), b.size());

  for (int i = 0; i < a.size(); i++) {
    EXPECT_NEAR(a(i), b(i), 1e-6);
  }
}

void EXPECT_NE_VECTOR_ELEM(const Vector& a, const Vector& b) {
  EXPECT_EQ(a.size(), b.size());

  bool ne_flg = false;
  for (int i = 0; i < a.size(); i++) {
    if (abs(a(i) - b(i)) > 1e-6) ne_flg = true;
  }

  EXPECT_TRUE(ne_flg);
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

/*
TEST(LUDecomposition, AssertInputIsSquareMatrix) {
  Matrix m = Matrix(3, 4);

  EXPECT_DEATH(OuterProductLU(m), "Assertion failed*");
  EXPECT_DEATH(CroutLU(m), "Assertion failed*");
  EXPECT_DEATH(OuterProductLUWithPartialPivot(m), "Assertion failed*");
}

TEST(LUDecomposition, AssertMatrixAndVectorIsCompatible) {
  Matrix m = Matrix(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 0;
  Vector b = Vector(3);

  EXPECT_DEATH(OuterProductLU(m).Solve(b), "Assertion failed*");
  EXPECT_DEATH(CroutLU(m).Solve(b), "Assertion failed*");
  EXPECT_DEATH(OuterProductLUWithPartialPivot(m).Solve(b), "Assertion failed*");
}*/

std::tuple<Matrix, Vector, Vector> GetTestData1() {
  Matrix a = Matrix(3, 3);
  a(0, 0) = 2;
  a(0, 1) = -1;
  a(0, 2) = 3;

  a(1, 0) = 4;
  a(1, 1) = 2;
  a(1, 2) = 1;

  a(2, 0) = -6;
  a(2, 1) = -1;
  a(2, 2) = 2;

  Vector b(3);
  b(0) = 2;
  b(1) = 1;
  b(2) = 3;

  Vector expected(3);
  expected(0) = -0.25;
  expected(1) = 0.5;
  expected(2) = 1;
  return std::make_tuple(a, b, expected);
}

std::tuple<Matrix, Vector, Vector> GetTestData2() {
  Matrix a(2, 2);
  a(0, 0) = 0.001;
  a(0, 1) = 1.00;
  a(1, 0) = 1.00;
  a(1, 1) = 2.00;

  Vector b(2);
  b(0) = 1;
  b(1) = 3;

  Vector expected(2);
  expected(0) = 1.00200401;
  expected(1) = 0.998998;
  return std::make_tuple(a, b, expected);
}

std::tuple<Matrix, Vector, Vector> GetTestData3() {
  Matrix a(2, 2);
  a(0, 0) = -0.001;
  a(0, 1) = 6;
  a(1, 0) = 3;
  a(1, 1) = 5;

  Vector b(2);
  b(0) = 6.001;
  b(1) = 2;

  Vector expected(2);
  expected(0) = -1;
  expected(1) = 1;
  return std::make_tuple(a, b, expected);
}

std::tuple<Matrix, Vector, Vector> GetTestDataLessStable() {
  Matrix a = Matrix(2, 2);
  a(0, 0) = 1e-20;
  a(0, 1) = 1;
  a(1, 0) = 1;
  a(1, 1) = 1;

  Vector b(2);
  b(0) = 1;
  b(1) = 0;

  Vector expected(2);
  expected(0) = -1;
  expected(1) = 1;
  return std::make_tuple(a, b, expected);
}

//
// OuterProductLU
//
TEST(LUDecomposition, SolveOuterProductLU1) {
  std::tuple<Matrix, Vector, Vector> data = GetTestData1();
  const auto& a = std::get<0>(data);
  const auto& b = std::get<1>(data);
  const auto& expected = std::get<2>(data);
  EXPECT_EQ_VECTOR(OuterProductLU(a).Solve(b), expected);
}

TEST(LUDecomposition, SolveOuterProductLU2) {
  std::tuple<Matrix, Vector, Vector> data = GetTestData2();
  const auto& a = std::get<0>(data);
  const auto& b = std::get<1>(data);
  const auto& expected = std::get<2>(data);
  EXPECT_EQ_VECTOR(OuterProductLU(a).Solve(b), expected);
}

TEST(LUDecomposition, SolveOuterProductLU3) {
  std::tuple<Matrix, Vector, Vector> data = GetTestData3();
  const auto& a = std::get<0>(data);
  const auto& b = std::get<1>(data);
  const auto& expected = std::get<2>(data);
  EXPECT_EQ_VECTOR(OuterProductLU(a).Solve(b), expected);
}

TEST(LUDecomposition, SolveOuterProductLUStability) {
  std::tuple<Matrix, Vector, Vector> data = GetTestDataLessStable();
  const auto& a = std::get<0>(data);
  const auto& b = std::get<1>(data);
  const auto& expected = std::get<2>(data);
  EXPECT_EQ_VECTOR(OuterProductLU(a).Solve(b), expected);
}

//
// CroutLU
//
TEST(LUDecomposition, SolveCroutLU1) {
  std::tuple<Matrix, Vector, Vector> data = GetTestData1();
  const auto& a = std::get<0>(data);
  const auto& b = std::get<1>(data);
  const auto& expected = std::get<2>(data);
  EXPECT_EQ_VECTOR(CroutLU(a).Solve(b), expected);
}

TEST(LUDecomposition, SolveCroutLU2) {
  std::tuple<Matrix, Vector, Vector> data = GetTestData2();
  const auto& a = std::get<0>(data);
  const auto& b = std::get<1>(data);
  const auto& expected = std::get<2>(data);
  EXPECT_EQ_VECTOR(CroutLU(a).Solve(b), expected);
}

TEST(LUDecomposition, SolveCroutLU3) {
  std::tuple<Matrix, Vector, Vector> data = GetTestData3();
  const auto& a = std::get<0>(data);
  const auto& b = std::get<1>(data);
  const auto& expected = std::get<2>(data);
  EXPECT_EQ_VECTOR(CroutLU(a).Solve(b), expected);
}

TEST(LUDecomposition, SolveCroutLUStability) {
  std::tuple<Matrix, Vector, Vector> data = GetTestDataLessStable();
  const auto& a = std::get<0>(data);
  const auto& b = std::get<1>(data);
  const auto& expected = std::get<2>(data);
  EXPECT_EQ_VECTOR(CroutLU(a).Solve(b), expected);
}

//
// OuterProductLUWithPartialPivot
//
TEST(LUDecomposition, SolveOuterProductLUWithPartialPivot1) {
  std::tuple<Matrix, Vector, Vector> data = GetTestData1();
  const auto& a = std::get<0>(data);
  const auto& b = std::get<1>(data);
  const auto& expected = std::get<2>(data);
  EXPECT_EQ_VECTOR(OuterProductLUWithPartialPivot(a).Solve(b), expected);
}

TEST(LUDecomposition, SolveOuterProductLUWithPartialPivot2) {
  std::tuple<Matrix, Vector, Vector> data = GetTestData2();
  const auto& a = std::get<0>(data);
  const auto& b = std::get<1>(data);
  const auto& expected = std::get<2>(data);
  EXPECT_EQ_VECTOR(OuterProductLUWithPartialPivot(a).Solve(b), expected);
}

TEST(LUDecomposition, SolveOuterProductLUWithPartialPivot3) {
  std::tuple<Matrix, Vector, Vector> data = GetTestData3();
  const auto& a = std::get<0>(data);
  const auto& b = std::get<1>(data);
  const auto& expected = std::get<2>(data);
  EXPECT_EQ_VECTOR(OuterProductLUWithPartialPivot(a).Solve(b), expected);
}

TEST(LUDecomposition, SolveOuterProductLUWithPartialPivotStability) {
  std::tuple<Matrix, Vector, Vector> data = GetTestDataLessStable();
  const auto& a = std::get<0>(data);
  const auto& b = std::get<1>(data);
  const auto& expected = std::get<2>(data);
  EXPECT_EQ_VECTOR(OuterProductLUWithPartialPivot(a).Solve(b), expected);
}

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe
