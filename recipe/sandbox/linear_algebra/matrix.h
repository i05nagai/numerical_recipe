#pragma once
#include <memory>

namespace recipe {
namespace sandbox {
namespace linear_algebra {

class Matrix {
 private:
  int nrow_;
  int ncol_;
  std::unique_ptr<double[]> data_;

 public:
  Matrix(const int nrows, const int ncols);
  Matrix(const Matrix& m);

  double operator()(int i, int j) const;
  double& operator()(int i, int j);
  Matrix& operator=(const Matrix& m);

  int nrow() const { return nrow_; }
  int ncol() const { return ncol_; }
};

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe
