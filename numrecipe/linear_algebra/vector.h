#pragma once

#include <iostream>
#include <memory>

namespace numrecipe {
namespace linear_algebra {

class Vector {
 public:
  explicit Vector(const int size);
  explicit Vector(std::initializer_list<double> list);
  Vector(const int size, const std::unique_ptr<double[]> data);
  Vector(const Vector& other);

  Vector& operator+=(const Vector& other);
  double operator()(int i) const;
  double& operator()(int i);
  Vector& operator=(const Vector& other);
  bool operator==(const Vector& other) const;
  int Size() const { return size_; }
  double* Get() { return data_.get(); }
  const double* Get() const { return data_.get(); };

 private:
  int size_;
  std::unique_ptr<double[]> data_;
};

Vector MakeUnitVector(const int size, const int pos);
Vector MakeVector(std::initializer_list<double> list);
std::ostream& operator<<(std::ostream& os, const Vector& target);

}  // namespace linear_algebra
}  // namespace numrecipe
