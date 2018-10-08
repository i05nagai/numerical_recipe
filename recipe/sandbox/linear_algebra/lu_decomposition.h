#pragma once

#include <vector>
#include "recipe/sandbox/linear_algebra/matrix.h"
#include "recipe/sandbox/linear_algebra/vector.h"

namespace recipe {
namespace sandbox {
namespace linear_algebra {

class LU {
 private:
  const Matrix lu_;
  const std::vector<int> pivot_index_;

 public:
  LU(const Matrix& lu, const std::vector<int>& pivot_index);
  ~LU(){};
  Vector Solve(const Vector& b) const;

  const Matrix& lu() const { return lu_; };
  const std::vector<int> pivot_index() const { return pivot_index_; };
};

LU OuterProductLU(const Matrix& a);
LU OuterProductLUWithPartialPivot(const Matrix& a);
LU CroutLU(const Matrix& a);

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe
