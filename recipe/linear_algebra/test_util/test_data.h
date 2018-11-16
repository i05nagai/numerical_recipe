#pragma once
#include <vector>
#include "recipe/test_util/test_data.h"

namespace recipe {
namespace linear_algebra {
///
/// @brief Common test data in linear_algebra.
///
/// Example:
///
/// ```
///   std::vector<double> data = TestData::GetRandomNumbers(10);
/// ```
class TestData {
  // private typedef
 private:
  // public typedef
 public:
  // public function
 public:
  ///
  /// @brief Generate random values whose value is within [0, 1).
  ///
  /// @param size
  ///
  /// @return vector of random values.
  ///
  static std::vector<double> GetRandomNumbers(const std::size_t size) {
    static test_util::RandomNumber generator;

    std::vector<double> x(size);
    std::generate(x.begin(), x.end(), generator);
    return x;
  }

  ///
  /// @brief Generate random values whose value is within [0, 1).
  ///
  /// @param size
  ///
  /// @return double array of random values.
  ///
  static std::unique_ptr<double[]> GetRandomDoublePointer(
      const std::size_t size) {
    std::unique_ptr<double[]> matrix(new double[size]);
    std::vector<double> data = TestData::GetRandomNumbers(size);
    std::copy(data.begin(), data.end(), matrix.get());
    return matrix;
  }

  static std::unique_ptr<double[]> GetRandomMatrix(const std::size_t row_size,
                                                   const std::size_t col_size) {
    const int size = row_size * col_size;
    return GetRandomDoublePointer(size);
  }
  // private function
 private:
  // private members
 private:
};  // class TestData {
}  // namespace linear_algebra
}  // namespace recipe
