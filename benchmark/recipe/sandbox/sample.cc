#include "recipe/sandbox/sample.h"
#include <benchmark/benchmark.h>

namespace recipe {
namespace sandbox {
static void BenchmarkFoo(benchmark::State& state)
{
  while(state.KeepRunning()) {
    benchmark::DoNotOptimize(Foo());
  }
}
BENCHMARK(BenchmarkFoo);
} // namespace sandbox
} // namespace recipe

