#pragma once
#include <random>
#include <vector>
#include <memory>

namespace recipe {
namespace test_util {

/// @brief Create random numbers.
///
/// Example:
///
/// ```cpp
///   RandomNumber generator;
///   const double val1 = generator();
/// ```
class RandomNumber {
  // private typedef
 private:
  // public typedef
 public:
  // public function
 public:
  RandomNumber(const std::size_t seed = 3252352)
      : engine_(seed), distribution_() {}
  ///
  /// @brief random value in [0, 1).
  ///
  /// @return random value in [0, 1).
  ///
  double operator()() { return distribution_(engine_); }
  ///
  /// @brief Create random number between [min, max)
  ///
  /// @param min the minimal value of random value.
  /// @param max the maximal value of random value.
  ///
  /// @return random number within [min, max)
  ///
  double operator()(const double min, const double max) {
    const int diff = max - min;
    return (*this)() * diff + min;
  }
  // private function
 private:
  // private members
 private:
  std::mt19937 engine_;
  std::uniform_real_distribution<double> distribution_;
};  // class RandomNumber {


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

  static std::vector<double> GetRandomNumbersSorted(
      const std::size_t size, const bool ascending = true) {
    std::vector<double> x = TestData::GetRandomNumbers(size);
    if (ascending) {
      std::sort(x.begin(), x.end());
    } else {
      std::sort(x.begin(), x.end(), std::greater<double>());
    }
    return x;
  }

  // private function
 private:
  // private members
 private:
};  // class TestData {

}  // namespace test_util
}  // namespace recipe
