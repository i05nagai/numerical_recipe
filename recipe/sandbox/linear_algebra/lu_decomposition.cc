#include "recipe/sandbox/linear_algebra/lu_decomposition.h"
#include <cmath>
#include <iostream>
#include <numeric>
#include <stdexcept>

namespace recipe {
namespace sandbox {
namespace linear_algebra {

LU::LU(const Matrix& lu_mat, const std::vector<int>& piv_ind)
    : lu(lu_mat), piv(piv_ind) {}

LU OuterProductLU(const Matrix& a) {
  Matrix lu_mat(a);
  int n = lu_mat.NCol();

  for (int k = 0; k < n - 1; k++) {
    if (lu_mat(k, k) == 0)
      throw std::runtime_error("failed to LU decomposition");

    for (int i = k + 1; i < n; i++) {
      lu_mat(i, k) /= lu_mat(k, k);
      for (int j = k + 1; j < n; j++) {
        lu_mat(i, j) -= lu_mat(i, k) * lu_mat(k, j);
      }
    }
  }

  std::vector<int> piv(lu_mat.NRow());
  std::iota(piv.begin(), piv.end(), 0);

  return LU(lu_mat, piv);
}

LU OuterProductLUWithPartialPivot(const Matrix& a) {
  Matrix lu_mat(a);
  std::vector<int> piv(lu_mat.NRow());
  std::iota(piv.begin(), piv.end(), 0);

  int n = lu_mat.NRow();
  for (int k = 0; k < n - 1; k++) {
    // partial pivoting
    double piv_max = abs(lu_mat(k, k));
    int piv_ind = k;
    for (int t = k + 1; t < n; t++) {
      if (piv_max < abs(lu_mat(t, k))) {
        piv_max = abs(lu_mat(t, k));
        piv_ind = t;
      }
    }
    piv[k] = piv_ind;

    if (piv[k] != k) {
      // interchange rows
      for (int j = 0; j < n; j++) {
        std::swap(lu_mat(k, j), lu_mat(piv[k], j));
      }
    }
    if (lu_mat(k, k) == 0) throw std::runtime_error("matrix is singular!!");

    for (int i = k + 1; i < n; i++) {
      lu_mat(i, k) /= lu_mat(k, k);
      for (int j = k + 1; j < n; j++) {
        lu_mat(i, j) -= lu_mat(i, k) * lu_mat(k, j);
      }
    }
  }

  return LU(lu_mat, piv);
}

LU CroutLU(const Matrix& a) {
  Matrix lu_mat(a);
  int n = lu_mat.NRow();

  for (int j = 0; j < n; j++) {
    // update U
    for (int i = 0; i <= j; i++) {
      double sum = 0;
      for (int k = 0; k < i; k++) sum += lu_mat(i, k) * lu_mat(k, j);
      lu_mat(i, j) -= sum;
    }

    if (lu_mat(j, j) == 0)
      throw std::runtime_error("failed to LU decomposition");

    // update L
    for (int i = j + 1; i < n; i++) {
      double sum = 0;
      for (int k = 0; k < j; k++) sum += lu_mat(i, k) * lu_mat(k, j);
      lu_mat(i, j) -= sum;
      lu_mat(i, j) /= lu_mat(j, j);
    }
  }

  std::vector<int> piv(lu_mat.NRow());
  std::iota(piv.begin(), piv.end(), 0);

  return LU(lu_mat, piv);
}

Vector LU::Solve(const Vector& b) const {
  const Matrix lu_mat = get_lu();
  const std::vector<int> piv = get_piv();

  int n = b.Length();
  Vector bb = b;
  Vector x(n);

  // forward substitution
  std::swap(bb(0), bb(piv[0]));
  x(0) = bb(0);
  for (int i = 1; i < n; i++) {
    double sum = 0;
    for (int j = 0; j < i; j++) sum += lu_mat(i, j) * x(j);

    std::swap(bb(i), bb(piv[i]));
    x(i) = bb(i) - sum;
  }

  // backsubstitution
  x(n - 1) /= lu_mat(n - 1, n - 1);
  for (int i = n - 2; i >= 0; i--) {
    double sum = 0;
    for (int j = i + 1; j < n; j++) sum += lu_mat(i, j) * x(j);
    x(i) = (x(i) - sum) / lu_mat(i, i);
  }

  return x;
}

}  // namespace linear_algebra
}  // namespace sandbox
}  // namespace recipe
