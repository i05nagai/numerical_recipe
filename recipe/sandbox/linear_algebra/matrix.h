#pragma once

namespace recipe {
namespace sandbox {
namespace linear_algebra {

class Matrix {
 private:
  int nrow;
  int ncol;
  double* data;

 public:
  Matrix(const int nrows, const int ncols);
  Matrix(const Matrix& m);
  ~Matrix();

  double operator()(int i, int j) const;
  double& operator()(int i, int j);
  Matrix& operator=(const Matrix& m);

  int NRow() const { return nrow; }
  int NCol() const { return ncol; }
};

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe
