#pragma once
#include <gtest/gtest.h>
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

namespace recipe {
namespace test_util {
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

inline ::testing::AssertionResult IsElementEqual(
    const char* expr1, const char* expr2, const char* size_expr,
    const std::unique_ptr<double[]>& v1, const std::unique_ptr<double[]>& v2,
    const int size) {
  for (size_t i = 0; i < size; ++i) {
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

}  // namespace test_util
}  // namespace recipe
