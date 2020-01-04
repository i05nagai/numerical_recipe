#include <algorithm>
#include <initializer_list>
#include <memory>

namespace numrecipe {
namespace linear_algebra {

std::unique_ptr<double[]> MakeDoubleArray(std::initializer_list<double> list) {
  const int size = list.size();
  std::unique_ptr<double[]> data(new double[size * size]);
  std::copy(list.begin(), list.end(), data.get());
  return data;
}

std::unique_ptr<double[]> GetIndentityMatrix(const int mat_size) {
  std::unique_ptr<double[]> data(new double[mat_size * mat_size]);
  std::fill(data.get(), data.get() + mat_size * mat_size, 0);
  for (int i = 0; i < mat_size; ++i) {
    data[i * mat_size + i] = 1.0;
  }
  return data;
}

std::unique_ptr<double[]> CopyDoubleArray(const double* original,
                                          const int size) {
  std::unique_ptr<double[]> data(new double[size]);
  std::copy(original, original + size, data.get());
  return data;
}
}  // namespace linear_algebra
}  // namespace numrecipe
