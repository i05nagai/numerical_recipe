#include "numrecipe/integrate/sample.h"
#include <benchmark/benchmark.h>

namespace numrecipe {
namespace integrate {
static void BenchmarkFoobar(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(Foobar(state.range(0)));
  }
}
// clang-format off
BENCHMARK(BenchmarkFoobar)
  ->Arg(100)
  ->Arg(1000)
  ->Arg(10000);
// clang-format on
}  // namespace integrate
}  // namespace numrecipe
