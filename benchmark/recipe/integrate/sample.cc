#include "recipe/integrate/sample.h"
#include <benchmark/benchmark.h>

namespace recipe {
namespace integrate {
static void BenchmarkFoobar(benchmark::State& state)
{
  while(state.KeepRunning()) {
    benchmark::DoNotOptimize(Foobar(state.range(0)));
  }
}
BENCHMARK(BenchmarkFoobar)
  ->Arg(100)
  ->Arg(1000)
  ->Arg(10000);
} // namespace integrate
} // namespace recipe
