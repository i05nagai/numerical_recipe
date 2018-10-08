#pragma once

namespace recipe {
namespace sandbox {
namespace linear_algebra {

class Vector {
 private:
  int size_;
  double* data_;

 public:
  Vector(int size);
  Vector(const Vector& v);
  ~Vector();

  double operator()(int i) const;
  double& operator()(int i);
  Vector& operator=(const Vector& v);

  int size() const { return size_; }
};

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe
