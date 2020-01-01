#include "numrecipe/linear_algebra/triangular.h"
#include <gtest/gtest.h>
#include <algorithm>
#include "numrecipe/linear_algebra/matrix.h"
#include "numrecipe/linear_algebra/test_util/test_data.h"

namespace numrecipe {
namespace linear_algebra {
TEST(SolveLinearEquationUpperTriangularTest, ManualSolution) {
  const int col_size = 2;
  const int row_size = 2;
  const int size = row_size * col_size;
  std::unique_ptr<double[]> mat_data = TestData::GetRandomDoublePointer(size);
  std::unique_ptr<double[]> mat(new double[size]);
  std::copy(mat_data.get(), mat_data.get() + size, mat.get());
  Matrix mat_copy(row_size, col_size, std::move(mat_data));

  std::unique_ptr<double[]> vector_data =
      TestData::GetRandomDoublePointer(size);
  std::unique_ptr<double[]> vector(new double[size]);
  std::copy(vector_data.get(), vector_data.get() + row_size, vector.get());

  SolveLinearEquationUpperTriangular(mat.get(), row_size, col_size,
                                     vector.get(), row_size);

  // manually solve
  const double expect1 = vector_data[1] / mat_copy(1, 1);
  const double expect0 =
      (vector_data[0] - expect1 * mat_copy(0, 1)) / mat_copy(0, 0);
  EXPECT_EQ(expect0, vector[0]);
  EXPECT_EQ(expect1, vector[1]);
}

TEST(SolveLinearEquationLowerTriangularTest, ManualSolution) {
  const int col_size = 2;
  const int row_size = 2;
  const int size = row_size * col_size;
  std::unique_ptr<double[]> mat_data = TestData::GetRandomDoublePointer(size);
  std::unique_ptr<double[]> mat(new double[size]);
  std::copy(mat_data.get(), mat_data.get() + size, mat.get());
  Matrix mat_copy(row_size, col_size, std::move(mat_data));

  std::unique_ptr<double[]> vector_data =
      TestData::GetRandomDoublePointer(size);
  std::unique_ptr<double[]> vector(new double[size]);
  std::copy(vector_data.get(), vector_data.get() + row_size, vector.get());

  SolveLinearEquationLowerTriangular(mat.get(), row_size, col_size,
                                     vector.get(), row_size);

  // manually solve
  const double expect0 = vector_data[0] / mat_copy(0, 0);
  const double expect1 =
      (vector_data[1] - expect0 * mat_copy(1, 0)) / mat_copy(1, 1);
  EXPECT_EQ(expect0, vector[0]);
  EXPECT_EQ(expect1, vector[1]);
}
}  // namespace linear_algebra
}  // namespace numrecipe
