namespace recipe {
namespace quadrature {
/*! \enum QuadratureRule
 *
 *  QuadratureRule enumerator lists all the quadrature rules that have been
 * implemented. Avairable are: Trapezoidal, Simpson. Please put a name in the
 * definition when you implements a new quadrature rule.
 *
 */
enum QuadratureRule { Trapezoidal, Simpson };

double RichardsonExtrapolation(QuadratureRule quadrature_rule,
                               double (*integrand)(double),
                               double left_endpoint, double right_endpoint,
                               unsigned int num_of_partition);
}  // namespace quadrature
}  // namespace recipe
