%module quadrature_wrap
%{
#include "../../numrecipe/quadrature/change_variable.h"
#include "../../numrecipe/quadrature/quadrature_gaussian.h"
#include "../../numrecipe/quadrature/quadrature.h"
#include "../../numrecipe/quadrature/richardson_extrapolation.h"
using namespace numrecipe::quadrature;
%}
%include "../../numrecipe/quadrature/change_variable.h"
%include "../../numrecipe/quadrature/quadrature_gaussian.h"
%include "../../numrecipe/quadrature/quadrature.h"
%include "../../numrecipe/quadrature/richardson_extrapolation.h"
using namespace numrecipe::quadrature;

