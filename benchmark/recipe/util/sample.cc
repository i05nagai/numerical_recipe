#include "recipe/util/sample.h"
#include <benchmark/benchmark.h>

namespace recipe {
namespace util {
static void BenchmarkBar(benchmark::State& state) {
  while (state.KeepRunning()) {
    benchmark::DoNotOptimize(Bar());
  }
}
BENCHMARK(BenchmarkBar);
}  // namespace util
}  // namespace recipe
