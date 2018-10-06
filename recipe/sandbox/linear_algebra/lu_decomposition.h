#pragma once

#include <vector>
#include "recipe/sandbox/linear_algebra/matrix.h"
#include "recipe/sandbox/linear_algebra/vector.h"

namespace recipe {
namespace sandbox {
namespace linear_algebra {

class LU {
 private:
  const Matrix lu;
  const std::vector<int> piv;

 public:
  LU(const Matrix& lu_mat, const std::vector<int>& piv_ind);
  ~LU(){};
  Vector Solve(const Vector& b) const;

  const Matrix& get_lu() const { return lu; };
  const std::vector<int> get_piv() const { return piv; };
};

LU OuterProductLU(const Matrix& a);
LU OuterProductLUWithPartialPivot(const Matrix& a);
LU CroutLU(const Matrix& a);

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe
