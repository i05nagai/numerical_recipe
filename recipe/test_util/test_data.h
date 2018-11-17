#pragma once
#include <random>

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

}  // namespace test_util
}  // namespace recipe
