%module quadrature_wrap
%{
#include "../../recipe/quadrature/change_variable.h"
#include "../../recipe/quadrature/quadrature_gaussian.h"
#include "../../recipe/quadrature/quadrature.h"
#include "../../recipe/quadrature/richardson_extrapolation.h"
using namespace recipe::quadrature;
%}
%include "../../recipe/quadrature/change_variable.h"
%include "../../recipe/quadrature/quadrature_gaussian.h"
%include "../../recipe/quadrature/quadrature.h"
%include "../../recipe/quadrature/richardson_extrapolation.h"
using namespace recipe::quadrature;

