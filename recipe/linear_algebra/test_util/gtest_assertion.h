#pragma once
#include <gtest/gtest.h>
#include <cmath>
#include "recipe/linear_algebra/matrix.h"
#include "recipe/linear_algebra/vector.h"
#include "recipe/test_util/gtest_assertion.h"

/// @brief 
/// 
#define EXPECT_MATRIX_ELEMENT_NEAR(expect, actual, abs_error)             \
  EXPECT_PRED_FORMAT3(recipe::linear_algebra::IsElementNearEqual, expect, \
                      actual, abs_error)

/// @brief 
/// 
#define EXPECT_VECTOR_ELEMENT_NEAR(expect, actual, abs_error)             \
  EXPECT_PRED_FORMAT3(recipe::linear_algebra::IsElementNearEqual, expect, \
                      actual, abs_error)

// @brief 
//
// #define EXPECT_VECTOR_ELEMENT_DOUBLE_EQ(expect, actual)                   \
//  EXPECT_PRED_FORMAT2(recipe::linear_algebra::IsElementEqual, expect, \
//                      actual)

namespace recipe {
namespace linear_algebra {
//
// IsElementNearEqual
//
inline ::testing::AssertionResult IsElementNearEqual(
    const char* expr1, const char* expr2, const char* abs_error_expr,
    const Matrix& mat1, const Matrix& mat2, const double abs_error) {
  if (mat1.NumRow() != mat2.NumRow()) {
    return ::testing::AssertionFailure()
           << "size of rows is not same." << std::endl
           << "expect.NumRow: " << mat1.NumRow() << std::endl
           << "actual.NumRow: " << mat2.NumRow();
  }
  if (mat1.NumCol() != mat2.NumCol()) {
    return ::testing::AssertionFailure()
           << "size of rows is not same." << std::endl
           << "expect.NumCol: " << mat1.NumCol() << std::endl
           << "actual.NumCol: " << mat2.NumCol();
  }
  for (size_t row = 0; row < mat1.NumRow(); ++row) {
    for (size_t col = 0; col < mat1.NumCol(); ++col) {
      const double val1 = mat1(row, col);
      const double val2 = mat2(row, col);
      const double diff = std::fabs(val1 - val2);
      if (diff > abs_error) {
        return ::testing::AssertionFailure()
               << "The difference between " << expr1 << " and " << expr2
               << " at " << row << ", " << col << " is " << diff
               << ", which exceeds " << abs_error_expr << ", where\n"
               << expr1 << " evaluates to " << val1 << ",\n"
               << expr2 << " evaluates to " << val2 << ", and\n"
               << abs_error_expr << " evaluates to " << abs_error << ".";
      }
    }
  }
  return ::testing::AssertionSuccess();
}

inline ::testing::AssertionResult IsElementNearEqual(
    const char* expr1, const char* expr2, const char* abs_error_expr,
    const Vector& vec1, const Vector& vec2, const double abs_error) {
  if (vec1.Size() != vec2.Size()) {
    return ::testing::AssertionFailure()
           << "size is not the same." << std::endl
           << "expect.Size: " << vec1.Size() << std::endl
           << "actual.Size: " << vec2.Size();
  }
  for (size_t row = 0; row < vec1.Size(); ++row) {
    const double val1 = vec1(row);
    const double val2 = vec2(row);
    const double diff = std::fabs(val1 - val2);
    if (diff > abs_error) {
      return ::testing::AssertionFailure()
             << "The difference between " << expr1 << " and " << expr2 << " is "
             << diff << ", which exceeds " << abs_error_expr << ", where\n"
             << expr1 << "(" << row << ") evaluates to " << val1 << ",\n"
             << expr2 << "(" << row << ") evaluates to " << val2 << ", and\n"
             << abs_error_expr << "(abs_error) evaluates to " << abs_error
             << ".";
    }
  }
  return ::testing::AssertionSuccess();
}

//
// IsElementEqual
//
/*
inline ::testing::AssertionResult IsElementEqual(
    const char* expr1, const char* expr2,
    const Vector& vec1, const Vector& vec2) {
  if (vec1.Size() != vec2.Size()) {
    return ::testing::AssertionFailure()
           << "size is not the same." << std::endl
           << "expect.Size: " << vec1.Size() << std::endl
           << "actual.Size: " << vec2.Size();
  }

  for (size_t row = 0; row < vec1.Size(); ++row) {
    const ::testing::internal::Double val1(vec1(row));
    const ::testing::internal::Double val2(vec2(row));
    if (!val1.AlmostEquals(val2)) {
      return ::testing::AssertionFailure()
             << expr1 << " and " << expr2 << " is not equal" << std::endl
             << expr1 << "(" << row << ") evaluates to " << val1 << ","
             << std::endl
             << expr2 << "(" << row << ") evaluates to " << val2 << ".";
    }
  }
  return ::testing::AssertionSuccess();
}
*/
}  // namespace linear_algebra
}  // namespace recipe
