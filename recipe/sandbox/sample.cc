#include "recipe/sandbox/sample.h"
#include "Eigen/Core"
#include <iostream>

namespace recipe {
namespace sandbox {
int Foo() {
  // Eigen::Matrix<double, Dynamic, Dynamic, RowMajor> m1;
  // Eigen::Matrix<double, Dynamic, Dynamic, RowMajor> m2;
  Eigen::Matrix4f m1;
  m1 <<
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16;
  Eigen::Matrix4f m2;
  m2 <<
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16;
  Eigen::Array44f a1;
  a1 <<
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16;
  Eigen::Array44f a2;
  a2 <<
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16;
  Eigen::Vector4d v1(1, 2, 3, 4);
  // coeffwise product, implicit conversion from array to matrix.
  m1 = a1 * a2;
  // matrix product, implicit conversion from matrix to array.
  a1 = m1 * m2;
  // mixing array and matrix is forbidden
  a2 = a1 + m1.array();
  m2 = a1.matrix() + m1;

  std::cout << m1 << std::endl;
  std::cout << m2 << std::endl;
  std::cout << v1.size() << std::endl;
  return 1;
}
}  // namespace sandbox
}  // namespace recipe
