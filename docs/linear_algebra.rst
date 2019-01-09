Linear Algebra
==============


Triangular Matrix
-----------------

.. doxygenfunction:: recipe::linear_algebra::SolveLinearEquationLowerTriangular
   :project: recipe
   :path: ...

.. doxygenfunction:: recipe::linear_algebra::SolveLinearEquationUpperTriangular
   :project: recipe
   :path: ...


Band-Diagonal Matrix
---------------------

.. doxygenfunction:: recipe::linear_algebra::GaussianEliminationOuterProductBandDiagonal(double *, const int, const int)
   :project: recipe
   :path: ...


Matrix
-------

.. doxygenclass:: recipe::linear_algebra::Matrix
   :project: recipe
   :path: ...
   :members:
   :protected-members:
   :private-members:
   :undoc-members:

.. doxygenfunction:: recipe::linear_algebra::MakeMatrix
   :project: recipe
   :path: ...


.. doxygenfunction:: recipe::linear_algebra::MakeIdentityMatrix
   :project: recipe
   :path: ...

Householder Transformation
---------------------------

.. doxygenfunction:: recipe::linear_algebra::ComputeHouseholderVector(const double *, const int, double *, double *)
   :project: recipe
   :path: ...

.. doxygenfunction:: recipe::linear_algebra::ComputeHouseholderMatrix(const double *, const double, const int)
   :project: recipe
   :path: ...

.. doxygenfunction:: recipe::linear_algebra::ComputeHouseholderBidiagonalization
   :project: recipe
   :path: ...


QR decompositions
-----------------

.. doxygenfunction:: recipe::linear_algebra::ComputeHouseholderQR(double* mat_a, const int row_size, const int col_size)
   :project: recipe
   :path: ...

.. doxygenfunction:: recipe::linear_algebra::ConvertHouseholderQRToQ(const double*, const double*, const int, const int);
   :project: recipe
   :path: ...

.. doxygenfunction:: recipe::linear_algebra::ConvertHouseholderQRToR(const double*, const double*, const int, const int);
   :project: recipe
   :path: ...

.. doxygenfunction:: recipe::linear_algebra::ConvertHouseholderQRToQR(const double*, const double*, const int, const int);
   :project: recipe
   :path: ...

Gievns Rotation
---------------

.. doxygenfunction:: recipe::linear_algebra::ComputeGivensRotationParameters
   :project: recipe
   :path: ...

.. doxygenfunction:: recipe::linear_algebra::MultiplyGivensRotation(const int, const int, const std::pair<double, double>&, double *, const int, const int)
   :project: recipe
   :path: ...

.. doxygenfunction:: recipe::linear_algebra::MultiplyGivensRotation(double *, const int, const int, const int, const int, const std::pair<double, double>&)
   :project: recipe
   :path: ...
