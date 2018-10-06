#include "recipe/sandbox/linear_algebra/vector.h"
#include <iostream>

namespace recipe {
namespace sandbox {
namespace linear_algebra {

Vector::Vector(int length) : len(length), data(new double[length]) {
  for (int i = 0; i < len; i++) data[i] = 0.0;
}

Vector::Vector(const Vector& v) : len(v.len), data(new double[v.len]) {
  for (int i = 0; i < len; i++) data[i] = v.data[i];
}

Vector::~Vector() { delete[] data; };

double Vector::operator()(int i) const { return data[i]; }
double& Vector::operator()(int i) { return data[i]; }

Vector& Vector::operator=(const Vector& v) {
  len = v.len;
  data = new double[len];
  for (int i = 0; i < len; i++) data[i] = v.data[i];

  return *this;
}

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe
