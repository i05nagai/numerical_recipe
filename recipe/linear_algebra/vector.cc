#include "recipe/linear_algebra/vector.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include "recipe/linear_algebra/util.h"

namespace recipe {
namespace linear_algebra {

Vector::Vector(const int size) : size_(size), data_(new double[size]) {}

Vector::Vector(std::initializer_list<double> list)
    : size_(list.size()), data_(new double[list.size()]) {
  std::copy(list.begin(), list.end(), data_.get());
}

Vector::Vector(const int size, std::unique_ptr<double[]> data)
    : size_(size), data_(std::move(data)) {}

Vector::Vector(const Vector& other)
    : size_(other.size_), data_(new double[other.size_]) {
  std::copy(other.data_.get(), other.data_.get() + other.size_, data_.get());
}

double Vector::operator()(int i) const {
  assert(0 <= i && i < size_);
  return data_[i];
}

double& Vector::operator()(int i) {
  assert(0 <= i && i < size_);
  return data_[i];
}

Vector& Vector::operator+=(const Vector& other) {
  for (int i = 0; i < other.size_; ++i) {
    data_[i] += other.data_[i];
  }
  return *this;
}

Vector& Vector::operator=(const Vector& other) {
  size_ = other.size_;
  data_ = std::unique_ptr<double[]>(new double[size_]);
  std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
  return *this;
}

bool Vector::operator==(const Vector& other) const {
  if (size_ != other.size_) {
    return false;
  }
  return std::equal(data_.get(), data_.get() + size_, other.data_.get());
}

//
// free functions
//
Vector MakeUnitVector(const int size, const int pos) {
  assert(pos < size);
  std::unique_ptr<double[]> data(new double[size]);
  std::fill(data.get(), data.get() + size, 0);
  data[pos] = 1.0;
  return Vector(size, std::move(data));
}

Vector MakeVector(std::initializer_list<double> list) {
  std::unique_ptr<double[]> data = MakeDoubleArray(list);
  return Vector(list.size(), std::move(data));
}

std::ostream& operator<<(std::ostream& os, const Vector& target) {
  for (int i = 0; i < target.Size(); ++i) {
    os << target(i) << ", ";
  }
  return os;
}

}  // namespace linear_algebra
}  // namespace recipe
