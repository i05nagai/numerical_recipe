#include "recipe/sandbox/linear_algebra/vector.h"
#include <iostream>

namespace recipe {
namespace sandbox {
namespace linear_algebra {

Vector::Vector(int size) : size_(size), data_(new double[size]) {
  for (int i = 0; i < size_; i++) data_[i] = 0.0;
}

Vector::Vector(const Vector& v) : size_(v.size_), data_(new double[v.size_]) {
  for (int i = 0; i < size_; i++) data_[i] = v.data_[i];
}

Vector::~Vector() { delete[] data_; };

double Vector::operator()(int i) const { return data_[i]; }
double& Vector::operator()(int i) { return data_[i]; }

Vector& Vector::operator=(const Vector& v) {
  size_ = v.size_;
  data_ = new double[size_];
  for (int i = 0; i < size_; i++) data_[i] = v.data_[i];

  return *this;
}

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe
