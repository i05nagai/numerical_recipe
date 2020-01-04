#include "numrecipe/quadrature/quadrature.h"
#include <iostream>
#include <vector>
#include <exception>
#include "numrecipe/quadrature/change_variable.h"

using namespace numrecipe::quadrature;
using namespace numrecipe;

namespace {

  Integrand GetTestFunction(const int id) {
    if (id == 0) {
      // integrate log(x)log(1-x) from 0 to 1 = 2 - pi^2 / 6
      static Integrand integrand = [](const double x) {
        assert(0.0 <= x && x <= 1.0);
        return std::log(x) * std::log(1.0 - x);
      };
      return integrand;
    } else if (id == 1) {
      // integrate 1.0 / (x^1/2 * (1 +x)) from 0 to inf equals pi
      return [](const double x) { 
        assert(0.0 <= x && x <= RECIPE_DOUBLE_INF);
        return 1.0 / (std::sqrt(x) * (1.0 + x));
      };
    } else if (id == 2) {
      // integrate x^{-3/2}sin(x/2) e^{-x} from 0 to inf equals sqrt(pi(sqrt(5) - 2))
      return [](const double x) { 
        assert(0.0 <= x && x <= RECIPE_DOUBLE_INF);
        return std::pow(x, -3.0 / 2.0) * std::sin(x / 2.0) * std::exp(-x);
      };
    } else if (id == 3) {
      // integrate x^{-2/7} e^{-x^{2}} from 0 to inf equals 0.5 * gamma(5/14)
      return [](const double x) { 
        assert(0.0 <= x && x <= RECIPE_DOUBLE_INF);
        return std::pow(x, - 2.0 / 7.0) * std::exp(-x * x);
      };
    } else if (id == 4) {
      // integrate (x - 2)(1-x)^{1/4}(1 + x)^{3/4} from -1 to 1 equals -1.9490...
      return [](const double x) { 
        assert(-1.0 <= x && x <= 1.0);
        return 1.0 / (x - 2.0) / std::pow(1.0 - x, 1.0 / 4.0) / std::pow(1.0 + x, 3.0 / 4.0);
      };
    } else if (id == 5) {
      // integrate cos(pi*x) / (1 - x)^{1/2} from -1 to 1 equals -0.69049...
      return [](const double x) { 
        assert(-1.0 <= x && x <= 1.0);
        return std::cos(RECIPE_PI * x) / std::sqrt(1.0 - x);
      };
    } else if (id == 6) {
      // integrate exp(-1-x) / (1 + x) from 0 to inf equals 0.21938...
      return [](const double x) { 
        return std::exp(-1.0 - x) / (1.0 + x);
      };
    } else if (id == 7) {
      // integrate 1.0 / (1 + x^{2})^{5/4} from -inf to inf equals 2.3962...
      return [](const double x) { 
        return 1.0 / std::pow(1.0 + x * x, 5.0 / 4.0);
      };
    } else if (id == 8) {
      // integrate 1.0 / (1 + x^{4}) from -inf to inf equals 2.2214...
      return [](const double x) { 
        return 1.0 / (1.0 + std::pow(x, 4.0));
      };
    } else {
      throw std::out_of_range("id must be less than 9");
    }
  }

  Integral GetIntegral(const int id) {
    if (id == 0) {
      return ChangeVariableFiniteToMinusOnePlusOne(GetTestFunction(id), 0.0, 1.0);
    } else if (id == 1) {
      return Integral(GetTestFunction(id), 0.0, RECIPE_DOUBLE_INF);
    } else if (id == 2) {
      return Integral(GetTestFunction(id), 0.0, RECIPE_DOUBLE_INF);
    } else if (id == 3) {
      return Integral(GetTestFunction(id), 0.0, RECIPE_DOUBLE_INF);
    } else if (id == 4) {
      return Integral(GetTestFunction(id), -1.0, 1.0);
    } else if (id == 5) {
      return Integral(GetTestFunction(id), -1.0, 1.0);
    } else if (id == 6) {
      return Integral(GetTestFunction(id), 0.0, RECIPE_DOUBLE_INF);
    } else if (id == 7) {
      return Integral(GetTestFunction(id), -RECIPE_DOUBLE_INF, RECIPE_DOUBLE_INF);
    } else if (id == 8) {
      return Integral(GetTestFunction(id), -RECIPE_DOUBLE_INF, RECIPE_DOUBLE_INF);
    } else {
      throw std::out_of_range("id must be less than 9");
    }
  }

  double GetIntegralExpected(const int id) {
    if (id == 0) {
      return 2.0 - RECIPE_PI * RECIPE_PI / 6.0;
    } else if (id == 1) {
      return RECIPE_PI;
    } else if (id == 2) {
      return std::sqrt(RECIPE_PI * (std::sqrt(5.0) - 2.0));
    } else if (id == 3) {
      return 0.5 * std::tgamma(5.0 / 14.0);
    } else if (id == 4) {
      return -1.9490;
    } else if (id == 5) {
      return -0.69049;
    } else if (id == 6) {
      return 0.2193839343955202;
    } else if (id == 7) {
      return 4.0 * std::sqrt(RECIPE_PI) * std::tgamma(3.0 / 4.0) / std::tgamma(1.0 / 4.0);
    } else if (id == 8) {
      return RECIPE_PI / std::sqrt(2.0);
    } else {
      throw std::out_of_range("id must be less than 6");
    }
  }
} // namespace


double Integrate(
    const Integral integral,
    const double length,
    const int n_partition,
    const int integration_mode) {
  if (integration_mode == 0) {
    return QuadratureDoubleExponentialFinite(integral, n_partition, length);
    // return QuadratureDoubleExponentialFinite(integral, n_partition, length);
  } else if (integration_mode == 1) {
    return QuadratureDoubleExponentialHalf(integral, n_partition, length);
  } else if (integration_mode == 2) {
    return QuadratureDoubleExponentialInfinite(integral, n_partition, length); 
  } else {
    throw std::out_of_range("integration_mode must be less than 4");
  }
}

void PartitionTest(
    const int id,
    const int integration_mode,
    const double length,
    const int n_partition) {
  const Integral integral = GetIntegral(id);
  const double expected = GetIntegralExpected(id);
  std::vector<int> n_partitions;

  std::cout << "id,length,n_partitions,value,expected,diff" << std::endl;
  for (int i = 0; i < 10; ++i) {
    n_partitions.push_back((i + 1) * n_partition);
    const double val = Integrate(integral, length, n_partitions[i], integration_mode);
    std::cout
      << id
      << ","
      << length
      << ","
      << n_partitions[i]
      << ","
      << val
      << ","
      << expected
      << ","
      << expected - val
      << std::endl;
  }
}

void LengthTest(
    const int id,
    const int integration_mode,
    const double step,
    const int n_partition) {
  const Integral integral = GetIntegral(id);
  const double expected = GetIntegralExpected(id);
  std::vector<double> lengths;

  std::cout << "id,length,n_partitions,value,expected,diff" << std::endl;
  for (int i = 0; i < 12; ++i) {
    lengths.push_back(step * (i + 1));
    const double val = Integrate(integral, lengths[i], n_partition, integration_mode);
    std::cout
      << id
      << ","
      << lengths[i]
      << ","
      << n_partition
      << ","
      << val
      << ","
      << expected
      << ","
      << expected - val
      << std::endl;
  }

}

int main(int argc, char const* argv[])
{
  std::cout << "Partition" << std::endl;
  PartitionTest(0, 0, 0.01, 10);
  PartitionTest(1, 1, 0.01, 10);
  PartitionTest(2, 1, 0.01, 10);
  PartitionTest(3, 1, 0.01, 10);
  PartitionTest(4, 0, 0.1, 10);
  PartitionTest(5, 0, 0.1, 10);
  PartitionTest(6, 1, 0.1, 10);
  PartitionTest(7, 2, 0.1, 10);
  PartitionTest(8, 2, 0.1, 10);

  std::cout << std::endl;
  std::cout << "Length" << std::endl;
  LengthTest(0, 0, 0.01, 20);
  LengthTest(1, 1, 0.01, 50);
  LengthTest(2, 1, 0.01, 50);
  LengthTest(3, 1, 0.01, 50);
  LengthTest(4, 0, 0.01, 30);
  LengthTest(5, 0, 0.01, 30);
  LengthTest(6, 1, 0.01, 30);
  LengthTest(7, 2, 0.01, 30);
  LengthTest(8, 2, 0.01, 30);
  return 0;
}
