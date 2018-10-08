#include "recipe/sandbox/linear_algebra/lu_decomposition.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <stdexcept>

namespace recipe {
namespace sandbox {
namespace linear_algebra {

LU::LU(const Matrix& lu, const std::vector<int>& pivot_index)
    : lu_(lu), pivot_index_(pivot_index) {}

LU OuterProductLU(const Matrix& a) {
  assert(a.nrow() == a.ncol());

  Matrix lu_mat(a);
  int n = lu_mat.ncol();

  for (int k = 0; k < n - 1; k++) {
    if (abs(lu_mat(k, k)) < 1e-20)
      throw std::runtime_error("failed to LU decomposition");

    for (int i = k + 1; i < n; i++) {
      lu_mat(i, k) /= lu_mat(k, k);
      for (int j = k + 1; j < n; j++) {
        lu_mat(i, j) -= lu_mat(i, k) * lu_mat(k, j);
      }
    }
  }

  std::vector<int> piv(lu_mat.nrow());
  std::iota(piv.begin(), piv.end(), 0);

  return LU(lu_mat, piv);
}

LU OuterProductLUWithPartialPivot(const Matrix& a) {
  assert(a.nrow() == a.ncol());

  Matrix lu_mat(a);
  std::vector<int> piv(lu_mat.nrow());
  std::iota(piv.begin(), piv.end(), 0);

  int n = lu_mat.nrow();
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
    std::swap(piv[k], piv[piv_ind]);

    if (piv[k] != k) {
      // interchange rows
      for (int j = 0; j < n; j++) {
        std::swap(lu_mat(k, j), lu_mat(piv[k], j));
      }
    }
    if (abs(lu_mat(k, k)) < 1e-20)
      throw std::runtime_error("matrix is singular!!");

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
  assert(a.nrow() == a.ncol());

  Matrix lu_mat(a);
  int n = lu_mat.nrow();

  for (int j = 0; j < n; j++) {
    // update U
    for (int i = 0; i <= j; i++) {
      double sum = 0;
      for (int k = 0; k < i; k++) sum += lu_mat(i, k) * lu_mat(k, j);
      lu_mat(i, j) -= sum;
    }

    if (abs(lu_mat(j, j)) < 1e-20)
      throw std::runtime_error("failed to LU decomposition");

    // update L
    for (int i = j + 1; i < n; i++) {
      double sum = 0;
      for (int k = 0; k < j; k++) sum += lu_mat(i, k) * lu_mat(k, j);
      lu_mat(i, j) -= sum;
      lu_mat(i, j) /= lu_mat(j, j);
    }
  }

  std::vector<int> piv(lu_mat.nrow());
  std::iota(piv.begin(), piv.end(), 0);

  return LU(lu_mat, piv);
}

Vector LU::Solve(const Vector& b) const {
  const Matrix lu_mat = lu();
  const std::vector<int> piv = pivot_index();

  int n = b.size();
  assert(lu_mat.ncol() == n);

  Vector bb = b;
  Vector x(n);

  // forward substitution
  x(0) = bb(piv[0]);
  for (int i = 1; i < n; i++) {
    double sum = 0;
    for (int j = 0; j < i; j++) sum += lu_mat(i, j) * x(j);

    x(i) = bb(piv[i]) - sum;
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
