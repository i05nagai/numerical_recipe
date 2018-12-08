#pragma once
#include <vector>
#include "recipe/linear_algebra/base.h"
#include "recipe/linear_algebra/matrix.h"
#include "recipe/linear_algebra/vector.h"
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
    std::vector<double> values = TestData::GetRandomNumbers(size);
    std::copy(values.begin(), values.end(), matrix.get());
    return matrix;
  }

  static Matrix GetRandomMatrix(const int row_size, const int col_size) {
    const int size = row_size * col_size;
    std::unique_ptr<double[]> data = GetRandomDoublePointer(size);
    return Matrix(row_size, col_size, std::move(data));
  }

  static Vector GetRandomVector(const int size) {
    std::unique_ptr<double[]> data = GetRandomDoublePointer(size);
    return Vector(size, std::move(data));
  }
  // private function
 private:
  // private members
 private:
};  // class TestData {

///
///
///
/// Exmaple:
///
/// ```c++
///  LinearEquationGenerator generator(size);
///  const Matrix& mat = generator.CreateMatrix();
///  const Vector& vec = generator.CreateVector();
///
/// ```
///
/// The system is used in the paper
/// Higham, N. J. (1997). Iterative refinement for linear systems and LAPACK.
/// IMA Journal of Numerical Analysis. https://doi.org/10.1093/imanum/17.4.495
///
class LinearEquationGenerator {
 public:
  LinearEquationGenerator(const int size) : size_(size) {}

  Matrix CreateMatrix() {
    const int mat_size = size_ * size_;
    std::unique_ptr<double[]> data(new double[mat_size]);
    for (int k = 0; k < mat_size; ++k) {
      const int row = k / size_;
      const int col = k % size_;
      data[k] = this->CreateMatrixElement(row, col);
    }
    return Matrix(size_, size_, std::move(data));
  }

  Vector CreateVector() {
    std::unique_ptr<double[]> data(new double[size_]);
    for (int k = 0; k < size_; ++k) {
      data[k] = this->CreateVectorElement(k);
    }
    return Vector(size_, std::move(data));
  }

 private:
  double CreateMatrixElement(const int row, const int col) {
    const int r = row + 1;
    const int c = col + 1;
    const double alpha = 10e-5;
    const double d = std::pow(alpha, 1.0 / r);
    const double factor1 = std::pow(d * (2 / (size_ + 1.0)), 0.5);
    const double factor2 = std::sin(r * c * PI / (size_ + 1.0));
    return factor1 * factor2;
  }

  double CreateVectorElement(const int row) { return row + 1; }

 private:
  int size_;
};
}  // namespace linear_algebra
}  // namespace recipe
