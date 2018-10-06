#pragma once

namespace recipe {
namespace sandbox {
namespace linear_algebra {

class Vector {
 private:
  int len;
  double* data;

 public:
  Vector(int length);
  Vector(const Vector& v);
  ~Vector();

  double operator()(int i) const;
  double& operator()(int i);
  Vector& operator=(const Vector& v);

  int Length() const { return len; }
};

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe
