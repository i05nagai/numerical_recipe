#pragma once
#include <gtest/gtest.h>
#include <cmath>
#include <memory>
#include <vector>

/// @brief an assertion compares two vectors.
/// Two vectors must have the same values.
///
/// Example
/// =======
///
/// ```
///   std::vector<double> expect(5, 1);
///   std::vector<double> actual(5, 1);
///   EXPECT_ARRAY_ELEMENT_EQ(expect, actual);
/// ```
#define EXPECT_VECTOR_ELEMENT_EQ(expect, actual) \
  EXPECT_TRUE(recipe::test_util::IsElementEqual(expect, actual));

/// @brief an assertion compares two arrays.
/// Two arrays must have the same values of the elements.
///
/// Example
/// =======
///
/// ```
///   std::unique_ptr<double[]> expect(new double[5]);
///   std::unique_ptr<double[]> actual(new double[5]);
///   EXPECT_ARRAY_ELEMENT_EQ(expect, actual, 5);
///
///   double expect[] = {1, 2, 3};
///   double actual[] = {1, 2, 3};
///   EXPECT_ARRAY_ELEMENT_EQ(expect, actual, 3);
///
///   double expect[] = {1, 2, 3};
///   std::unique_ptr<double[]> actual(new double[3]);
///   EXPECT_ARRAY_ELEMENT_EQ(expect, actual, 3);
///
///   std::unique_ptr<double[]> expect(new double[3]);
///   double actual[] = {1, 2, 3};
///   EXPECT_ARRAY_ELEMENT_EQ(expect, actual, 3);
/// ```
#define EXPECT_ARRAY_ELEMENT_EQ(expect, actual, size) \
  EXPECT_PRED_FORMAT3(recipe::test_util::IsElementEqual, expect, actual, size)

/// @brief an assertion compares two arrays.
/// Two arrays must have the same values of the elements.
///
/// Example
/// =======
///
/// ```
///   double expect[] = {1, 2, 3};
///   double actual[] = {1, 2, 3};
///   EXPECT_ARRAY_ELEMENT_NEAR(expect, actual, 3, 1e-10);
/// ```
#define EXPECT_ARRAY_ELEMENT_NEAR(expect, actual, size, abs_error)           \
  EXPECT_PRED_FORMAT4(recipe::test_util::IsElementNearEqual, expect, actual, \
                      size, abs_error)

/// @brief an assertion checkes whether the statement passes.
/// The message of `assert` function varies between compilers.
///
/// Example
/// =======
///
/// ```
///   EXPECT_ASSERT_FAIL(assert(1 != 1)); // Pass
///   EXPECT_ASSERT_FAIL(assert(1 == 1)); // Fail
/// ```
#define EXPECT_ASSERT_FAIL(statement) EXPECT_DEATH(statement, "Assert")

namespace recipe {
namespace test_util {

//
// Compare two vectors
//
template <typename T>
inline ::testing::AssertionResult IsElementEqual(const std::vector<T>& v1,
                                                 const std::vector<T>& v2) {
  if (v1.size() != v2.size()) {
    return ::testing::AssertionFailure() << "size of vector is not same";
  }
  for (size_t i = 0; i < v1.size(); ++i) {
    if (v1[i] != v2[i]) {
      return ::testing::AssertionFailure()
             << i << " th element is different. "
             << " expect: " << static_cast<int>(v1[i]) << ", "
             << " actual: " << static_cast<int>(v2[i]);
    }
  }
  return ::testing::AssertionSuccess();
}

template <>
inline ::testing::AssertionResult IsElementEqual(
    const std::vector<double>& v1, const std::vector<double>& v2) {
  if (v1.size() != v2.size()) {
    return ::testing::AssertionFailure()
           << "size of vector is not same." << std::endl
           << "expect.size: " << v1.size() << std::endl
           << "actual.size: " << v2.size();
  }
  for (size_t i = 0; i < v1.size(); ++i) {
    const ::testing::internal::FloatingPoint<double> value1(v1[i]);
    const ::testing::internal::FloatingPoint<double> value2(v2[i]);
    if (!value1.AlmostEquals(value2)) {
      return ::testing::AssertionFailure() << i << " th element is different. "
                                           << " expect: " << v1[i] << std::endl
                                           << " actual: " << v2[i];
    }
  }
  return ::testing::AssertionSuccess();
}

//
// Compare two double pointers with size.
//
inline ::testing::AssertionResult IsElementEqual(
    const char* expr1, const char* expr2, const char* size_expr,
    const double* v1, const double* v2, const int size) {
  for (int i = 0; i < size; ++i) {
    const ::testing::internal::FloatingPoint<double> value1(v1[i]);
    const ::testing::internal::FloatingPoint<double> value2(v2[i]);
    if (!value1.AlmostEquals(value2)) {
      return ::testing::AssertionFailure()
             << i << " th element is different. " << std::endl
             << " expect: " << v1[i] << std::endl
             << " actual: " << v2[i];
    }
  }
  return ::testing::AssertionSuccess();
}

inline ::testing::AssertionResult IsElementEqual(
    const char* expr1, const char* expr2, const char* size_expr,
    const double* v1, const std::unique_ptr<double[]>& v2, const int size) {
  return IsElementEqual(expr1, expr2, size_expr, v1, v2.get(), size);
}

inline ::testing::AssertionResult IsElementEqual(
    const char* expr1, const char* expr2, const char* size_expr,
    const std::unique_ptr<double[]>& v1, const double* v2, const int size) {
  return IsElementEqual(expr1, expr2, size_expr, v1.get(), v2, size);
}

inline ::testing::AssertionResult IsElementEqual(
    const char* expr1, const char* expr2, const char* size_expr,
    const std::unique_ptr<double[]>& v1, const std::unique_ptr<double[]>& v2,
    const int size) {
  return IsElementEqual(expr1, expr2, size_expr, v1.get(), v2.get(), size);
}

//
// IsElementNearEqual
//

inline ::testing::AssertionResult IsElementNearEqual(
    const char* expr1, const char* expr2, const char* size_expr,
    const char* abs_error_expr, const double* vec1, const double* vec2,
    const int size, const double abs_error) {
  for (int i = 0; i < size; ++i) {
    const double diff = std::fabs(vec1[i] - vec2[i]);
    if (diff > abs_error) {
      return ::testing::AssertionFailure()
             << "The difference between " << expr1 << " and " << expr2 << " at "
             << i << "-th index is " << diff << ", which exceeds "
             << abs_error_expr << ", where\n"
             << expr1 << " evaluates to " << vec1[i] << ",\n"
             << expr2 << " evaluates to " << vec2[i] << ", and\n"
             << abs_error_expr << " evaluates to " << abs_error << ".";
    }
  }
  return ::testing::AssertionSuccess();
}

inline ::testing::AssertionResult IsElementNearEqual(
    const char* expr1, const char* expr2, const char* size_expr,
    const char* abs_error_expr, const std::unique_ptr<double[]>& vec1,
    const double* vec2, const int size, const double abs_error) {
  return IsElementNearEqual(expr1, expr2, size_expr, abs_error_expr, vec1.get(),
                            vec2, size, abs_error);
}

inline ::testing::AssertionResult IsElementNearEqual(
    const char* expr1, const char* expr2, const char* size_expr,
    const char* abs_error_expr, const double* vec1,
    const std::unique_ptr<double[]>& vec2, const int size,
    const double abs_error) {
  return IsElementNearEqual(expr1, expr2, size_expr, abs_error_expr, vec1,
                            vec2.get(), size, abs_error);
}

inline ::testing::AssertionResult IsElementNearEqual(
    const char* expr1, const char* expr2, const char* size_expr,
    const char* abs_error_expr, const std::unique_ptr<double[]>& vec1,
    const std::unique_ptr<double[]>& vec2, const int size,
    const double abs_error) {
  return IsElementNearEqual(expr1, expr2, size_expr, abs_error_expr, vec1.get(),
                            vec2.get(), size, abs_error);
}

}  // namespace test_util
}  // namespace recipe
