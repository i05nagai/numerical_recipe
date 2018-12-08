#pragma once

#include <algorithm>
#include <initializer_list>
#include <memory>

namespace recipe {
namespace linear_algebra {
std::unique_ptr<double[]> MakeDoubleArray(std::initializer_list<double> list);

std::unique_ptr<double[]> GetIndentityMatrix(const int mat_size);

std::unique_ptr<double[]> CopyDoubleArray(const double* orginal,
                                          const int size);
}  // namespace linear_algebra
}  // namespace recipe
